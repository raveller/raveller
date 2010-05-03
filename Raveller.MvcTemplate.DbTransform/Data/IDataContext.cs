namespace MobiCentric.Incentives.DbTransform.Data
{
    using System;
    using System.Data;
    using NHibernate;

    public interface IDataContext :
        IDisposable
    {
        ICommandContext CreateCommand(string text);
        ICommandContext CreateCommand(string text, CommandType commandType);
        ICommandContext CreateCommand(string text, CommandType commandType, ITransaction transaction);

        ISession Session { get; }
    }
}