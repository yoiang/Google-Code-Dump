using System.Drawing;

namespace ImageBreakdownBuildup
{
    public class AverageColorBitmap
    {
        Bitmap Average;
        protected int iGridWidth;
        protected int iGridHeight;
        protected int iGridSpacingWidth;
        protected int iGridSpacingHeight;

        public AverageColorBitmap( Bitmap Copy, int SetGridWidth, int SetGridHeight, int SetGridSpacingWidth, int SetGridSpacingHeight )
        {
            iGridWidth = -1;
            iGridHeight = -1;
            iGridSpacingWidth = -1;
            iGridSpacingHeight = -1;
            Update( Copy, SetGridWidth, SetGridHeight, SetGridSpacingWidth, SetGridSpacingHeight );
        }

        public AverageColorBitmap( AverageColorBitmap Copy )
        {
            Average = new Bitmap( Copy );
            iGridWidth = Copy.iGridWidth;
            iGridHeight = Copy.iGridHeight;
            iGridSpacingWidth = Copy.iGridSpacingWidth;
            iGridSpacingHeight = Copy.iGridSpacingHeight;
        }

        public void Update( Bitmap Copy, int SetGridWidth, int SetGridHeight, int SetGridSpacingWidth, int SetGridSpacingHeight )
        {
            if( iGridWidth == SetGridWidth && iGridHeight == SetGridHeight && iGridSpacingWidth == SetGridSpacingWidth && iGridSpacingHeight == SetGridSpacingHeight )
            {
                return;
            }

            iGridWidth = SetGridWidth;
            iGridHeight = SetGridHeight;
            iGridSpacingWidth = SetGridSpacingWidth;
            iGridSpacingHeight = SetGridSpacingHeight;
            Average = new Bitmap( Copy );
            for( int TravX = 0; TravX < Average.Width; TravX += iGridWidth + iGridSpacingWidth )
            {
                for( int TravY = 0; TravY < Average.Height; TravY += iGridHeight + iGridSpacingHeight )
                {
                    int EndX = TravX + iGridWidth;
                    int EndY = TravY + iGridHeight;
                    if( EndX >= Average.Width )
                    {
                        EndX = Average.Width - 1;
                    }
                    if( EndY >= Average.Height )
                    {
                        EndY = Average.Height - 1;
                    }

                    if( TravX != EndX && TravY != EndY )
                    {
                        Color AverageColor = Average.GetAverageColor( TravX, TravY, EndX, EndY );

                        Average.SetBlock( TravX, TravY, EndX, EndY, AverageColor );
                    }
                }
            }
        }

        public static implicit operator Bitmap( AverageColorBitmap Bitmap )
        {
            return Bitmap.Average;
        }

        public int GridWidth { get { return iGridWidth; } }
        public int GridHeight { get { return iGridHeight; } }
        public int GridSpacingWidth { get { return iGridSpacingWidth; } }
        public int GridSpacingHeight { get { return iGridSpacingHeight; } }
    }

    public class BuildUpBitmap : AverageColorBitmap
    {
        Bitmap BuildUp;

        string BuildUpSourceFolder;
        System.Collections.Generic.Dictionary<Color, Bitmap> BuildUpsByAverageColor;
        double Tolerance;

        public BuildUpBitmap( Bitmap Original, AverageColorBitmap AverageColorBitmap, string SetBuildUpSourceFolder, double SetTolerance )
            : base( AverageColorBitmap )
        {
            BuildUpSourceFolder = SetBuildUpSourceFolder;
            Tolerance = SetTolerance;
            CreateBuildUpsByAverageColorDictionary();

            BuildUp = new Bitmap( Original );
            System.Random RandomClosest = new System.Random();
            for( int TravX = 0; TravX < BuildUp.Width; TravX += iGridWidth + iGridSpacingWidth )
            {
                for( int TravY = 0; TravY < BuildUp.Height; TravY += iGridHeight + iGridSpacingHeight )
                {
                    int EndX = TravX + iGridWidth;
                    int EndY = TravY + iGridHeight;
                    if( EndX >= BuildUp.Width )
                    {
                        EndX = BuildUp.Width - 1;
                    }
                    if( EndY >= BuildUp.Height )
                    {
                        EndY = BuildUp.Height - 1;
                    }

                    if( TravX != EndX && TravY != EndY )
                    {
                        System.Collections.Generic.List<Color> ClosestColors = FindClosestInAverageColorDictionary( ( ( Bitmap )AverageColorBitmap ).GetPixel( TravX, TravY ) );
                        if( ClosestColors.Count > 0 )
                        {
                            BuildUp.SetBlock( TravX, TravY, EndX, EndY, BuildUpsByAverageColor[ ClosestColors[ RandomClosest.Next( 0, ClosestColors.Count ) ] ] );
                        }
                    }
                }
            }
        }

        private void CreateBuildUpsByAverageColorDictionary()
        {
            if( BuildUpsByAverageColor == null )
            {
                BuildUpsByAverageColor = new System.Collections.Generic.Dictionary<Color, Bitmap>();
            } else
            {
                BuildUpsByAverageColor.Clear();
            }
            string[] BuildUpsFileNames = System.IO.Directory.GetFiles( BuildUpSourceFolder, "*.jpg" );//, System.IO.SearchOption.
            foreach( string FileName in BuildUpsFileNames )
            {
                Bitmap BuildUpWith = new Bitmap( FileName );
                BuildUpWith = new Bitmap( BuildUpWith, new Size( iGridWidth, iGridHeight ) );
                BuildUpsByAverageColor[ BuildUpWith.GetAverageColor( 0, 0, BuildUpWith.Width - 1, BuildUpWith.Height - 1 ) ] = BuildUpWith;
            }
        }

        private System.Collections.Generic.List<Color> FindClosestInAverageColorDictionary( Color To )
        {
            double ToleranceSquared = System.Math.Pow( Tolerance, 2 );
            double ClosestDistanceSquared = -1;
            Color Closest = Color.Black;
            System.Collections.Generic.List< Color > WithinTolerance = new System.Collections.Generic.List<Color>();

            foreach( Color Key in BuildUpsByAverageColor.Keys )
            {
                if( ClosestDistanceSquared == -1 )
                {
                    Closest = Key;
                    ClosestDistanceSquared = System.Math.Pow( To.R - Key.R, 2 ) + System.Math.Pow( To.G - Key.G, 2 ) + System.Math.Pow( To.B - Key.B, 2 );
                    if( ClosestDistanceSquared <= ToleranceSquared )
                    {
                        WithinTolerance.Add( Key );
                    }
                } else
                {
                    double KeyDistanceSquared = System.Math.Pow( To.R - Key.R, 2 ) + System.Math.Pow( To.G - Key.G, 2 ) + System.Math.Pow( To.B - Key.B, 2 );
                    if( ClosestDistanceSquared > KeyDistanceSquared )
                    {
                        Closest = Key;
                        ClosestDistanceSquared = KeyDistanceSquared;
                    }
                    if( KeyDistanceSquared <= ToleranceSquared )
                    {
                        WithinTolerance.Add( Key );
                    }
                }
            }
            if( WithinTolerance.Count == 0 )
            {
                WithinTolerance.Add( Closest );
            }
            return WithinTolerance;
        }

        public static implicit operator Bitmap( BuildUpBitmap Bitmap )
        {
            return Bitmap.BuildUp;
        }
    }
}