#include <stdio.h>
#include <cstring>
#include <stdlib.h> // for malloc
#include <unistd.h> // for rmdir
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/param.h>
#include <errno.h>
#include <stdarg.h>
#include <ctype.h>
#include <limits.h> // for PAGESIZE...
#include <math.h>
#include <algorithm> // for min max

#include <string>
#include <alloca.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/mman.h> // for mmap / munmap
#include <dirent.h>
#include <utime.h>

#include <SDL2/SDL.h>
#define CONFIG_USE_SDL

#define _LINUX // for GameSpy

#if !defined(__INTEL_COMPILER)
#define _alloca alloca
#endif

#define _MAX_PATH PATH_MAX + 1
#define MAX_PATH PATH_MAX + 1

#define WINAPI

#define _copysign copysign

#define _cdecl //__attribute__((cdecl))
#define _stdcall //__attribute__((stdcall))
#define _fastcall //__attribute__((fastcall))

#define __cdecl
#define __stdcall
#define __fastcall
//#define __declspec
#define __forceinline FORCE_INLINE
#define __pragma
#define __declspec(x)
#define CALLBACK

/*
static inline long InterlockedExchange(volatile long *val, long new_val)
{
  long old_val;
  do {
    old_val = *val;
  } while (__sync_val_compare_and_swap (val, old_val, new_val) != old_val);
    return old_val;
}
*/
//TODO: Implement more platform independend atomic operations: https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/Common/Atomic_GCC.h
inline void InterlockedExchange(volatile unsigned int& target, unsigned int value)
{
  __sync_add_and_fetch(&target, value);
}

inline pthread_t GetCurrentThreadId()
{
    return pthread_self();
}

inline void Sleep(int ms)
{
    SDL_Delay(ms);
}

inline void _splitpath (
   const char *path,  // Path Input
   char *drive,       // Drive     : Output
   char *dir,         // Directory : Output
   char *fname,       // Filename  : Output
   char *ext          // Extension : Output
){}

inline unsigned long GetLastError()
{
  return 0;
}

#define xr_unlink unlink

typedef int BOOL;
typedef char* LPSTR;
typedef char* PSTR;
typedef char* LPTSTR;
typedef const char* LPCSTR;
typedef const char* LPCTSTR;
typedef unsigned char BYTE;
typedef unsigned char* LPBYTE;
typedef unsigned int UINT;
typedef int INT;
typedef long LONG;

typedef unsigned short WORD;
typedef unsigned short* LPWORD;
typedef unsigned long DWORD;
typedef unsigned long* LPDWORD;
typedef const void *LPCVOID;

#define WAVE_FORMAT_PCM  0x0001

typedef struct {
  WORD  wFormatTag;
  WORD  nChannels;
  DWORD nSamplesPerSec;
  DWORD nAvgBytesPerSec;
  WORD  nBlockAlign;
  WORD  wBitsPerSample;
  WORD  cbSize;
} WAVEFORMATEX;

typedef struct _EXCEPTION_POINTERS {
} EXCEPTION_POINTERS, *PEXCEPTION_POINTERS;

#ifdef XR_X64
typedef int64_t INT_PTR;
typedef uint16_t UINT_PTR;
typedef int64_t LONG_PTR;
#else
typedef int INT_PTR;
typedef unsigned int UINT_PTR;
typedef long LONG_PTR;
#endif // XR_X64

typedef void *HANDLE;
typedef void *HMODULE;
typedef void *LPVOID;
typedef UINT_PTR WPARAM;
typedef LONG_PTR LPARAM;
typedef long HRESULT;
typedef long LRESULT;
typedef long _W64;
//typedef void *HWND;
typedef SDL_Window *HWND;
typedef void *HDC;
//typedef void *HGLRC;
typedef SDL_GLContext HGLRC;
typedef float FLOAT;
typedef unsigned char UINT8;

typedef struct _RECT {
  long left;
  long top;
  long right;
  long bottom;
} RECT, *PRECT;

typedef struct tagPOINT {
  long x;
  long y;
} POINT, *PPOINT, *LPPOINT;

#define WM_USER 0x0400

#define TRUE 1
#define FALSE 0
#define NONE 0
#define CONST const

typedef dirent DirEntryType;

#define _O_WRONLY O_WRONLY
#define _O_RDONLY O_RDONLY
#define _O_TRUNC O_TRUNC
#define _O_CREAT O_CREAT
#define _S_IWRITE S_IWRITE
#define _S_IREAD S_IREAD
#define _O_BINARY 0
#define O_BINARY 0
#define O_SEQUENTIAL 0
#define SH_DENYWR 0

#define _stricmp stricmp
#define strcmpi stricmp
#define stricmp strcasecmp
#define strncpy_s(dest, size, source, num) strncpy(dest, source, num)
#define strcpy_s(dest, num, source) strcpy(dest, source)
#define _vsnprintf vsnprintf
#define _alloca alloca
#define _snprintf snprintf
#define sprintf_s(buffer, buffer_size, stringbuffer, ...) sprintf(buffer, stringbuffer, ##__VA_ARGS__)
#define GetProcAddress(handle, name) dlsym(handle, name)
#define _chdir chdir
#define _strnicmp strnicmp
#define strnicmp strncasecmp
#define _getcwd getcwd
#define _snwprintf swprintf
#define swprintf_s swprintf
#define wcsicmp _wcsicmp
#define _wcsicmp wcscmp
#define _tempnam tempnam
#define _unlink unlink
#define _access access
#define _open open
#define _close close
#define _sopen open
#define _sopen_s(handle, filename, ...) open(filename, O_RDONLY)
#define _fdopen fdopen
#define _rmdir rmdir
#define _write write
#define _strupr strupr
#define _read read
#define _set_new_handler std::set_new_handler
#define _finite isfinite
#define _mkdir(dir) mkdir(dir, S_IRWXU)
#define _wtoi(arg) wcstol(arg, NULL, 10)
#define _wtoi64(arg) wcstoll(arg, NULL, 10)
#undef min
#undef max
#define __max(a, b) std::max(a, b)
#define __min(a, b) std::min(a, b)

#define ZeroMemory(p, sz) memset((p), 0, (sz))
#define CopyMemory(d, s, n) memcpy(d, s, n)

#define RGB(r,g,b) ( ((DWORD)(BYTE)r)|((DWORD)((BYTE)g)<<8)|((DWORD)((BYTE)b)<<16) )
#define SUCCEEDED(hr) (((HRESULT)(hr)) >= 0)
#define FAILED(hr) (((HRESULT)(hr)) < 0)
#define S_OK 0x00000000
#define S_FALSE 0x10000000
#define E_FAIL 0x80004005

// TODO: Move input stuff to xrEngine
#define DIK_1            SDLK_1
#define DIK_2            SDLK_2
#define DIK_3            SDLK_3
#define DIK_4            SDLK_4
#define DIK_5            SDLK_5
#define DIK_6            SDLK_6
#define DIK_7            SDLK_7
#define DIK_8            SDLK_8
#define DIK_9            SDLK_9
#define DIK_0            SDLK_0
#define DIK_MINUS        SDLK_MINUS
#define DIK_EQUALS       SDLK_EQUALS

// 1st alpha row
#define DIK_Q            SDLK_q
#define DIK_W            SDLK_w
#define DIK_E            SDLK_e
#define DIK_R            SDLK_r
#define DIK_T            SDLK_t
#define DIK_Y            SDLK_y
#define DIK_U            SDLK_u
#define DIK_I            SDLK_i
#define DIK_O            SDLK_o
#define DIK_P            SDLK_p
#define DIK_LBRACKET     SDLK_RIGHTPAREN
#define DIK_RBRACKET     SDLK_RIGHTPAREN
#define DIK_BACKSLASH    SDLK_BACKSLASH

// 2nd alpha row
#define DIK_A            SDLK_a
#define DIK_S            SDLK_s
#define DIK_D            SDLK_d
#define DIK_F            SDLK_f
#define DIK_G            SDLK_g
#define DIK_H            SDLK_h
#define DIK_J            SDLK_j
#define DIK_K            SDLK_k
#define DIK_L            SDLK_l
#define DIK_SEMICOLON    SDLK_SEMICOLON
#define DIK_APOSTROPHE   SDLK_QUOTE

// 3rd alpha row
#define DIK_Z            SDLK_z
#define DIK_X            SDLK_x
#define DIK_C            SDLK_c
#define DIK_V            SDLK_v
#define DIK_B            SDLK_b
#define DIK_N            SDLK_n
#define DIK_M            SDLK_m
#define DIK_COMMA        SDLK_COMMA
#define DIK_PERIOD       SDLK_PERIOD
#define DIK_SLASH        SDLK_SLASH

// row with F-keys
#define DIK_F1           SDLK_F1
#define DIK_F2           SDLK_F2
#define DIK_F3           SDLK_F3
#define DIK_F4           SDLK_F4
#define DIK_F5           SDLK_F5
#define DIK_F6           SDLK_F6
#define DIK_F7           SDLK_F7
#define DIK_F8           SDLK_F8
#define DIK_F9           SDLK_F9
#define DIK_F10          SDLK_F10
#define DIK_F11          SDLK_F11
#define DIK_F12          SDLK_F12

// extra keys
#define DIK_ESCAPE       SDLK_ESCAPE
#define DIK_TILDE        SDLK_BACKQUOTE
#define DIK_BACKSPACE    SDLK_BACKSPACE
#define DIK_TAB          SDLK_TAB
#define DIK_CAPSLOCK     SDLK_CAPSLOCK
#define DIK_ENTER        SDLK_RETURN
#define DIK_SPACE        SDLK_SPACE
#define DIK_GRAVE        DIK_TILDE
#define DIK_RETURN       DIK_ENTER
#define DIK_BACK         DIK_BACKSPACE

// modifier keys
#define DIK_LSHIFT       SDLK_LSHIFT
#define DIK_RSHIFT       SDLK_RSHIFT
#define DIK_LCONTROL     SDLK_LCTRL
#define DIK_RCONTROL     SDLK_RCTRL
#define DIK_LALT         SDLK_LALT
#define DIK_RALT         SDLK_RALT

// navigation keys
#define DIK_ARROWUP      SDLK_UP
#define DIK_ARROWDOWN    SDLK_DOWN
#define DIK_ARROWLEFT    SDLK_LEFT
#define DIK_ARROWRIGHT   SDLK_RIGHT
#define DIK_INSERT       SDLK_INSERT
#define DIK_DELETE       SDLK_DELETE
#define DIK_HOME         SDLK_HOME
#define DIK_END          SDLK_END
#define DIK_PAGEUP       SDLK_PAGEUP
#define DIK_PAGEDOWN     SDLK_PAGEDOWN
#define DIK_PRINTSCR     SDLK_PRINTSCREEN
#define DIK_SCROLLLOCK   SDLK_SCROLLLOCK
#define DIK_PAUSE        SDLK_PAUSE
#define DIK_PRIOR DIK_PAGEUP
#define DIK_NEXT DIK_PAGEDOWN
#define DIK_UP DIK_ARROWUP
#define DIK_DOWN DIK_ARROWDOWN
#define DIK_LEFT DIK_ARROWLEFT
#define DIK_RIGHT DIK_ARROWRIGHT

// numpad numbers
#define DIK_NUM0         SDLK_KP_0
#define DIK_NUM1         SDLK_KP_1
#define DIK_NUM2         SDLK_KP_2
#define DIK_NUM3         SDLK_KP_3
#define DIK_NUM4         SDLK_KP_4
#define DIK_NUM5         SDLK_KP_5
#define DIK_NUM6         SDLK_KP_6
#define DIK_NUM7         SDLK_KP_7
#define DIK_NUM8         SDLK_KP_8
#define DIK_NUM9         SDLK_KP_9
#define DIK_NUMDECIMAL   SDLK_KP_PERIOD
#define DIK_NUMPAD0 DIK_NUM0
#define DIK_NUMPAD1 DIK_NUM1
#define DIK_NUMPAD2 DIK_NUM2
#define DIK_NUMPAD3 DIK_NUM3
#define DIK_NUMPAD4 DIK_NUM4
#define DIK_NUMPAD5 DIK_NUM5
#define DIK_NUMPAD6 DIK_NUM6
#define DIK_NUMPAD7 DIK_NUM7
#define DIK_NUMPAD8 DIK_NUM8
#define DIK_NUMPAD9 DIK_NUM9

// numpad keys
#define DIK_NUMLOCK      SDLK_NUMLOCKCLEAR
#define DIK_NUMSLASH     SDLK_KP_DIVIDE
#define DIK_NUMMULTIPLY  SDLK_KP_MULTIPLY
#define DIK_NUMMINUS     SDLK_KP_MINUS
#define DIK_NUMPLUS      SDLK_KP_PLUS
#define DIK_NUMENTER     SDLK_KP_ENTER
#define DIK_NUMPADENTER  DIK_NUMENTER
#define DIK_MULTIPLY     DIK_NUMMULTIPLY
#define DIK_NUMPADMINUS  SDLK_KP_MINUS
#define DIK_NUMPADPLUS   SDLK_KP_PLUS
#define DIK_NUMPADSTAR   SDLK_KP_MULTIPLY
#define DIK_NUMPADSLASH  SDLK_KP_DIVIDE
#define DIK_NUMPADPERIOD SDLK_KP_PERIOD

// mouse buttons
#define DIK_MOUSE1       -1
#define DIK_MOUSE2       -1
#define DIK_MOUSE3       -1
#define DIK_MOUSE4       -1
#define DIK_MOUSE5       -1
#define DIK_MOUSEWHEELUP -1
#define DIK_MOUSEWHEELDOWN -1

//#define MOUSE_LBUTTON 1
//#define MOUSE_RBUTTON 2
//#define MOUSE_MBUTTON 3
#include "d3d9_posix_stubbs.h"
