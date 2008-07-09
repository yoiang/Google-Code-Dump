using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace RawImageViewer
{
    public partial class ImageWindow : Form
    {
        public MainWindow MainWindow;

        System.Drawing.Bitmap Bitmap;
        
        public ImageWindow()
        {
            InitializeComponent();
        }

        public void SetImageSize(int Width, int Height)
        {
            if (Width <= 0 || Height <= 0)
            {
                return;
            }
            Bitmap = new System.Drawing.Bitmap(Width, Height, System.Drawing.Imaging.PixelFormat.Format24bppRgb);
//            Bitmap.SetResolution( Width, Height );
        }

        public void SetPixel(int X, int Y, Color Color)
        {
            if (Bitmap == null || X >= Bitmap.Width || Y >= Bitmap.Height)
            {
                return;
            }

            Bitmap.SetPixel(X, Y, Color);
        }

        public void Redraw()
        {
            if (Bitmap != null)
            {
/*                Image.Image = new System.Drawing.Bitmap( Bitmap.Width, Bitmap.Height, System.Drawing.Imaging.PixelFormat.Format24bppRgb );
                Graphics Imagebox = Graphics.FromImage( Image.Image );
                Imagebox.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.Bilinear;
                Imagebox.DrawImage( Bitmap, new System.Drawing.RectangleF( 0, 0, Bitmap.Width, Bitmap.Height ) );*/
                Image.Image = Bitmap;
            }
        }

        private void PictureBoxOnMouseMove( object sender, MouseEventArgs e )
        {
            int MouseX = e.X;
            int MouseY = e.Y;
            int RealX = (int)Math.Floor((float)Bitmap.Width * (float)(MouseX) / (float)Image.Width);
            int RealY = ( int )Math.Floor( ( float )Bitmap.Height * ( float )( MouseY) / ( float )Image.Height );
            MainWindow.UpdateMouseOver( RealX, RealY );
        }

        private void OnClosing( object sender, FormClosingEventArgs e )
        {
            if( MainWindow != null )
            {
                MainWindow.Close();
            }
        }
    }

    public class Pixel
    {
        public int Red, Green, Blue;
    }
}
