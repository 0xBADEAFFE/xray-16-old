#ifndef STDAFX_3DA
#define STDAFX_3DA
#pragma once

#ifdef _EDITOR
#include "editors/ECore/stdafx.h"
#else // _EDITOR

#ifndef NDEBUG
#ifndef INGAME_EDITOR
#define INGAME_EDITOR
#endif // INGAME_EDITOR
#endif // NDEBUG

#if defined(WINDOWS) && defined(INGAME_EDITOR)
#define _WIN32_WINNT 0x0550
#endif // WINDOWS && INGAME_EDITOR

#include "xrCore/xrCore.h"
#include "Include/xrAPI/xrAPI.h"
#include "xrCore/_std_extensions.h"

#define ECORE_API

// Our headers
#include "Engine.h"
#include "defines.h"
#ifndef NO_XRLOG
#include "xrCore/log.h"
#endif // NO_XRLOG
#include "device.h"
#include "xrCore/FS.h"

#include "xrCDB/xrXRC.h"

#include "xrSound/Sound.h"
#ifndef WINDOWS
#warning OpenAutomate is disabled on posix
#else
// TODO: Make usable on Linux
#define USEOPENAUTOMATE
#endif  // WINDOWS

extern ENGINE_API CInifile* pGameIni;

#ifdef WINDOWS
#pragma comment( lib, "xrCore.lib" )
#pragma comment( lib, "xrCDB.lib" )
#pragma comment( lib, "xrSound.lib" )
#pragma comment(lib, "xrScriptEngine.lib")
#pragma comment( lib, "xrAPI.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "dinput8.lib" )
#pragma comment( lib, "dxguid.lib" )
#endif // WINDOWS

// XXX: move to script engine headers
#ifndef DEBUG
#define LUABIND_NO_ERROR_CHECKING
#endif // DEBUG
#define LUABIND_DONT_COPY_STRINGS

#define READ_IF_EXISTS(ltx,method,section,name,default_value)\
 (((ltx)->line_exist(section, name)) ? ((ltx)->method(section, name)) : (default_value))

#endif // !M_BORLAND
#endif // !defined STDAFX_3DA
