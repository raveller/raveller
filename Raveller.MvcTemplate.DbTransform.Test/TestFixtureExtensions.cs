namespace MobiCentric.Incentives.DbTransform.Test
{
    using NUnit.Framework;

    public static class TestFixtureExtensions
    {
        public static void ShouldBeTrue(this bool condition)
        {
            Assert.IsTrue(condition);
        }

        public static void ShouldBeTrue(this bool condition, string message)
        {
            Assert.IsTrue(condition, message);
        }

        public static void ShouldBeFalse(this bool condition)
        {
            Assert.IsFalse(condition);
        }
    }
}