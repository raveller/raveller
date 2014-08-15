using System;
using System.Configuration;
using System.Net;
using System.Net.Http;
using System.Web;
using System.Web.Http;
using System.Web.Http.Cors;
using CorsWebAPI.Attributes;
using CorsWebAPI.Helpers;
using CorsWebAPI.Models;
using CorsWebAPI.Services;
using log4net;

namespace CorsWebAPI.Controllers
{
    public class SessionController : ApiController
    {
        private static readonly ILog Log = LogManager.GetLogger(System.Reflection.MethodBase.GetCurrentMethod().DeclaringType);

        private readonly string _cookieName = ConfigurationManager.AppSettings["SessionCookie"];

        private void SetCookie(IDemoSession demoSession)
        {
            var domain = HttpContext.Current.Request.Url.Host;

            #region IE Specific
            HttpContext.Current.Response.Headers.Add("P3P", "CP=\"CAO DSP COR CURa ADMa DEVa OUR IND PHY ONL UNI COM NAV INT DEM PRE\" policyref=\"/w3c/p3p.xml\"");
            #endregion

            HttpContext.Current.Response.Cookies.Add(new HttpCookie(_cookieName) { Value = demoSession.Id, Expires = demoSession.Expiry, Domain = domain});
        }

        private void RemoveCookie()
        {
            var domain = HttpContext.Current.Request.Url.Host;
            CookieHelper.RemoveCookie(HttpContext.Current.ApplicationInstance, _cookieName, domain);
        }


        #region v2

        [Route("check/v2")]
        public HttpResponseMessage Get()
        {
            return CheckSession();
        }

        [Route("login/v2")]
        public HttpResponseMessage Post([FromBody]LoginModel login)
        {
            return Login(login);
        }

        [Route("logout/v2")]
        public HttpResponseMessage Delete()
        {
            return Logout();
        }
        #endregion 
        #region v3

        [Route("check/v3")]
        [EnableCors(origins: "*", headers: "*", methods: "*", SupportsCredentials = true)]
        public HttpResponseMessage GetWithCors()
        {
            return CheckSession();
        }

        [Route("login/v3")]
        [EnableCors(origins: "*", headers: "*", methods: "*", SupportsCredentials = true)]
        public HttpResponseMessage PostWithCors([FromBody] LoginModel login)
        {
            return Login(login);
        }


        [Route("logout/v3")]
        [EnableCors(origins: "*", headers: "*", methods: "*", SupportsCredentials = true)]
        public HttpResponseMessage DeleteWithCors()
        {
            return Logout();
        }

        #endregion

        [HttpGet]
        public HttpResponseMessage CheckSession()
        {
            var sessionId = SessionCheckAtrribute.GetSessionId(HttpContext.Current.Request);
            if (sessionId == null)
                return Request.CreateErrorResponse(HttpStatusCode.Forbidden, "No Session");


            if (DemoSessionManager.GetInstance().CheckSession(sessionId) == null)
            {
                RemoveCookie();
                return Request.CreateErrorResponse(HttpStatusCode.Forbidden, "No Session");
            }

            return Request.CreateResponse(HttpStatusCode.OK, new {});
        }

        [HttpPost]
        public HttpResponseMessage Login([FromBody] LoginModel login)
        {
            if (login == null)
            {
                RemoveCookie();
                return Request.CreateErrorResponse(HttpStatusCode.BadRequest, "No input was provided.");
            }

            try
            {
                var session = DemoSessionManager.GetInstance().Login(login);

                if (session == null)
                {
                    RemoveCookie();
                    return Request.CreateErrorResponse(HttpStatusCode.Forbidden, "Credentials are invalid.");
                }

                SetCookie(session);
                return Request.CreateResponse(HttpStatusCode.OK, new { });
            }
            catch (Exception e)
            {
                Log.Error(e);

                RemoveCookie();
                return Request.CreateErrorResponse(HttpStatusCode.InternalServerError, "Exception on call.");
            }
        }

        [HttpDelete]
        public HttpResponseMessage Logout()
        {
            var sessionId = SessionCheckAtrribute.GetSessionId(HttpContext.Current.Request);
            if (sessionId != null)
            {
                DemoSessionManager.GetInstance().LogOut(sessionId);
            }

            RemoveCookie();
            return Request.CreateResponse(HttpStatusCode.OK, new { });
        }
    }
}
