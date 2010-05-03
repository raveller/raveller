namespace MobiCentric.Incentives.DbTransform.Data
{
    using System;
    using System.Data;
    using System.Data.SqlClient;
    using NHibernate;

    public abstract class SqlDataContext :
        IDataContext
    {
        private readonly ISessionFactory _sessionFactory;
        private SqlConnection _connection;
        private volatile bool _disposed;
        private ISession _session;

        protected SqlDataContext(ISessionFactory sessionFactory)
        {
            _sessionFactory = sessionFactory;
        }

        public SqlConnection Connection
        {
            get
            {
                if (_connection != null)
                    return _connection;

                _connection = GetConnection();

                return _connection;
            }
        }

        public ICommandContext CreateCommand(string text)
        {
            var command = new SqlCommandContext(Connection, text, CommandType.StoredProcedure);

            return command;
        }

        public ICommandContext CreateCommand(string text, CommandType commandType)
        {
            var command = new SqlCommandContext(Connection, text, commandType);

            return command;
        }

        public ICommandContext CreateCommand(string text, CommandType commandType, ITransaction transaction)
        {
            var command = new SqlCommandContext(Connection, text, commandType, transaction);

            return command;
        }

        public ISession Session
        {
            get
            {
                if (_session != null)
                    return _session;

                _session = _sessionFactory.OpenSession(Connection);

                return _session;
            }
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        ~SqlDataContext()
        {
            Dispose(false);
        }

        public virtual void Dispose(bool disposing)
        {
            if (!disposing || _disposed) return;

            if (_session != null)
            {
                _session.Close();
                _session.Dispose();
                _session = null;
            }

            if (_connection != null)
            {
                _connection.Close();
                _connection.Dispose();
                _connection = null;
            }

            _disposed = true;
        }

        protected abstract SqlConnection GetConnection();
    }
}