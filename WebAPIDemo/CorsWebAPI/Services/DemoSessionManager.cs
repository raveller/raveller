using System;
using System.Collections.Generic;
using System.Configuration;
using System.Security.Cryptography;
using System.Text;
using CorsWebAPI.Models;
using log4net;

namespace CorsWebAPI.Services
{
    public class DemoSessionManager : IDemoSessionManager
    {
        private static readonly ILog Log = LogManager.GetLogger(System.Reflection.MethodBase.GetCurrentMethod().DeclaringType);
        
        private const string Separator = "|";
        private static DemoSessionManager _instance;

        private readonly IDictionary<string, IDemoSession> _sessions = new Dictionary<string, IDemoSession>();
        private readonly string _credentialSalt;
        private readonly IDictionary<string, AccountModel> _accounts = new Dictionary<string, AccountModel>();
        private readonly ISet<string> _logins= new HashSet<string>();

        public static DemoSessionManager GetInstance()
        {
            lock (Log)
            {
                if (_instance == null)
                    _instance = new DemoSessionManager();
            }
            return _instance;
        }
        private DemoSessionManager()
        {
            _credentialSalt = ConfigurationManager.AppSettings["CredentialSalt"];
            InitializeLogins();
        }

        public IDemoSession Login(LoginModel login)
        {
            var credentialHash = GenerateSha2PasswordHash(login);
        
            if (credentialHash == null || !_logins.Contains(credentialHash))
                return null;

            var session = new DemoSession(login.UserId);

            _sessions.Add(session.Id, session);

            return session;
        }

        public IDemoSession CheckSession(string sessionId)
        {
            if (String.IsNullOrEmpty(sessionId) || !_sessions.ContainsKey(sessionId))
                return null;

            var session = _sessions[sessionId];
            return session.Expiry >= DateTime.Now ? session : null;
        }

        public void LogOut(string sessionId)
        {
            if (String.IsNullOrEmpty(sessionId) || !_sessions.ContainsKey(sessionId))
                return ;

            _sessions.Remove(sessionId);
        }

        private void InitializeLogins()
        {
            var adminAccount = new AccountModel {UserId = "Admin", Administrator = true};
            var shopperAccount = new AccountModel { UserId = "Guest", Administrator = false };

            AddLogin(adminAccount, "Admin!2");
            AddLogin(shopperAccount, "Guest!2");
        }

        private void AddLogin(AccountModel account, string password)
        {
            _accounts.Add(account.UserId, account);
            _logins.Add(GenerateSha2PasswordHash(account.UserId, password));
        }


        protected string GenerateSha2PasswordHash(LoginModel login)
        {
            if (login == null)
                return null;
            return GenerateSha2PasswordHash(login.UserId, login.Password);
        }

        protected string GenerateSha2PasswordHash(string userId, string password)
        {
            if (userId == null || password == null || userId.Contains(Separator) || password.Contains(Separator))
                return null;

            var hashTool = new SHA256Managed();
            var saltedInput = userId + Separator + password + Separator + _credentialSalt;
            var saltedBytes = Encoding.UTF8.GetBytes(saltedInput);
            var encryptedBytes = hashTool.ComputeHash(saltedBytes);
            hashTool.Clear();
            var output = Convert.ToBase64String(encryptedBytes);
            return output;
        }

        public AccountModel ReadAccountInfo(string userId)
        {
            if (string.IsNullOrEmpty(userId) || !_accounts.ContainsKey(userId))
                return null;

            return _accounts[userId];
        }
    }
}