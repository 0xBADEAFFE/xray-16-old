#include "stdafx.h"
#include "Include/xrRender/DrawUtils.h"
#include "Render.h"
#include "IGame_Persistent.h"
#include "XR_IOConsole.h"
#ifdef CONFIG_USE_SDL
#include <SDL2/SDL.h>
#endif //CONFIG_USE_SDL

void CRenderDevice::Destroy(void)
{
    if (!b_is_Ready)
        return;
    Log("Destroying Direct3D...");
#ifdef CONFIG_USE_SDL
    SDL_ShowCursor(TRUE);
#else
    ShowCursor(TRUE);
#endif // CONFIG_USE_SDL
    GlobalEnv.Render->ValidateHW();
    GlobalEnv.DU->OnDeviceDestroy();
    b_is_Ready = FALSE;
    Statistic->OnDeviceDestroy();
    GlobalEnv.Render->destroy();
    GlobalEnv.Render->OnDeviceDestroy(false);
    Memory.mem_compact();
    GlobalEnv.Render->DestroyHW();
    seqRender.R.clear();
    seqAppActivate.R.clear();
    seqAppDeactivate.R.clear();
    seqAppStart.R.clear();
    seqAppEnd.R.clear();
    seqFrame.R.clear();
    seqFrameMT.R.clear();
    seqDeviceReset.R.clear();
    seqParallel.clear();
    xr_delete(Statistic);
}

#include "IGame_Level.h"
#include "CustomHUD.h"
extern BOOL bNeed_re_create_env;

void CRenderDevice::Reset(bool precache)
{
    u32 dwWidth_before = dwWidth;
    u32 dwHeight_before = dwHeight;
#ifdef CONFIG_USE_SDL
    SDL_ShowCursor(TRUE);
#else
    ShowCursor(TRUE);
#endif // CONFIG_USE_SDL
    u32 tm_start = TimerAsync();
    GlobalEnv.Render->Reset(m_hWnd, dwWidth, dwHeight, fWidth_2, fHeight_2);
    if (g_pGamePersistent)
        g_pGamePersistent->Environment().bNeed_re_create_env = TRUE;
    _SetupStates();
    if (precache)
        PreCache(20, true, false);
    u32 tm_end = TimerAsync();
    Msg("*** RESET [%d ms]", tm_end - tm_start);
    // TODO: Remove this! It may hide crash
    Memory.mem_compact();
#ifndef DEDICATED_SERVER
#ifdef CONFIG_USE_SDL
    SDL_ShowCursor(FALSE);
#else
    ShowCursor(FALSE);
#endif // CONFIG_USE_SDL
#endif
    seqDeviceReset.Process(rp_DeviceReset);
    if (dwWidth_before != dwWidth || dwHeight_before != dwHeight)
        seqResolutionChanged.Process(rp_ScreenResolutionChanged);
}
