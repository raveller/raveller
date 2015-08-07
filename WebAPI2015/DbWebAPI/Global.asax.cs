using System.Web;
using System.Web.Http;
using System.Web.Mvc;
using DBWebAPI.App_Start;

namespace DbWebAPI
{
    public class WebApiApplication : HttpApplication
    {
        protected void Application_Start()
        {
            // Add this code, if not present.
            AreaRegistration.RegisterAllAreas();
            
            GlobalConfiguration.Configure(WebApiConfig.Register);
        }
    }
}
