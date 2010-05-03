namespace MobiCentric.Incentives.DbTransform.Data
{
    using System;
    using System.Data;
    using System.Data.SqlClient;

    public interface ICommandContext :
        IDisposable
    {
        void AddParameter(string name, DbType type, ParameterDirection direction);
        void AddParameter(string name, DbType type, int size, ParameterDirection direction);
        void AddParameter<T>(string name, DbType type, ParameterDirection direction, T value);
        void Execute();
        SqlDataReader ExecuteReader();
        Object ExecuteScalar();
        T GetParameterValue<T>(string name);
        int ExecuteNonQuery();
    }
}