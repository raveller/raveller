namespace MobiCentric.Incentives.DbTransform.Test
{
    using System.Diagnostics;
    using StructureMap.Pipeline;
    using Tests;

    public abstract class BootstrappedTestBase : TestBase
    {
        private static bool _alreadyBootstrapped;

        protected override void EstablishFixtureContext()
        {
            base.EstablishFixtureContext();

            Bootstrap();
        }

        protected override void TearDownFixtureContext()
        {
            new ThreadLocalStorageLifecycle().EjectAll();

            base.TearDownFixtureContext();
        }

        protected static void Bootstrap()
        {
            if (_alreadyBootstrapped)
                return;

            Trace.WriteLine("Bootstrapping.");
            new Bootstrapper().Bootstrap();

            _alreadyBootstrapped = true;
        }
    }
}