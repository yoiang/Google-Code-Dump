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
    public partial class MainWindow : Form
    {
        ImageWindow ImageWindow;

        RawBitmap Bitmap;

        public MainWindow()
        {
            InitializeComponent();
            CreateMembers();
        }

        public MainWindow(string FileName, int HeaderSize, int ImageWidth, string ImageFormat)
        {
            InitializeComponent();
            CreateMembers();

            this.HeaderSize.Value = HeaderSize;
            this.ImageWidth.Value = ImageWidth;
            this.ImageFormat.Text = ImageFormat;

            FromFile( FileName );
        }

        private void CreateMembers()
        {
            ImageWindow = new ImageWindow();
            ImageWindow.MainWindow = this;
        }

        private void OnShown(object sender, EventArgs e)
        {
            ImageWindow.Show();
            Point ImageWindowLocation = new Point( Location.X + Width, Location.Y );
            ImageWindow.Location = ImageWindowLocation;
            Focus();
        }

        private void ImageChanged()
        {
            ImageHeight.Text = Bitmap.Height.ToString();
            PixelSize.Text = Bitmap.PixelSize.ToString();
            ImageWindow.SetImageSize( Bitmap.Width, Bitmap.Height );

            for( int X = 0; X < Bitmap.Width; X++ )
            {
                for( int Y = 0; Y < Bitmap.Height; Y++ )
                {
                    ImageWindow.SetPixel(X, Y, Bitmap.GetPixel(X, Y));
                }
            }

            ImageWindow.Redraw();
        }

        private void OpenFileButton_Click( object sender, EventArgs e )
        {
            System.Windows.Forms.OpenFileDialog OpenFileDialog = new System.Windows.Forms.OpenFileDialog();
            if( OpenFileDialog.ShowDialog() == DialogResult.OK )
            {
                FromFile( OpenFileDialog.FileName );
            }
        }

        private void FromFile( string filename )
        {
            Bitmap = RawBitmap.FromFile( filename );
            if( Bitmap != null )
            {
                Bitmap.Width = Convert.ToInt32( ImageWidth.Value );
                Bitmap.HeaderSize = Convert.ToInt32( HeaderSize.Value );
                Bitmap.PixelFormat = ImageFormat.Text;

                ImageChanged();

                ImageFileNameLabel.Text = filename;
                ImageWindow.Text = filename;
            }
        }

        private void ImageWidthChanged(object sender, EventArgs e)
        {
            if( Bitmap != null )
            {
                Bitmap.Width = Convert.ToInt32(ImageWidth.Value);
                ImageChanged();
            }
        }

        private void HeaderSizeChanged(object sender, EventArgs e)
        {
            if( Bitmap != null )
            {
                Bitmap.HeaderSize = Convert.ToInt32( HeaderSize.Value );
                ImageChanged();
            }
        }

        private void ImageFormatChanged(object sender, EventArgs e)
        {
            if( Bitmap != null )
            {
                Bitmap.PixelFormat = ImageFormat.Text;
                ImageChanged();
            }
        }

        public void UpdateMouseOver( int X, int Y )
        {
            MouseX.Text = X.ToString();
            MouseY.Text = Y.ToString();
            MouseRed.Text = Bitmap.GetPixel( X, Y ).R.ToString();
            MouseGreen.Text = Bitmap.GetPixel( X, Y ).G.ToString();
            MouseBlue.Text = Bitmap.GetPixel( X, Y ).B.ToString();
        }
    }
}
