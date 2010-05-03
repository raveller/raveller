namespace MobiCentric.Incentives.DbTransform.Data
{
    using System.Data.SqlClient;
    using NHibernate;

    public class SqlLocalDataContext :
        SqlDataContext,
        ILocalDataContext
    {
        private readonly ISqlConnectionFactory _connectionFactory;

        public SqlLocalDataContext(ISqlConnectionFactory connectionFactory, ISessionFactory sessionFactory)
            : base(sessionFactory)
        {
            _connectionFactory = connectionFactory;
        }

        protected override SqlConnection GetConnection()
        {
            return _connectionFactory.GetConnection("Local");
        }
    }
}