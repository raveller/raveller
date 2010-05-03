namespace MobiCentric.Incentives.DbTransform.Data
{
    using System.Data.SqlClient;
    using NHibernate;

    public class SqlProviderDataContext :
        SqlDataContext,
        IProviderDataContext
    {
        private readonly ISqlConnectionFactory _connectionFactory;

        public SqlProviderDataContext(ISqlConnectionFactory connectionFactory, ISessionFactory sessionFactory)
            : base(sessionFactory)
        {
            _connectionFactory = connectionFactory;
        }

        protected override SqlConnection GetConnection()
        {
            return _connectionFactory.GetConnection("Provider");
        }
    }
}