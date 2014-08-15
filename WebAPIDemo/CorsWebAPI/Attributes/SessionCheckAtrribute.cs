using System.Configuration;
using System.Net;
using System.Web;
using System.Web.Http;
using System.Web.Http.Controllers;
using System.Web.Http.Filters;
using CorsWebAPI.Helpers;
using CorsWebAPI.Services;
using log4net;

namespace CorsWebAPI.Attributes
{
    public class SessionCheckAtrribute : AuthorizationFilterAttribute
    {
        private static readonly ILog Log = LogManager.GetLogger(typeof(SessionCheckAtrribute));

        private static readonly string CookieName = ConfigurationManager.AppSettings["SessionCookie"];

        public override void OnAuthorization(HttpActionContext actionContext)
        {
            var sessionId = GetSessionId(HttpContext.Current.Request);
            
            if (sessionId == null || DemoSessionManager.GetInstance().CheckSession(sessionId) == null)
            {
                // User does not have the proper permission for the action that has been requested
                throw new HttpResponseException(HttpStatusCode.Forbidden);
            }

            base.OnAuthorization(actionContext);
        }

        public static string GetSessionId(HttpRequest request)
        {
            var cookie = CookieHelper.GetCookie(HttpContext.Current.Request, CookieName);

            return cookie == null ? null : cookie.Value;
        }
    }
}