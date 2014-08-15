using CorsWebAPI.Models;

namespace CorsWebAPI.Services
{
    public interface IDemoSessionManager
    {
        IDemoSession Login(LoginModel model);
        IDemoSession CheckSession(string sessionId);
        void LogOut(string sessionId);
    }
}