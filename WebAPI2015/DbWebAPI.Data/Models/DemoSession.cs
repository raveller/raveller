using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace DbWebAPI.Data.Models
{
    public class DemoSession : IDemoSession
    {
        public string Id { get; private set; }
        public DateTime Expiry { get; private set; }
        public string UserId { get; private set; }

        public DemoSession(string userId)
        {
            Id = Guid.NewGuid().ToString().Replace("-", "").Replace("{", "").Replace("}", "");
            Expiry = DateTime.Now + TimeSpan.FromHours(8);
            UserId = userId;
        }
    }
}