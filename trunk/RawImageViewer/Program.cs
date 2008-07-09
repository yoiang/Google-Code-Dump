using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace RawImageViewer
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
//            Application.Run(new MainWindow());
            Application.Run(new MainWindow("Untitled.bmp", 54, 61, "B1G1R1"));
        }
    }
}
