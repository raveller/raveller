using System;
using System.Globalization;
using System.Web;

namespace CorsWebAPI.Helpers
{

    public class CookieHelper
    {
        public static HttpCookie GetCookie(HttpRequest request, string name)
        {
            if (request == null)
                return null;

            var cookies = request.Cookies;
            return FindCookie(cookies, name);
        }

        public static HttpCookie FindCookie(HttpCookieCollection cookies, string name)
        {
            if (cookies == null)
                return null;

            var count = cookies.Count;

            for (var i = 0; i < count; i++)
            {
                if (cookies[i] != null && String.Compare(cookies[i].Name, name, true, CultureInfo.InvariantCulture) == 0)
                    return cookies[i];
            }

            return null;
        }

        public static void RemoveCookie(HttpApplication context, string cookieName, string domain)
        {
            if (context == null)
                return;

            context.Request.Cookies.Remove(cookieName);

            if (context.Response.Cookies[cookieName] == null)
                return;

            context.Response.Cookies[cookieName].Value = string.Empty;
            context.Response.Cookies[cookieName].Expires = DateTime.Now - TimeSpan.FromDays(1);
            context.Response.Cookies[cookieName].Domain = domain;
        }
    }
}