using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using DbWebAPI.Data.Models;
using log4net;

namespace DbWebAPI.Data
{
    public class AdoDataManager : IDataManager
    {
        private static readonly ILog Log = LogManager.GetLogger(System.Reflection.MethodBase.GetCurrentMethod().DeclaringType);

        public string ConnectionString { get; set; }

        private AdoDataContext AdoContext { get; set; }

        public IDataContext Context
        {
            get
            {
                if (AdoContext == null)
                    AdoContext = AdoDataContext.Create(ConnectionString);

                return AdoContext;
            }
        }
    

        public IEnumerable<ProductModel> ReadProducts(int userRole)
        {
            if (AdoContext == null)
                yield break;

            using (var command = new SqlCommand("demosp_ReadProducts", AdoContext.Connection))
            {
                command.CommandType = CommandType.StoredProcedure;
                command.Parameters.Add(new SqlParameter("@userRole", userRole));

                using (var reader = command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        var product = new ProductModel
                        {
                            ProductCode = Convert.ToString(reader["ProductCode"]),
                            Title = Convert.ToString(reader["Title"]),
                            Price = Convert.ToDecimal(reader["Price"]),
                            Quantity = Convert.ToInt32(reader["Quantity"]),
                            Description = Convert.ToString(reader["Description"]),
                            Active = Convert.ToBoolean(reader["Active"]),
                            Released = Convert.ToBoolean(reader["Released"]),
                        };

                        yield return product;
                    }
                }
            }
        }

        public bool AddAccount(AccountModel account)
        {
            if (AdoContext == null || account == null || string.IsNullOrEmpty(account.UserId) || string.IsNullOrEmpty(account.PasswordHash))
                return false;

            try
            {
                using (var command = new SqlCommand("demosp_AddAccount", AdoContext.Connection))
                {
                    command.CommandType = CommandType.StoredProcedure;
                    command.Parameters.Add(new SqlParameter("@userId", account.UserId));
                    command.Parameters.Add(new SqlParameter("@passHash", account.PasswordHash));
                    command.Parameters.Add(new SqlParameter("@userRole", account.UserRole));

                    // If there was no processResultRow Action provided, then we execute a non-query
                    command.ExecuteNonQuery();
                }
                return true;
            }
            catch (Exception ex)
            {
                Log.Error("Exception occurred adding Account", ex);
                return false;
            }
        }

        public bool InsertProduct(ProductModel product)
        {
            return UpsertProduct(product);
        }

        public bool UpdateProduct(ProductModel product)
        {
            return UpsertProduct(product);
        }

        public bool UpsertProduct(ProductModel product)
        {
            if (AdoContext == null || product == null || string.IsNullOrEmpty(product.ProductCode))
                return false;

            try
            {
                using (var command = new SqlCommand("demosp_UpsertProduct", AdoContext.Connection))
                {
                    command.CommandType = CommandType.StoredProcedure;
                    command.Parameters.Add(new SqlParameter("@productCode", product.ProductCode));
                    command.Parameters.Add(new SqlParameter("@title", product.Title));
                    command.Parameters.Add(new SqlParameter("@description", product.Description));
                    command.Parameters.Add(new SqlParameter("@price", product.Price));
                    command.Parameters.Add(new SqlParameter("@released", product.Released));

                    // If there was no processResultRow Action provided, then we execute a non-query
                    command.ExecuteNonQuery();
                }
            }
            catch (Exception ex)
            {
                Log.Error("Exception occurred adding Account", ex);
            }
            return true;
        }

        public bool DeleteProduct(string productCode)
        {
            if (string.IsNullOrEmpty(productCode))
                return false;

            try
            {
                using (var command = new SqlCommand("demosp_DeactivateProduct", AdoContext.Connection))
                {
                    command.CommandType = CommandType.StoredProcedure;
                    command.Parameters.Add(new SqlParameter("@productCode", productCode));

                    // If there was no processResultRow Action provided, then we execute a non-query
                    command.ExecuteNonQuery();
                }
            }
            catch (Exception ex)
            {
                Log.Error("Exception occurred adding Account", ex);
            }
            return true;
        }
    }
}
