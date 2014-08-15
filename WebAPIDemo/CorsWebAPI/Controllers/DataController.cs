using System.Net;
using System.Net.Http;
using System.Web.Http;
using System.Web.Http.Cors;
using CorsWebAPI.Attributes;
using CorsWebAPI.Attributes.Portal.Filters;
using CorsWebAPI.Services;

namespace CorsWebAPI.Controllers
{
    public class DataController : AccountControllerBase
    {
        #region v0

        [Route("product/v0")]
        public HttpResponseMessage Get()
        {
            return Request.CreateResponse(DemoDataManager.GetInstance().ReadProducts(false));
        }

        #endregion
        #region v1

        [EnableCors(origins: "*", headers: "*", methods: "*")]
        [Route("product/v1")]
        public HttpResponseMessage GetCors()
        {
            return Request.CreateResponse(DemoDataManager.GetInstance().ReadProducts(false));
        }

        #endregion
        #region v2

        [SessionCheckAtrribute]
        [Route("product/v2")]
        public HttpResponseMessage GetSession()
        {
            if (Account == null)
                return Request.CreateErrorResponse(HttpStatusCode.Forbidden, "Request not allowed");

            return Request.CreateResponse(DemoDataManager.GetInstance().ReadProducts(Account.Administrator));
        }

        #endregion
        #region v3

        [EnableCors(origins: "*", headers: "*", methods: "*", SupportsCredentials = true)]
        [SessionCheckAtrribute]
        [Route("product/v3")]
        public HttpResponseMessage GetSessionCors()
        {
            if (Account == null)
                return Request.CreateErrorResponse(HttpStatusCode.Forbidden, "Request not allowed");

            return Request.CreateResponse(DemoDataManager.GetInstance().ReadProducts(Account.Administrator));
        }

        #endregion
        #region v4

        [EnableCors(origins: "http://demo.huck13.com", headers: "content-type,accept,cookie", methods: "OPTIONS,GET", SupportsCredentials = true)]
        [SessionCheckAtrribute]
        [Route("product/v4")]
        public HttpResponseMessage GetSessionWtihNamedOrigin()
        {
            if (Account == null)
                return Request.CreateErrorResponse(HttpStatusCode.Forbidden, "Request not allowed");

            return Request.CreateResponse(DemoDataManager.GetInstance().ReadProducts(Account.Administrator));
        }

        #endregion
    }
}
