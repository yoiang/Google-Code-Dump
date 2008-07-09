using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RawImageViewer
{
    class RawBitmap
    {
        List<byte> Data;
        
        int nHeaderSize;
        
        string strPixelFormat;
        System.Collections.Generic.Dictionary<char, PixelParamInfo> PixelParamInfos;
        int nPixelSize;
        int nWidth;
        int nHeight;

        #region Constructors
        public RawBitmap() : base()
        {
            Data = new List<byte>();
            PixelParamInfos = new Dictionary<char, PixelParamInfo>();
        }

        public void ClearPixelParamInfos()
        {
            PixelParamInfos.Clear();
        }
        #endregion

        public int HeaderSize { get { return nHeaderSize; } set { nHeaderSize = value; CalcHeight(); } }
        public string PixelFormat { get { return strPixelFormat; } set { strPixelFormat = value; CalcPixelSize(); CalcHeight(); } }
        public int PixelSize { get { return nPixelSize; } }
        public int Width { get { return nWidth; } set { nWidth = value; CalcHeight(); } }
        public int Height { get { return nHeight; } }


        #region Loading and Saving
        public static RawBitmap FromFile( string filename )
        {
            if ( !System.IO.File.Exists( filename ) )
            {
                return null;
            }
            System.IO.Stream FileStream = System.IO.File.Open( filename, System.IO.FileMode.Open );
            RawBitmap Result = FromStream( FileStream );
            FileStream.Close();
            return Result;
        }

        public static RawBitmap FromStream( System.IO.Stream stream )
        {
            RawBitmap ReadFromFile = new RawBitmap();
            byte[] ByteBuffer = new byte[ 256 ];
            while( stream.Position < stream.Length )
            {
                int CountRead = stream.Read( ByteBuffer, 0, 256 );
                for( int TravCountRead = 0; TravCountRead < CountRead; ++TravCountRead )
                {
                    ReadFromFile.Data.Add( ByteBuffer[ TravCountRead ] );
                }
            }
            return ReadFromFile;
        }

        public void Save( string filename )
        {
            System.IO.Stream FileStream = System.IO.File.Open( filename, System.IO.FileMode.Create );
            Save( FileStream );
            FileStream.Close();
        }

        public void Save( System.IO.Stream stream )
        {
            for( int TravData = 0; TravData < Data.Count; TravData++ )
            {
                stream.WriteByte( Data[ TravData ] );
            }
        }
        #endregion

        private void CalcPixelSize()
        {
            nPixelSize = 0;
            if( PixelFormat.Length < 0 )
            {
                return;
            }

            System.Text.RegularExpressions.Regex regexObj = new System.Text.RegularExpressions.Regex( "([A-Za-z]{1}[0-9]+)" );
            System.Text.RegularExpressions.Match matchResults = regexObj.Match( PixelFormat );
            while( matchResults.Success )
            {
                char Parameter = matchResults.Value[ 0 ];
                string strParamSize = matchResults.Value.Remove( 0, 1 );

                PixelParamInfos[ Parameter ] = new PixelParamInfo( Parameter, nPixelSize, Convert.ToInt32( strParamSize ) );

                nPixelSize += PixelParamInfos[ Parameter ].Size;
                matchResults = matchResults.NextMatch();

            }
        }

        private void CalcHeight()
        {
            if( Data.Count - HeaderSize < 1 )
            {
                return;
            }

            if( PixelSize == 0 || Width == 0 )
            {
                nHeight = 0;
                return;
            }
            nHeight = ( int )Math.Floor( ( float )( Data.Count - HeaderSize ) / ( float )PixelSize / ( float )Width );
        }

        public System.Drawing.Color GetPixel( int X, int Y )
        {
            int PixelOffset = HeaderSize + X * PixelSize + Y * PixelSize * Width;
            return System.Drawing.Color.FromArgb( GetParameterValue( PixelOffset, 'R' ), GetParameterValue( PixelOffset, 'G' ), GetParameterValue( PixelOffset, 'B' ) );
        }

        private int GetParameterValue( int PixelOffset, char Parameter )
        {
            if( !PixelParamInfos.ContainsKey( Parameter ) || PixelParamInfos[ Parameter ].Size == 0 )
            {
                return 0;
            }

            PixelParamInfo ParamInfo = PixelParamInfos[ Parameter ];
            int UnscaledValue = 0;
            if( ParamInfo.Size == 1 )
            {
                return Data[ PixelOffset + ParamInfo.Offset ];
            }
            //Todo: currently left to right, add support for right to left
            for( int TravSize = 0; TravSize < ParamInfo.Size; ++TravSize )
            {
                UnscaledValue += Data[ PixelOffset + ParamInfo.Offset + TravSize ] << ( ParamInfo.Size - TravSize - 1 ) * 8;
            }
            return ( int )( ( float )( 256 * UnscaledValue ) / ( float )( Math.Pow( 256, ParamInfo.Size ) ) );
        }
    }


    public class PixelParamInfo
    {
        public char Parameter;
        public int Offset;
        public int Size;
        public PixelParamInfo() { }
        public PixelParamInfo( char Parameter, int Offset, int Size )
        {
            this.Parameter = Parameter;
            this.Offset = Offset;
            this.Size = Size;
        }
    }
}
