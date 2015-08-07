using System.Configuration;
using System.Diagnostics;
using System.Linq;
using DbWebAPI.Data;
using DbWebAPI.Data.Models;
using NUnit.Framework;

namespace WebAPIDemoTest
{
    [TestFixture]
    public class DemoDataManagerTest
    {
        [Test]
        public void VerifyAddAdoItem()
        {
            IDataManager manager = new AdoDataManager
                                       {
                                           ConnectionString =
                                               ConfigurationManager.ConnectionStrings["DEMODB"]
                                               .ConnectionString
                                       };

            using (manager.Context)
            {
                manager.InsertProduct(new ProductModel
                                          {
                                              ProductCode = "WAFLEE",
                                              Title = "Southern Waffle General Charger"
                                          });

                Assert.IsTrue(manager.ReadProducts(10000).Contains(new ProductModel {ProductCode = "WAFLEE"}));
            }
        }

        [Test]
        public void VerifyReadAdoItems()
        {
            IDataManager manager = new AdoDataManager
                                       {
                                           ConnectionString =
                                               ConfigurationManager.ConnectionStrings["DEMODB"]
                                               .ConnectionString
                                       };
                                              
            using (manager.Context)
            {
                foreach (var item in manager.ReadProducts(0))
                {
                    Trace.WriteLine(item.ProductCode);
                }
            }
        }

        [Test]
        public void VerifyAddEfItem()
        {

            IDataManager manager = new EfDataManager();
            

            using (manager.Context)
            {
                manager.InsertProduct(new ProductModel
                {
                    ProductCode = "WAFLEE",
                    Title = "Southern Waffle General Charger"
                });

                Assert.IsTrue(manager.ReadProducts(10000).Contains(new ProductModel { ProductCode = "WAFLEE" }));
            }
        }
        [Test]
        public void VerifyEfReadProducts()
        {
            IDataManager manager = new EfDataManager();
            
            using (manager.Context)
            {
                foreach (var item in manager.ReadProducts(0))
                {
                    Trace.WriteLine(item.ProductCode);
                }
            }
        }

        [Test]
        public void VerifyEfReadProductsAgain()
        {
            IDataManager manager = new EfDataManager();

            using (manager.Context)
            {
                foreach (var item in manager.ReadProducts(0))
                {
                    Trace.WriteLine(item.ProductCode);
                }
            }
        }
    }
}
