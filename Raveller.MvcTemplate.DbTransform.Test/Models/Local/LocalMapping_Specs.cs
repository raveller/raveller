using System;

namespace MobiCentric.Incentives.DbTransform.Test.Models.Local
{
    using Data;
    using NUnit.Framework;
    using StructureMap;

    [TestFixture]
    public class LocalMapping_Specs : BootstrappedTestBase
    {
        private ILocalDataContext _context;

        protected override void EstablishContext()
        {
            base.EstablishContext();

            _context = ObjectFactory.GetInstance<ILocalDataContext>();
        }

        [Test]
        public void AllNHibernateMappingsAreOkay()
        {
            var allClassMetadata = _context.Session.SessionFactory.GetAllClassMetadata();
            bool allPassed = true;

            foreach (var entry in allClassMetadata)
            {
                if (!entry.Key.Contains("MobiCentric.DbTransform.Models.Local")) continue;

                try
                {
                    _context.Session.CreateCriteria(entry.Key)
                         .SetMaxResults(0).List();
                }
                catch (Exception)
                {
                    allPassed = false;
                }

            }
            Assert.IsTrue(allPassed);
        }
    }
}
