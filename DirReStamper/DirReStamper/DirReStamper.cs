using System;
using System.IO;

namespace DirReStamper
{
    public class DirReStamper
    {
        public static void ReStampDirs(string path)
        {
            if (!Directory.Exists(path))
                return;

            Console.WriteLine($"Reading directories for: {path}");
            foreach (var dir in Directory.GetDirectories(path))
            {
                ReStampDir(dir);
            }
        }

        public static void ReStampDir(string path)
        {
            if (!Directory.Exists(path))
                return;

            var createdStamp = Directory.GetCreationTime(path);
            var lastModStamp = DateTime.Now - TimeSpan.FromDays(20*365);
            var mods = false;
            foreach (var file in Directory.GetFiles(path))
            {
                mods = true;
                var fileCreatedStamp = File.GetCreationTime(file);
                var fileLastModStamp = File.GetLastWriteTime(file);

                if (fileCreatedStamp < createdStamp)
                {
                    mods = true;
                    createdStamp = fileCreatedStamp;
                }
                if (fileLastModStamp > lastModStamp)
                {
                    lastModStamp = fileLastModStamp;
                    mods = true;
                }

            }
            if (!mods)
                return;

            Console.WriteLine($"ReStamping: {path} to {lastModStamp} created on {createdStamp}");
            Directory.SetCreationTime(path, createdStamp);
            Directory.SetLastWriteTime(path, lastModStamp);
        }
    }
}