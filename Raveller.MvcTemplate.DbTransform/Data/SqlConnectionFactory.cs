namespace MobiCentric.Incentives.DbTransform.Data
{
    using System;
    using System.Configuration;
	using System.Data.SqlClient;
	using System.Reflection;
	using log4net;

	public class SqlConnectionFactory :
		ISqlConnectionFactory
	{
		private static readonly ILog _log = LogManager.GetLogger(typeof (SqlConnectionFactory));

		public SqlConnection GetConnection(string connectionName)
		{
			return CreateConnection(GetConnectionString(connectionName));
		}

	    private static string GetConnectionString(string connectionName)
		{
			ConnectionStringSettings connectionSettings = ConfigurationManager.ConnectionStrings[connectionName];
			if (connectionSettings == null)
			{
				var map = new ExeConfigurationFileMap
					{
						ExeConfigFilename = Assembly.GetExecutingAssembly().Location + ".config"
					};

				_log.InfoFormat("Using Configuration File: {0}", map.ExeConfigFilename);

				var config = ConfigurationManager.OpenMappedExeConfiguration(map, ConfigurationUserLevel.None);

				connectionSettings = config.ConnectionStrings.ConnectionStrings[connectionName];
			}

			if (connectionSettings == null)
				throw new ConfigurationErrorsException("There are no configuration string configured");

			string connectionString = connectionSettings.ConnectionString;

			return connectionString;
		}

		private static SqlConnection CreateConnection(string connectionString)
		{
			try
			{
				var connection = new SqlConnection(connectionString);
				connection.Open();

				return connection;
			}
			catch (Exception ex)
			{
				throw new Exception(string.Format("Error creating connection to \"{0}\"", connectionString), ex);
			}
		}
	}
}