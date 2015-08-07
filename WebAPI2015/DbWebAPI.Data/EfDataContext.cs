using DbWebAPI.Data.Entities;

namespace DbWebAPI.Data
{
    public class EfDataContext : IDataContext
    {
        public DemoDbDataEntities Db { get; private set; }

        public static EfDataContext Create()
        {
            var context = new EfDataContext {Db = new DemoDbDataEntities()};

            return context;
        }

        public void Dispose()
        {
            Db.Dispose();
        }
    }
}
