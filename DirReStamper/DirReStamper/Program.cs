using System;
using System.IO;

namespace DirReStamper
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args == null || args.Length < 0 || !Directory.Exists(args[0]))
            {
                Console.WriteLine("YUCK!  Your path input stinks");
                return;
            }

            DirReStamper.ReStampDirs(args[0]);
        }
    }
}
