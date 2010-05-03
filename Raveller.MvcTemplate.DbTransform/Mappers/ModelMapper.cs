namespace MobiCentric.Incentives.DbTransform.Mappers
{
    using AutoMapper;
    using Models.Local;
    using Models.Provider;

    public class ModelMapper
    {
        public static void InitializeMapping()
        {
            Mapper.CreateMap<FromTable, ToTable>()
                .ForMember(d => d.DataField1, o => o.MapFrom(s => s.DataField1))
                .ForMember(d => d.DataField2, o => o.MapFrom(s => s.DataField2))
                .ForMember(d => d.KeyField, o => o.Ignore());
        }
    }
}
