using System.Collections.Generic;
using System.Linq;
using CorsWebAPI.Models;
using log4net;

namespace CorsWebAPI.Services
{
    public class DemoDataManager
    {
        private static readonly ILog Log = LogManager.GetLogger(System.Reflection.MethodBase.GetCurrentMethod().DeclaringType);
        
        private static DemoDataManager _instance;

        private readonly ICollection<ProductModel> _products = new List<ProductModel>();

        public static DemoDataManager GetInstance()
        {
            lock (Log)
            {
                if (_instance == null)
                    _instance = new DemoDataManager();
            }
            return _instance;
        }

        public IEnumerable<ProductModel> ReadProducts(bool admin)
        {
            if (admin)            
                return _products;
            
            return _products.Where(x => x.Unreleased == false && x.Discontinued == false);
        }


        private DemoDataManager()
        {
            _products.Add(new ProductModel
            {
                Title = "Premium Waffle",
                Description = "The best of what we have to offer.  Waffle with Syrup and Butter and Whipped Cream !",
                Price = 60,
                ProductCode = "PREMWAF2000",
                Quantity = 20
            });
            _products.Add(new ProductModel
            {
                Title = "Waffle",
                Description = "Entry Level Waffle for the Waffling novice",
                Price = 10,
                ProductCode = "EWAF2000",
                Quantity = 41
            });
            _products.Add(new ProductModel
            {
                Title = "Waffle + Butter",
                Description = "Waffle Plus Butter",
                Price = 15,
                ProductCode = "WAF",
                Quantity = 38
            });
            _products.Add(new ProductModel
            {
                Title = "Waffle Supreme",
                Description = "Waffle with Butter and Maple Syrup, our best seller!",
                Price = 23,
                ProductCode = "WAFSUPR3323",
                Quantity = 99,
            });
            _products.Add(new ProductModel
            {
                Title = "Zombie Waffle",
                Description = "This waffle has it all!  Waffles!  Butter!  Syrup!  Gummy Worms!",
                Price = 35,
                ProductCode = "ZMBEEWAF2000",
                Quantity = 20,
                Unreleased = true
            });
            _products.Add(new ProductModel
            {
                Title = "Burnt Waffle",
                Description = "Burnt waffles have many uses!  Take advantages of our mistakes!  Buy today!",
                Price = 5,
                ProductCode = "BRNTWAFXXXX",
                Quantity = 3000,
                Discontinued = true
            });
        }
    }
}