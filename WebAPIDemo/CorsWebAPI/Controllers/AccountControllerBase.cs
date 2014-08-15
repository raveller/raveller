using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web;
using System.Web.Http;
using System.Web.Http.Controllers;
using CorsWebAPI.Attributes;
using CorsWebAPI.Helpers;
using CorsWebAPI.Models;
using CorsWebAPI.Services;
using log4net;

namespace CorsWebAPI.Controllers
{
    public class AccountControllerBase : ApiController
    {
        private static readonly ILog Log = LogManager.GetLogger(typeof(SessionCheckAtrribute));

        private AccountModel _account;

        protected AccountModel Account
        {
            get
            {
                if (_account == null)
                {
                    var sessionId = SessionCheckAtrribute.GetSessionId(HttpContext.Current.Request);
                    if (sessionId != null)
                    {
                        var session = DemoSessionManager.GetInstance().CheckSession(sessionId);
                        if (session != null)
                            _account = DemoSessionManager.GetInstance().ReadAccountInfo(session.UserId);
                    }
                }
                return _account;
            }
        }
    }
}
