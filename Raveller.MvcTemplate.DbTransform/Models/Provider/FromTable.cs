namespace MobiCentric.Incentives.DbTransform.Models.Provider
{
    using FluentNHibernate.Mapping;

    public class FromTable
    {
        public virtual string KeyField { get; set; }
        public virtual string DataField1 { get; set; }
        public virtual int DataField2 { get; set; }
    }

    public class FromTableMap : ClassMap<FromTable>
    {
        public FromTableMap()
        {
            Table("tbl_FromTable");
            Id(x => x.KeyField);

            Map(x => x.DataField1, "DataFeeld1");
            Map(x => x.DataField2, "DaterFieldtoo");
        }
    }
}