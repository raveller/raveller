using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace CorsWebAPI.Models
{
    public class ProductModel
    {
        public string Title { get; set; }
        public string ProductCode { get; set; }
        public decimal Price { get; set; }
        public int Quantity { get; set; }
        public string Description { get; set; }
        public bool Discontinued { get; set; }
        public bool Unreleased { get; set; }
    }
}