namespace MobiCentric.Incentives.DbTransform.Models.Local
{
    using FluentNHibernate.Mapping;

    public class ToTable
    {
        public virtual string KeyField { get; set; }
        public virtual string DataField1 { get; set; }
        public virtual int DataField2 { get; set; }
    }

    public class ToTableMap : ClassMap<ToTable>
    {
        public ToTableMap()
        {
            Table("tbl_ToTable");
            Id(x => x.KeyField);

            Map(x => x.DataField1, "DataFieldONE");
            Map(x => x.DataField2, "DataFieldtoo");
        }
    }
}