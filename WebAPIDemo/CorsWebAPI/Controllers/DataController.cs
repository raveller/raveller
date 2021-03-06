﻿using System.Net;
using System.Net.Http;
using System.Web.Http;
using System.Web.Http.Cors;
using CorsWebAPI.Attributes;
using CorsWebAPI.Attributes.Portal.Filters;
using CorsWebAPI.Models;
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
        public HttpResponseMessage GetAnything()
        {
            if (Account == null)
                return Request.CreateErrorResponse(HttpStatusCode.Forbidden, "Request not allowed");

            return Request.CreateResponse(DemoDataManager.GetInstance().ReadProducts(Account.Administrator));
        }

        #endregion
        [SessionCheckAtrribute]
        [Route("product/v3")]
        public HttpResponseMessage Post([FromBody] ProductModel product)
        {
            if (DemoDataManager.GetInstance().InsertProduct(product))
                return Request.CreateResponse(HttpStatusCode.OK, product);

            return Request.CreateErrorResponse(HttpStatusCode.BadRequest, "This was a bad product request");
        }
    }
}
