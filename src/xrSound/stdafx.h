// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#ifndef stdafxH
#define stdafxH
#pragma once

#include "xrCore/xrCore.h"
#include "xrCore/_std_extensions.h"

#ifdef WINDOWS
// mmsystem.h
#define MMNOSOUND
#define MMNOMIDI
#define MMNOAUX
#define MMNOMIXER
#define MMNOJOY
#include <mmsystem.h>

// mmreg.h
#define NOMMIDS
#define NONEWRIFF
#define NOJPEGDIB
#define NONEWIC
#define NOBITMAP
#include <mmreg.h>
#else //POSIX
//NOTE: Move to different place
#define EAX_ENVIRONMENT_GENERIC 0
#define EAXLISTENER_DEFAULTENVIRONMENT            EAX_ENVIRONMENT_GENERIC
#define EAXLISTENER_MINENVIRONMENTSIZE            1.0f
#define EAXLISTENER_MAXENVIRONMENTSIZE            100.0f
#define EAXLISTENER_DEFAULTENVIRONMENTSIZE        7.5f

#define EAXLISTENER_MINENVIRONMENTDIFFUSION       0.0f
#define EAXLISTENER_MAXENVIRONMENTDIFFUSION       1.0f
#define EAXLISTENER_DEFAULTENVIRONMENTDIFFUSION   1.0f

#define EAXLISTENER_MINROOM                       (-10000)
#define EAXLISTENER_MAXROOM                       0
#define EAXLISTENER_DEFAULTROOM                   (-1000)

#define EAXLISTENER_MINROOMHF                     (-10000)
#define EAXLISTENER_MAXROOMHF                     0
#define EAXLISTENER_DEFAULTROOMHF                 (-100)

#define EAXLISTENER_MINROOMLF                     (-10000)
#define EAXLISTENER_MAXROOMLF                     0
#define EAXLISTENER_DEFAULTROOMLF                 0

#define EAXLISTENER_MINDECAYTIME                  0.1f
#define EAXLISTENER_MAXDECAYTIME                  20.0f
#define EAXLISTENER_DEFAULTDECAYTIME              1.49f

#define EAXLISTENER_MINDECAYHFRATIO               0.1f
#define EAXLISTENER_MAXDECAYHFRATIO               2.0f
#define EAXLISTENER_DEFAULTDECAYHFRATIO           0.83f

#define EAXLISTENER_MINDECAYLFRATIO               0.1f
#define EAXLISTENER_MAXDECAYLFRATIO               2.0f
#define EAXLISTENER_DEFAULTDECAYLFRATIO           1.00f

#define EAXLISTENER_MINREFLECTIONS                (-10000)
#define EAXLISTENER_MAXREFLECTIONS                1000
#define EAXLISTENER_DEFAULTREFLECTIONS            (-2602)

#define EAXLISTENER_MINREFLECTIONSDELAY           0.0f
#define EAXLISTENER_MAXREFLECTIONSDELAY           0.3f
#define EAXLISTENER_DEFAULTREFLECTIONSDELAY       0.007f

#define EAXLISTENER_MINREVERB                     (-10000)
#define EAXLISTENER_MAXREVERB                     2000
#define EAXLISTENER_DEFAULTREVERB                 200

#define EAXLISTENER_MINREVERBDELAY                0.0f
#define EAXLISTENER_MAXREVERBDELAY                0.1f
#define EAXLISTENER_DEFAULTREVERBDELAY            0.011f

#define EAXLISTENER_MINECHOTIME                   0.075f
#define EAXLISTENER_MAXECHOTIME	                  0.25f
#define EAXLISTENER_DEFAULTECHOTIME               0.25f

#define EAXLISTENER_MINECHODEPTH                  0.0f
#define EAXLISTENER_MAXECHODEPTH                  1.0f
#define EAXLISTENER_DEFAULTECHODEPTH              0.0f

#define EAXLISTENER_MINMODULATIONTIME             0.04f
#define EAXLISTENER_MAXMODULATIONTIME             4.0f
#define EAXLISTENER_DEFAULTMODULATIONTIME         0.25f

#define EAXLISTENER_MINMODULATIONDEPTH            0.0f
#define EAXLISTENER_MAXMODULATIONDEPTH            1.0f
#define EAXLISTENER_DEFAULTMODULATIONDEPTH        0.0f

#define EAXLISTENER_MINAIRABSORPTIONHF            (-100.0f)
#define EAXLISTENER_MAXAIRABSORPTIONHF            0.0f
#define EAXLISTENER_DEFAULTAIRABSORPTIONHF        (-5.0f)

#define EAXLISTENER_MINHFREFERENCE                1000.0f
#define EAXLISTENER_MAXHFREFERENCE                20000.0f
#define EAXLISTENER_DEFAULTHFREFERENCE            5000.0f

#define EAXLISTENER_MINLFREFERENCE                20.0f
#define EAXLISTENER_MAXLFREFERENCE                1000.0f
#define EAXLISTENER_DEFAULTLFREFERENCE            250.0f

#define EAXLISTENER_MINROOMROLLOFFFACTOR          0.0f
#define EAXLISTENER_MAXROOMROLLOFFFACTOR          10.0f
#define EAXLISTENER_DEFAULTROOMROLLOFFFACTOR      0.0f

typedef void log_fn_ptr_type(char*);
extern log_fn_ptr_type*	pLog;

#define WAVE_FORMAT_PCM	0x0001
/*
typedef struct {
  WORD  wFormatTag;
  WORD  nChannels;
  DWORD nSamplesPerSec;
  DWORD nAvgBytesPerSec;
  WORD  nBlockAlign;
  WORD  wBitsPerSample;
  WORD  cbSize;
} WAVEFORMATEX;
*/

typedef struct _GUID {
  DWORD Data1;
  WORD  Data2;
  WORD  Data3;
  BYTE  Data4[8];
} GUID;
#endif // WINDOWS

#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

#include "xrCDB/xrCDB.h"
#include "Sound.h"

#undef ENGINE_API

#include "xrCore/xr_resource.h"

#ifdef _EDITOR
#include "ETools.h"
#endif
// TODO: reference additional headers your program requires here
#endif
