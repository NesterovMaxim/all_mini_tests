#pragma once

#include <iostream>

#define out std::cout

#if defined(FOO_IMPLEMENTATION)
#define FOO_EXPORT __declspec(dllexport)
#else
#define FOO_EXPORT __declspec(dllimport)
#endif  // defined(BASE_IMPLEMENTATION)

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

