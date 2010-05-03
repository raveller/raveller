namespace MobiCentric.Incentives.DbTransform
{
    using System;
    using System.Linq;
    using Data;
    using FluentNHibernate.Cfg;
    using log4net;
    using Mappers;
    using NHibernate;
    using StructureMap;
    using StructureMap.Configuration.DSL;
    using StructureMap.Graph;
    using StructureMap.TypeRules;

    public class Bootstrapper
    {
        private static readonly ILog _log = LogManager.GetLogger(typeof (Bootstrapper));

        public void Bootstrap()
        {
            BootstrapContainer();

            ModelMapper.InitializeMapping();
        }


        private void BootstrapContainer()
        {
            try
            {
                ObjectFactory.Configure(x =>
                    {
                        x.For<ISessionFactory>()
                            .Singleton().Use(CreateSessionFactory);

                        x.For<ILocalDataContext>()
                            .HybridHttpOrThreadLocalScoped().Use<SqlLocalDataContext>();

                        x.For<IProviderDataContext>()
                            .HybridHttpOrThreadLocalScoped().Use<SqlProviderDataContext>();

                        /*
						x.For<SingletonInterface>()
							.Singleton().Use<SingletonClass>();

						x.For<HybridttpOrThreadLocalScopedInterface>()
							.HybridHttpOrThreadLocalScoped().Use<HybridttpOrThreadLocalScopedObject>();

						x.For<StandardInterface>().Use<StandardClass>();
                        */

                        x.Scan(scanner =>
                            {
                                scanner.TheCallingAssembly();
                                scanner.Convention<MatchingInterfaceConvention>();
                            });
                    });

                if (_log.IsDebugEnabled)
                    _log.Debug(ObjectFactory.WhatDoIHave());
            }
            catch (Exception ex)
            {
                LogManager.GetLogger(typeof (Bootstrapper)).Error("Failed to initialize container", ex);
            }
        }

        private static ISessionFactory CreateSessionFactory(IContext context)
        {
            return Fluently.Configure()
                .Mappings(m => m.FluentMappings.AddFromAssemblyOf<SqlConnectionFactory>())
                .BuildSessionFactory();
        }

        private class MatchingInterfaceConvention :
            IRegistrationConvention
        {
            public void Process(Type type, Registry registry)
            {
                if (!type.IsConcrete())
                    return;

                Type matchingInterface = type.GetInterfaces().Where(x => x.Name.EndsWith(type.Name)).FirstOrDefault();
                if (matchingInterface == null)
                    return;

                registry.For(matchingInterface).Use(type);
            }
        }
    }
}