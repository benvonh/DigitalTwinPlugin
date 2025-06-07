#ifndef TEST__VISIBILITY_CONTROL_H_
#define TEST__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define TEST_EXPORT __attribute__ ((dllexport))
    #define TEST_IMPORT __attribute__ ((dllimport))
  #else
    #define TEST_EXPORT __declspec(dllexport)
    #define TEST_IMPORT __declspec(dllimport)
  #endif
  #ifdef TEST_BUILDING_LIBRARY
    #define TEST_PUBLIC TEST_EXPORT
  #else
    #define TEST_PUBLIC TEST_IMPORT
  #endif
  #define TEST_PUBLIC_TYPE TEST_PUBLIC
  #define TEST_LOCAL
#else
  #define TEST_EXPORT __attribute__ ((visibility("default")))
  #define TEST_IMPORT
  #if __GNUC__ >= 4
    #define TEST_PUBLIC __attribute__ ((visibility("default")))
    #define TEST_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define TEST_PUBLIC
    #define TEST_LOCAL
  #endif
  #define TEST_PUBLIC_TYPE
#endif

#endif  // TEST__VISIBILITY_CONTROL_H_
