namespace MobiCentric.Incentives.DbTransform.Data
{
    using System;
    using System.Data;
    using System.Data.SqlClient;
    using log4net;
    using NHibernate;

    public class SqlCommandContext :
        ICommandContext
    {
        private static readonly ILog _log = LogManager.GetLogger("RelayHealth.SQL");
        private SqlCommand _command;
        private SqlConnection _connection;
        private volatile bool _disposed;

        public SqlCommandContext(SqlConnection connection, string text, CommandType commandType)
        {
            _connection = connection;
            _command = new SqlCommand(text, connection)
                {
                    CommandTimeout = 120,
                    CommandType = commandType
                };
        }

        public SqlCommandContext(SqlConnection connection, string text, CommandType commandType, ITransaction transaction)
        {
            _connection = connection;
            _command = new SqlCommand(text, connection)
                {
                    CommandTimeout = 120,
                    CommandType = commandType
                };
            transaction.Enlist(_command);
        }

        public void AddParameter(string name, DbType type, ParameterDirection direction)
        {
            var parameter = new SqlParameter
                {
                    ParameterName = name,
                    DbType = type,
                    Direction = direction
                };

            _command.Parameters.Add(parameter);
        }

        public void AddParameter(string name, DbType type, int size, ParameterDirection direction)
        {
            var parameter = new SqlParameter
                {
                    ParameterName = name,
                    DbType = type,
                    Size = size,
                    Direction = direction
                };

            _command.Parameters.Add(parameter);
        }

        public void AddParameter<T>(string name, DbType type, ParameterDirection direction, T value)
        {
            var parameter = new SqlParameter
                {
                    ParameterName = name,
                    DbType = type,
                    Direction = direction,
                    Value = value,
                };

            _command.Parameters.Add(parameter);
        }

        public void Execute()
        {
            _log.DebugFormat("{0} {1}", _command.CommandType, _command.CommandText);

            if (_connection.State != ConnectionState.Open)
            {
                _log.DebugFormat("Reconnecting to {0} - {1}", _connection.DataSource, _connection.Database);
                _connection.Open();
            }

            _command.ExecuteNonQuery();
        }

        public int ExecuteNonQuery()
        {
            _log.DebugFormat("{0} {1}", _command.CommandType, _command.CommandText);

            if (_connection.State != ConnectionState.Open)
            {
                _log.DebugFormat("Reconnecting to {0} - {1}", _connection.DataSource, _connection.Database);
                _connection.Open();
            }

            return (_command.ExecuteNonQuery());
        }

        public Object ExecuteScalar()
        {
            _log.DebugFormat("{0} {1}", _command.CommandType, _command.CommandText);

            if (_connection.State != ConnectionState.Open)
            {
                _log.DebugFormat("Reconnecting to {0} - {1}", _connection.DataSource, _connection.Database);
                _connection.Open();
            }

            return (_command.ExecuteScalar());
        }

        public SqlDataReader ExecuteReader()
        {
            _log.DebugFormat("{0} {1}", _command.CommandType, _command.CommandText);

            if (_connection.State != ConnectionState.Open)
            {
                _log.DebugFormat("Reconnecting to {0} - {1}", _connection.DataSource, _connection.Database);
                _connection.Open();
            }

            return _command.ExecuteReader();
        }

        public T GetParameterValue<T>(string name)
        {
            SqlParameter parameter = _command.Parameters[name];
            if (parameter == null)
                throw new ArgumentException("No parameter named " + name + " was found", "name");

            return (T) parameter.Value;
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        ~SqlCommandContext()
        {
            Dispose(false);
        }

        public virtual void Dispose(bool disposing)
        {
            if (!disposing || _disposed) return;

            _command.Dispose();
            _command = null;

            _disposed = true;
        }
    }
}