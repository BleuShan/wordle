#ifndef WORDLE_PRELUDE_EXPORTS_H
#define WORDLE_PRELUDE_EXPORTS_H

#if WORDLE_BUILD_SHARED_LIBRARY && (WIN32 || __CYGWIN__)
  #ifndef WORDLE_PUBLIC_API
    #ifdef WORDLE_EXPORTS
      #define WORDLE_PUBLIC_API __declspec(dllexport)
    #else
      #define WORDLE_PUBLIC_API __declspec(dllimport)
    #endif
  #endif
  #ifndef WORDLE_PRIVATE_API
    #define WORDLE_PRIVATE_API
  #endif
#elif __GNUC__ >= 4 && WORDLE_BUILD_SHARED_LIBRARY
  #ifndef WORDLE_PUBLIC_API
    #define WORDLE_PUBLIC_API __attribute__((visibility("default")))
  #endif
  #ifndef WORDLE_PRIVATE_API
    #define WORDLE_PRIVATE_API __attribute__((visibility("hidden")))
  #endif
#else
  #ifndef WORDLE_PUBLIC_API
    #define WORDLE_PUBLIC_API
  #endif
  #ifndef WORDLE_PRIVATE_API
    #define WORDLE_PRIVATE_API
  #endif
#endif

#endif
