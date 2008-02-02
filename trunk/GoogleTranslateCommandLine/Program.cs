using System;
using System.Collections.Generic;
using System.Text;
using Google.Unoffical.Translate;

namespace GoogleTranslateCommandLine
{
    class Program
    {
        static int Main( string[] args )
        {
            if (args.Length < 1)
            {
                WriteSyntax();
                return 1;
            }
            if( args[ 0 ] == "-t" )
            {
                return DoTranslate( args );
            }
            if( args[ 0 ] == "-c" )
            {
                return DoCheckPair( args );
            }
            return 1;
        }

        static void WriteSyntax()
        {
            Console.Write( "Invalid syntax\n" );
            Console.Write( "\tExpected: GoogleTranslateCommandLine.exe <Switch> <Switch Parameters>\n" );
            Console.Write( "\t\t-t <From> <To> <Text>\n" );
            Console.Write( "\t\t-c <From> <To>" );
        }

        static int DoTranslate( string[] args )
        {
            if( args.Length < 4 )
            {
                WriteSyntax();
                return 1;
            }

            string From = args[ 1 ];
            string To = args[ 2 ];
            string Text = args[ 3 ];
            for( int nTravTextParams = 4; nTravTextParams < args.Length; ++nTravTextParams )
            {
                Text += " " + args[ nTravTextParams ];
            }
            Console.Write( Translate.translate( Text, From, To ) );
            return 0;
        }

        static int DoCheckPair( string[] args )
        {
            if( args.Length < 3 )
            {
                WriteSyntax();
                return 1;
            }

            string From = args[ 1 ];
            string To = args[ 2 ];
            if( !Language.isValidLanguagePair( From, To ) )
            {
                Console.Write( From + " " + To + " is an invalid pair" );
                return 0;
            }

            Console.Write( From + " " + To + " is a valid pair" );
            return 0;
        }
    }
}
