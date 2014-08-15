namespace CorsWebAPI.Attributes
{
    using System;
    using System.Linq;
    using System.Web;
    using System.Web.Http.Controllers;
    using System.Web.Http.Filters;

    namespace Portal.Filters
    {
        public class AllowCrossOriginAttribute : System.Web.Http.Filters.ActionFilterAttribute
        {
            public string HttpMethod { get; set; }

            public override void OnActionExecuting(HttpActionContext actionContext)
            {
                OnActionExecuting(HttpMethod, HttpContext.Current, () => base.OnActionExecuting(actionContext));
            }

            public override void OnActionExecuted(HttpActionExecutedContext actionExecutedContext)
            {
                OnActionExecuted(HttpContext.Current,
                                             () => base.OnActionExecuted(actionExecutedContext));
            }


            private enum CrossOriginRequestType
            {
                CorsPreFlight,
                Cors,
                Default
            }

            private CrossOriginRequestType _requestType;
            private string _origin;

            // Request Headers
            private const string OriginHeader = "Origin";

            // Response Headers
            public const string AccessControlAllowOriginHeader = "Access-Control-Allow-Origin";
            public const string AccessControlAllowMethods = "Access-Control-Allow-Methods";
            public const string AccessControlAllowHeaders = "Access-Control-Allow-Headers";
            public const string AccessControlAllowCredentials = "Access-Control-Allow-Credentials";

            private const string OptionsMethod = "OPTIONS";


            public void DetermineRequestType(HttpRequest request)
            {
                var originArray = request.Headers.GetValues(OriginHeader);
                _origin = (originArray != null ? originArray.FirstOrDefault() : null);

                var isPreflightRequest = request.HttpMethod == OptionsMethod;

                if (String.IsNullOrEmpty(_origin))
                    _requestType = CrossOriginRequestType.Default;
                else if (isPreflightRequest)
                    _requestType = CrossOriginRequestType.CorsPreFlight;
                else
                    _requestType = CrossOriginRequestType.Cors;
            }

            public void OnActionExecuting(string httpMethod, HttpContext httpContext, Action baseAction)
            {
                DetermineRequestType(httpContext.Request);

                if (_requestType != CrossOriginRequestType.CorsPreFlight)
                {
                    baseAction();
                    return;
                }

                // Add response headers for the CORS request
                var response = httpContext.Response;

                // Allow only GET requests to be called cross-domain by default
                response.AppendHeader(AccessControlAllowMethods, httpMethod ?? "GET");
                response.AppendHeader(AccessControlAllowCredentials, "true");
                response.AppendHeader(AccessControlAllowOriginHeader, _origin);
                response.AppendHeader(AccessControlAllowHeaders, "content-type, accept");
                response.End();
            }

            public void OnActionExecuted(HttpContext httpContext, Action baseAction)
            {

                DetermineRequestType(HttpContext.Current.Request);
                
                switch (_requestType)
                {
                    case CrossOriginRequestType.Cors:
                        // If the Origin header is in the request, then process this as a CORS request
                        // Let the default filter process the request
                        baseAction();

                        // Add response headers for the CORS request
                        var response = httpContext.Response;

                        // Allow all origins
                        response.AppendHeader(AccessControlAllowOriginHeader, _origin);
                        response.AppendHeader(AccessControlAllowCredentials, "true");

                        break;

                    default:
                        baseAction();

                        break;
                }
            }
        }
    }
}