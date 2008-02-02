/**
 * Language.cs - based off of Language.java, Copyright (C) 2007,  Richard Midwinter
 */

using System;

namespace Google.Unoffical.Translate
{

    /**
    * Defines language information for the Google Translate API.
    *
    * @author Richard Midwinter
    */

    public class Language
    {
        public static String ARABIC = "ar";
        public static String CHINESE = "zh";
        public static String CHINESE_SIMPLIFIED = "zh-CN";
        public static String CHINESE_TRADITIONAL = "zh-TW";
        public static String DUTCH = "nl";
        public static String ENGLISH = "en";
        public static String FRENCH = "fr";
        public static String GERMAN = "de";
        public static String GREEK = "el";
        public static String ITALIAN = "it";
        public static String JAPANESE = "ja";
        public static String KOREAN = "ko";
        public static String PORTUGESE = "pt";
        public static String RUSSIAN = "ru";
        public static String SPANISH = "es";

        private static String[] validLanguages = new String[] {
                       ARABIC,
                       CHINESE,
                       CHINESE_SIMPLIFIED,
                       CHINESE_TRADITIONAL,
                       ENGLISH,
                       FRENCH,
                       GERMAN,
                       ITALIAN,
                       JAPANESE,
                       KOREAN,
                       PORTUGESE,
                       RUSSIAN,
                       SPANISH
                       };

        private static String[] validLanguagePairs = new String[] {
                       ARABIC +'|' +ENGLISH,
                       CHINESE +'|' +ENGLISH,
                       CHINESE_SIMPLIFIED +'|' +CHINESE_TRADITIONAL,
                       CHINESE_TRADITIONAL +'|' +CHINESE_SIMPLIFIED,
                       DUTCH +'|' +ENGLISH,
                       ENGLISH +'|' +ARABIC,
                       ENGLISH +'|' +CHINESE,
                       ENGLISH +'|' +CHINESE_SIMPLIFIED,
                       ENGLISH +'|' +CHINESE_TRADITIONAL,
                       ENGLISH +'|' +DUTCH,
                       ENGLISH +'|' +FRENCH,
                       ENGLISH +'|' +GERMAN,
                       ENGLISH +'|' +GREEK,
                       ENGLISH +'|' +ITALIAN,
                       ENGLISH +'|' +JAPANESE,
                       ENGLISH +'|' +KOREAN,
                       ENGLISH +'|' +PORTUGESE,
                       ENGLISH +'|' +RUSSIAN,
                       ENGLISH +'|' +SPANISH,
                       FRENCH +'|' +ENGLISH,
                       FRENCH +'|' +GERMAN,
                       GERMAN +'|' +ENGLISH,
                       GERMAN +'|' +FRENCH,
                       GREEK +'|' +ENGLISH,
                       ITALIAN +'|' +ENGLISH,
                       JAPANESE +'|' +ENGLISH,
                       KOREAN +'|' +ENGLISH,
                       PORTUGESE +'|' +ENGLISH,
                       RUSSIAN +'|' +ENGLISH,
                       SPANISH +'|' +ENGLISH
       };

        /**
         * Checks a given language is available to use with Google Translate.
         *
         * @param language The language code to check for.
         * @return true if this language is available to use with Google Translate, false otherwise.
         */
        public static Boolean isValidLanguage( String language )
        {
            return Array.IndexOf<String>( validLanguages, language ) != validLanguagePairs.GetLowerBound( 0 ) - 1;
        }

        /**
         * Checks the languages to translate to and from match with a supported Google Translate pairing.
         *
         * @param from The language code to translate from.
         * @param to The language code to translate to.
         * @return true if the language pairing is supported, false otherwise.
         */
        public static Boolean isValidLanguagePair( String from, String to )
        {
            return Array.IndexOf<String>( validLanguagePairs, from + '|' + to ) != validLanguagePairs.GetLowerBound( 0 ) - 1;
        }
    }
}