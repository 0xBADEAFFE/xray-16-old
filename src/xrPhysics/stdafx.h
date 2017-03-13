#pragma once

#define	MTL_EXPORT_API
#define ENGINE_API
#define DLL_API
#define ECORE_API

#include "xrCore/xrCore.h"
#include "xrServerEntities/smart_cast.h"
#include "xrCDB/xrCDB.h"
#include "xrSound/Sound.h"
#include "xrEngine/GameMtlLib.h"
#include "xrCore/_std_extensions.h"

#include "xrPhysics.h"
#include "Include/xrAPI/xrAPI.h"
#if defined(WINDOWS) && defined(DEBUG)
#include <d3d9types.h>
#endif

#pragma comment( lib, "xrCore.lib"	)

// XXX: TODO: What on earth have CODE to do in a PCH header like this?!

//IC IGame_Level &GLevel()
//{
//	VERIFY( g_pGameLevel );
//	return *g_pGameLevel;
//}

class CGameMtlLibrary;
IC CGameMtlLibrary &GMLibrary()
{
    VERIFY(GlobalEnv.PGMLib);
    return *GlobalEnv.PGMLib;
}
