#ifndef WORDLE_PRELUDE_H
#define WORDLE_PRELUDE_H

#if defined(_WIN32) || defined(__CYGWIN__)
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
#else
  #if __GNUC__ >= 4
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

#endif
