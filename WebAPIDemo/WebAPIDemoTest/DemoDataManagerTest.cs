using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CorsWebAPI.Models;
using CorsWebAPI.Services;
using NUnit.Framework;

namespace WebAPIDemoTest
{
    [TestFixture]
    public class DemoDataManagerTest
    {

        [Test]
        public void VerifyAddItem()
        {
            var manager = DemoDataManager.GetInstance();
            manager.InsertProduct(new ProductModel {ProductCode = "WAFLEE", Title = "Southern Waffle General Charger"});

            Assert.IsTrue(manager.ReadProducts(false).Contains(new ProductModel { ProductCode = "WAFLEE"}));

        }

    }
}
