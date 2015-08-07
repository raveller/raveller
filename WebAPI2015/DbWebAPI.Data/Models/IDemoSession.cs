using System;

namespace DbWebAPI.Data.Models
{
    public interface IDemoSession
    {
        string      Id { get; }
        DateTime    Expiry { get; }
        string      UserId { get; }
    }
}
