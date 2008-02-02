/**
 * Translate.cs - based off of Translate.java, Copyright (C) 2007,  Richard Midwinter
 */

using System;
using System.IO;
using System.Threading;

using Google.GData.Client;

namespace Google.Unoffical.Translate
{

    /**
     * Makes the Google Translate API available to C# applications.
     * 
     * @author Richard Midwinter
     * @author Emeric Vernat
     * @author Juan B Cabral
     * @converted to C# by Ian G
     */
    public class Translate
    {

        private static System.Text.Encoding ENCODING = System.Text.Encoding.UTF8;
        private static String INTERMEDIATE_LANGUAGE = Language.ENGLISH;
        private static String URL_STRING = "http://translate.google.com/translate_t?langpair=";
        private static String TEXT_VAR = "&text=";

        /**
         * Translates text from a given language to another given language using Google Translate
         * 
         * @param text The String to translate.
         * @param from The language code to translate from.
         * @param to The language code to translate to.
         * @return The translated String.
         * @throws Exception
         */
        public static string translate( string text, string from, string to ) //throws Exception 
        {
            if( Language.isValidLanguagePair( from, to ) )
            {
                return retrieveTranslation( text, from, to );
            } else
            {
                return retrieveTranslation( retrieveTranslation( text, from, INTERMEDIATE_LANGUAGE ), INTERMEDIATE_LANGUAGE, to );
            }
        }

        /**
         * Forms an HTTP request and parses the response for a translation.
         * 
         * @param text The String to translate.
         * @param from The language code to translate from.
         * @param to The language code to translate to.
         * @return The translated String.
         * @throws Exception
         */
        private static string retrieveTranslation( string text, string from, string to )// throws Exception 
        {
            try
            {
                Uri RequestURL = new Uri( URL_STRING + from + "|" + to + TEXT_VAR + text ); //URLEncoder.encode( text, ENCODING ) );
                Service TranslationRequest = new Service( "GoogleTranslateCommandLine" );

                Stream result = TranslationRequest.Query( RequestURL );
                String page = "";

                const int size = 4096;
                byte[] bytes = new byte[ size ];
                int numBytes;
                while( ( numBytes = result.Read( bytes, 0, size ) ) > 0 )
                {
                    page += System.Text.Encoding.ASCII.GetString( bytes, 0, numBytes );
                }

                int resultBox = page.IndexOf( "<div id=result_box dir=" );
                if( resultBox < 0 )
                    throw new Exception( "No translation result returned." );

                String start = page.Substring( resultBox );
                int nStart = start.IndexOf( '>' ) + 1;
                return start.Substring( nStart, start.IndexOf( "</div>" ) - nStart );
            } catch( Exception ex )
            {
                throw new Exception( "[google-api-translate] Error retrieving translation.", ex );
            }
        }
    }
};