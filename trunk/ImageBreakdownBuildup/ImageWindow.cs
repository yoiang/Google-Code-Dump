using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.ComponentModel;

namespace System.Windows.Forms
{
    public partial class ImageWindow : Form
    {
        [Browsable( true ), Category( "ImageWindow" ), DefaultValue( true ), EditorBrowsable( EditorBrowsableState.Always )]
        public bool AutoResizeWindowToBitmap { get; set; }
        [Browsable( true ), Category( "ImageWindow" ), DefaultValue( true ), EditorBrowsable( EditorBrowsableState.Always )]
        public bool FitWindowToScreen { get; set; }

        [Browsable( true ), Category( "ImageWindow" ), DefaultValue( true ), EditorBrowsable( EditorBrowsableState.Always )]
        public bool AutoConstructImageWindowInfo { get; set; }
        private ImageWindowInfo ImageInfo;

        protected System.Drawing.Bitmap Bitmap;

        #region Constructors
        public ImageWindow()
        {
            ImageWindowConstructor();
        }

        public ImageWindow( string FileName )
        {
            ImageWindowConstructor();

            SetToImageFile( FileName );
        }

        public ImageWindow( ImageWindowInfo SetImageInfo )
        {
            ImageInfo = SetImageInfo;

            ImageWindowConstructor();
        }

        public ImageWindow( string FileName, ImageWindowInfo SetImageInfo )
        {
            ImageInfo = SetImageInfo;

            ImageWindowConstructor();

            SetToImageFile( FileName );
        }

        void ImageWindowConstructor()
        {
            InitializeComponent();
        }
        #endregion

        public void SetToImageFile( string FileName )
        {
            SetImage( new System.Drawing.Bitmap( FileName ) );
        }

        public virtual void SetImage( Bitmap SetBitmap )
        {
            Bitmap = SetBitmap;

            if( Bitmap != null )
            {
                if( AutoResizeWindowToBitmap )
                {
                    this.Width = Bitmap.Width;
                    this.Height = Bitmap.Height;
                    if( this.Width != Bitmap.Width || this.Height != Bitmap.Height || FitWindowToScreen && this.Width > DesktopBounds.Width || this.Height > DesktopBounds.Height )
                    {
                        float ImageRatio = ( float )this.Width / ( float )this.Height;
                        if( ( float )this.Width / ( float )DesktopBounds.Width > ( float )this.Height / ( float )DesktopBounds.Height )
                        {
                            this.Width = DesktopBounds.Width;
                            this.Height = ( int )( ( float )this.Width / ImageRatio );
                        } else
                        {
                            this.Height = DesktopBounds.Height;
                            this.Width = ( int )( ( float )this.Height * ImageRatio );
                        }
                    } 
                }
            }
//            Bitmap = new Bitmap( Bitmap, new Size( Image.Width, Image.Height ) );
            
            Redraw();
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
            /*                Image.Image = new System.Drawing.Bitmap( Bitmap.Width, Bitmap.Height, System.Drawing.Imaging.PixelFormat.Format24bppRgb );
                            Graphics Imagebox = Graphics.FromImage( Image.Image );
                            Imagebox.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.Bilinear;
                            Imagebox.DrawImage( Bitmap, new System.Drawing.RectangleF( 0, 0, Bitmap.Width, Bitmap.Height ) );*/
            Image.Image = Bitmap;
            UpdateImageWindowInfo();
        }

        public void UpdateImageWindowInfo()
        {
            if( ImageInfo != null )
            {
                if( Bitmap != null )
                {

                    ImageInfo.UpdateSize( Bitmap.Width, Bitmap.Height );
                } else
                {
                    ImageInfo.UpdateSize( 0, 0 );
                }
            }
        }

/*        private void PictureBoxOnMouseMove( object sender, MouseEventArgs e )
        {
            int MouseX = e.X;
            int MouseY = e.Y;
            int RealX = (int)Math.Floor((float)Bitmap.Width * (float)(MouseX) / (float)Image.Width);
            int RealY = ( int )Math.Floor( ( float )Bitmap.Height * ( float )( MouseY) / ( float )Image.Height );
            MainWindow.UpdateMouseOver( RealX, RealY );
        }
        */
        private void OnClosing( object sender, FormClosingEventArgs e )
        {
            if( ImageInfo != null )
            {
                ImageInfo.Close();
                ImageInfo = null;
            }
        }

        private void OnShown( object sender, EventArgs e )
        {
            if( AutoConstructImageWindowInfo )
            {
                ImageInfo = ConstructDefaultImageWindowInfo();
            }

            if( ImageInfo != null )
            {
                UpdateImageWindowInfo();
                ImageInfo.Show( this );
                ImageInfo.Left = this.Right;
            }
        }

        public virtual ImageWindowInfo ConstructDefaultImageWindowInfo()
        {
            return new ImageWindowInfo();
        }
    }
}
