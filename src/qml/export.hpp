#ifndef _OSGQTQML_EXPORT_
#define _OSGQTQML_EXPORT_ 1

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__) || defined( __MWERKS__)
    #  if defined( OSG_LIBRARY_STATIC )
        #    define OSGQTQML_EXPORT
        #  elif defined( OSGQTQML_LIBRARY )
        #    define OSGQTQML_EXPORT   __declspec(dllexport)
        #  else
        #    define OSGQTQML_EXPORT   __declspec(dllimport)
        #endif
#else
        #define OSGQT_EXPORT
#endif

#endif // _OSGQTQML_EXPORT_

