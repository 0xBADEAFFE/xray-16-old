#pragma once
#include "Common/Config.hpp"

#if defined(__linux__)
#define LINUX
#elif defined(_WIN32)
#define WINDOWS
#else
#error Unsupported platform
#endif

#if defined(_M_X64) || defined(__amd64__)
#define XR_X64
#else
#define XR_X86
#endif

#include "Common/Compiler.inl"

#include <ctime>

#if defined(LINUX)
#include "Common/PlatformLinux.inl"
#elif defined(WINDOWS)
#include "Common/PlatformWindows.inl"
#endif

// Flip this to 1 to turn off these messages everywhere.
// !!! FIXME: I have it forced off for Windows because fprintf.
#if 0 || WINDOWS
#define STUBBED(txt) do {} while (0)
#endif

#ifndef STUBBED
#define STUBBED(txt) do { \
  static bool already_seen = false; \
  if (!already_seen) { \
    already_seen = true; \
    fprintf(stderr, "STUBBED: %s in %s, line %d.\n", txt, __FILE__, __LINE__); \
  } \
} while (0)
#endif
