using System;

namespace CorsWebAPI.Models
{
    public interface IDemoSession
    {
        string      Id { get; }
        DateTime    Expiry { get; }
        string      UserId { get; }
    }
}
