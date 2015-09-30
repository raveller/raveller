using System;
using System.Collections.Generic;
using System.Configuration;
using System.Net;
using System.Net.Http;
using System.Web.Http;
using DbWebAPI.Data;
using DbWebAPI.Data.Models;

namespace DbWebAPI.Controllers
{
    public class ProductController : ApiController
    {
        
        private IDataManager DataManager { get; set; }
        private IDataContext DataContext { get; set; }

        public ProductController()
        {
            if (ConfigurationManager.AppSettings["DataAccess"].ToUpper() == "ADO")
                DataManager = new AdoDataManager
                                           {
                                               ConnectionString =
                                                   ConfigurationManager.ConnectionStrings["DEMODB"]
                                                   .ConnectionString
                                           };
            else
                DataManager = new EfDataManager();

            DataContext = DataManager.Context;
        }

        [Route("product")]
        [HttpGet]
        public IEnumerable<ProductModel> Read()
        {
            try
            {
                return DataManager.ReadProducts(0);
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        [Route("product")]
        public HttpResponseMessage Post([FromBody] ProductModel product)
        {
            if (DataManager.InsertProduct(product))
                return Request.CreateResponse(HttpStatusCode.OK, product);

            return Request.CreateErrorResponse(HttpStatusCode.NoContent, "This was a bad product request");
        }

        [Route("product")]
        public HttpResponseMessage Put([FromBody] ProductModel product)
        {
            if (DataManager.UpdateProduct(product))
                return Request.CreateResponse(HttpStatusCode.OK, product);

            return Request.CreateErrorResponse(HttpStatusCode.NoContent, "This was a bad product request");
        }

        [Route("product/{productCode}")]
        public HttpResponseMessage Delete(string productCode)
        {
            using (DataManager.Context)
            {
                if (DataManager.DeleteProduct(productCode))
                    return Request.CreateResponse(HttpStatusCode.OK, "Deleted");
            }

            return Request.CreateErrorResponse(HttpStatusCode.NoContent, "Delete was unsuccessful");
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                DataContext.Dispose();
            }
            base.Dispose(disposing);
        }
    }
}
