#ifndef WORDLE_PRELUDE_H
#define WORDLE_PRELUDE_H

  #if defined(WORDLE_BUILD_SHARED_LIBRARY) && defined(_WIN32) || defined(__CYGWIN__)
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
  #elif __GNUC__ >= 4 && defined(WORDLE_BUILD_SHARED_LIBRARY)
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