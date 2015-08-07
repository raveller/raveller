using System;
using System.Collections.Generic;
using DbWebAPI.Data.Models;

namespace DbWebAPI.Data
{
    public interface IDataManager
    {
        IDataContext Context { get; }

        IEnumerable<ProductModel> ReadProducts(int userRole);

        bool InsertProduct(ProductModel product);

        bool UpdateProduct(ProductModel product);

        bool DeleteProduct(string productCode);
    }
}
