using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace DbWebAPI.Data.Models
{
    public class AccountModel
    {
        public string UserId       { get; set; }
        public string PasswordHash { get; set; }
        public int UserRole        { get; set; }
    }
}