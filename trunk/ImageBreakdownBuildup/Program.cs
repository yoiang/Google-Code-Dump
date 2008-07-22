using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Drawing;

namespace ImageBreakdownBuildup
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
            Application.SetCompatibleTextRenderingDefault( false );

            OpenFileDialog OpenFile = new OpenFileDialog();
            OpenFile.Title = "Select an image to Break Down...";
            OpenFile.Filter = "Supported Formats|*.bmp;*.gif;*.jpg;*.jpeg;*.png;*.tiff|BMP files|*.bmp|GIF files|*.gif|JPEG files|*.jpg;*.jpeg|PNG files|*.png|TIFF files|*.tiff";

            FolderBrowserDialog OpenDirectory = new FolderBrowserDialog();
            OpenDirectory.Description = "Select the directory to gather Build Up images from...";

            DialogResult Result = OpenFile.ShowDialog();
            if( Result == DialogResult.OK )
            {
                Result = OpenDirectory.ShowDialog();
            }
            if( Result == DialogResult.OK )
            {
                Form Main = new Main( OpenFile.FileName, OpenDirectory.SelectedPath );
                Application.Run( Main );
            }
        }

        public static Color GetAverageColor( this Bitmap Bitmap, int StartX, int StartY, int EndX, int EndY )
        {
            if( StartX > EndX || StartY > EndY )
            {
                throw new Exception( "In GetAverageColor Start is past End" );
            }

            int PixelCount = 0;
            int RedTotal = 0, GreenTotal = 0, BlueTotal = 0;
            for( int TravX = StartX; TravX < EndX; TravX++ )
            {
                for( int TravY = StartY; TravY < EndY; TravY++ )
                {
                    RedTotal += Bitmap.GetPixel( TravX, TravY ).R;
                    GreenTotal += Bitmap.GetPixel( TravX, TravY ).G;
                    BlueTotal += Bitmap.GetPixel( TravX, TravY ).B;
                    PixelCount++;
                }
            }
            return Color.FromArgb( RedTotal / PixelCount, GreenTotal / PixelCount, BlueTotal / PixelCount );
        }

        public static void SetBlock( this Bitmap Bitmap, int StartX, int StartY, int EndX, int EndY, Color SetColor )
        {
            for( int TravX = StartX; TravX < EndX; TravX++ )
            {
                for( int TravY = StartY; TravY < EndY; TravY++ )
                {
                    Bitmap.SetPixel( TravX, TravY, SetColor );
                }
            }
        }
        public static void SetBlock( this Bitmap Bitmap, int StartX, int StartY, int EndX, int EndY, Bitmap SetFrom )
        {
            for( int TravX = StartX; TravX < EndX; TravX++ )
            {
                for( int TravY = StartY; TravY < EndY; TravY++ )
                {
                    Color SetColor;
                    if( TravX - StartX < SetFrom.Width && TravY - StartY < SetFrom.Height )
                    {
                        SetColor = SetFrom.GetPixel( TravX - StartX, TravY - StartY );
                    } else
                    {
                        SetColor = Color.Black;
                    }
                    Bitmap.SetPixel( TravX, TravY, SetColor );
                }
            }
        }
    }
}
