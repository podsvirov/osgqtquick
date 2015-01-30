#ifndef _OSGQTQUICK_EXPORT_
#define _OSGQTQUICK_EXPORT_ 1

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__) || defined( __MWERKS__)
#  if defined( OSGQTQUICK_LIBRARY_STATIC )
#    define OSGQTQUICK_EXPORT
#  elif defined( OSGQTQUICK_LIBRARY )
#    define OSGQTQUICK_EXPORT __declspec(dllexport)
#  else
#    define OSGQTQUICK_EXPORT __declspec(dllimport)
#  endif
#else
#  define OSGQTQUICK_EXPORT
#endif

#endif // _OSGQTQUICK_EXPORT_
