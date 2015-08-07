using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Web;

namespace DBWebAPI.Helpers
{
    public sealed class HashHelper
    {
        private const string Separator = "|";

        public static string GenerateSha2PasswordHash(string userId, string password, string credentialSalt)
        {
            if (userId == null || password == null || userId.Contains(Separator) || password.Contains(Separator))
                return null;

            var hashTool = new SHA256Managed();
            var saltedInput = userId + Separator + password + Separator + credentialSalt;
            var saltedBytes = Encoding.UTF8.GetBytes(saltedInput);
            var encryptedBytes = hashTool.ComputeHash(saltedBytes);
            hashTool.Clear();
            var output = Convert.ToBase64String(encryptedBytes);
            return output;
        }
    }
}