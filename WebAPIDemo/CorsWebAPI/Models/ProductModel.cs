﻿using System;
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

        protected bool Equals(ProductModel other)
        {
            return string.Equals(ProductCode, other.ProductCode);
        }

        public override bool Equals(object obj)
        {
            if (ReferenceEquals(null, obj)) return false;
            if (ReferenceEquals(this, obj)) return true;
            if (obj.GetType() != this.GetType()) return false;
            return Equals((ProductModel)obj);
        }

        public override int GetHashCode()
        {
            return (ProductCode != null ? ProductCode.GetHashCode() : 0);
        }
    }
}