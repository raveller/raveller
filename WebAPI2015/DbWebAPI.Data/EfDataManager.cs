using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using DbWebAPI.Data.Entities;
using DbWebAPI.Data.Models;
using log4net;

namespace DbWebAPI.Data
{
    public class EfDataManager : IDataManager
    {
        private static readonly ILog Log = LogManager.GetLogger(System.Reflection.MethodBase.GetCurrentMethod().DeclaringType);

        private EfDataContext EfContext { get; set; }
        private DemoDbDataEntities Db { get { return EfContext == null ? null : EfContext.Db; } }

        public IDataContext Context {
            get {
                EfContext = EfDataContext.Create();
                return EfContext;
            }
        }

        public IEnumerable<ProductModel> ReadProducts(int userRole)
        {
            try
            {
                var released = new [] { true, userRole < 9999 };
                var active = new [] { true, userRole < 999 };

                return from product in Db.Products
                            where released.Contains(product.Released) && active.Contains(product.Active)
                            orderby product.Title
                            select new ProductModel
                                    {
                                        Active = product.Active,
                                        Description = product.Description,
                                        Price = product.Price,
                                        ProductCode = product.ProductCode,
                                        Quantity = product.Quantity,
                                        Released = product.Released,
                                        Title = product.Title
                                    };
                
            }
            catch (Exception e)
            {
                Log.Error("Error reading products", e);
                return null;
            }
        }

        public bool InsertProduct(ProductModel product)
        {
            if (product == null)
                return false;

            using (Db.Database.BeginTransaction())
            {
                var matches = (from p in Db.Products
                               where p.ProductCode == product.ProductCode
                               select p.ProductCode).Count();
                if (matches > 0)
                    return false;

                Db.Products.Add(new Product
                                    {
                                        ProductCode = product.ProductCode,
                                        Title = product.Title,
                                        Active = true,
                                        Description = product.Description,
                                        Price = product.Price,
                                        Quantity = product.Quantity,
                                        Released = product.Released
                                    });
                Db.SaveChanges();
            }
            return true;
        }

        public bool UpdateProduct(ProductModel productDto)
        {
            if (productDto == null)
                return false;

            using (Db.Database.BeginTransaction())
            {
                var products = from p in Db.Products
                               where p.ProductCode == productDto.ProductCode
                               select p;

                if (products.Count() != 1)
                    return false;

                var product = products.First();
                
                product.Title = productDto.Title;
                product.Active = productDto.Active;
                product.Description = productDto.Title;
                product.Price = productDto.Price;
                product.Quantity = productDto.Quantity;
                product.Released = productDto.Released;

                Db.Entry(product).State = EntityState.Modified;

                Db.SaveChanges();

                return true;
            }
        }

        public bool DeleteProduct(string productCode)
        {

            if (string.IsNullOrEmpty(productCode))
                return false;

            using (Db.Database.BeginTransaction())
            {
                var products = from p in Db.Products
                               where p.ProductCode == productCode
                               select p;

                if (products.Count() != 1)
                    return false;

                var product = products.First();

                product.Active = false;

                Db.SaveChanges();

                return true;
            }
        }
    }
}
