namespace MobiCentric.Incentives.DbTransform.Tests
{
    using System.IO;
    using System.Reflection;
    using log4net;
    using log4net.Appender;
    using log4net.Config;
    using log4net.Core;
    using log4net.Layout;
    using log4net.Repository.Hierarchy;
    using NUnit.Framework;
    using Test;

    public abstract class TestBase
    {
        private bool _establishFixtureContextCalled;
        private bool _establishContextCalled;
        private bool _tearDownContextCalled;
        private bool _tearDownFixtureContextCalled;

        [TestFixtureSetUp]
        public void TestFixtureSetup()
        {
            _establishFixtureContextCalled = false;
            BootstrapLogger();
            SetupLogger();
            EstablishFixtureContext();
            _establishFixtureContextCalled.ShouldBeTrue("EstablishFixtureContext chain is broken, verify all sub classes call base.EstablishFixtureContext()");
        }

        [SetUp]
        public void Setup()
        {
            _establishContextCalled = false;
            EstablishContext();
            _establishContextCalled.ShouldBeTrue("EstablishContext chain is broken, verify all sub classes call base.EstablishContext()");
        }

        [TearDown]
        public void Teardown()
        {
            _tearDownContextCalled = false;
            TearDownContext();
            _tearDownContextCalled.ShouldBeTrue("Teardown chain is broken, verify all sub classes call base.Teardown()");
        }

        [TestFixtureTearDown]
        public void TestFixtureTeardown()
        {
            _tearDownFixtureContextCalled = false;
            TearDownFixtureContext();
            _tearDownFixtureContextCalled.ShouldBeTrue("TestFixtureTeardown chain is broken, verify all sub classes call base.TestFixtureTeardown()");
        }

        private void BootstrapLogger()
        {
            const string logConfiguration = "log4net.config";
            string configurationPath = Path.Combine(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location), logConfiguration);
            XmlConfigurator.ConfigureAndWatch(new FileInfo(configurationPath));

            LogManager.GetLogger(typeof (Bootstrapper)).Info("AppDomain Started");
        }

        private void SetupLogger()
        {
            var defaultAppender = new TraceAppender
                {
                    Layout = new SimpleLayout(),
                    Threshold = Level.Warn
                };

            BasicConfigurator.Configure(defaultAppender);

            var mobiLogger = (Logger) LogManager.GetLogger("MobiCentric").Logger;

            var mobiAppender = new TraceAppender
                {
                    Layout = new SimpleLayout(),
                    Threshold = Level.All,
                };

            mobiLogger.AddAppender(mobiAppender);
        }

        protected virtual void EstablishFixtureContext()
        {
            _establishFixtureContextCalled = true;
        }

        protected virtual void EstablishContext()
        {
            _establishContextCalled = true;
        }

        protected virtual void TearDownContext()
        {
            _tearDownContextCalled = true;
        }

        protected virtual void TearDownFixtureContext()
        {
            _tearDownFixtureContextCalled = true;
        }
    }
}