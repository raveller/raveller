using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DbWebAPI.Data
{
    public class AdoDataContext : IDataContext
    {
        public SqlConnection Connection { get; private set; }

        public static AdoDataContext Create(string connectionString)
        {
            var context = new AdoDataContext { Connection = new SqlConnection(connectionString) };

            context.Connection.Open();

            return context;
        }

        public void Dispose()
        {
            if (Connection == null)
                return;

            Connection.Close();
            Connection.Dispose();
        }
    }
}
