using System;
using System.Runtime.InteropServices;

namespace HelloWorld
{
    class Program
    {
        [DllImport("Test")]
        static extern int NativeFunc();

        static void Main(string[] args)
        {
            Console.WriteLine("[Program.cs] Main");
            int value = NativeFunc();
            Console.WriteLine("[Program.cs] NativeFunc returns {0}", value);
        }
    }
}