#include "stdafx.h"
#pragma hdrstop

#include "cpuid.h"

/***
*
* int _cpuid (_p_info *pinfo)
*
* Entry:
*
*   pinfo: pointer to _p_info, NULL is not allowed!
*
* Exit:
*
*   Returns int with capablity bit set.
*
****************************************************/
#ifdef _EDITOR
int _cpuid( _processor_info *pinfo )
{
    ZeroMemory(pinfo, sizeof(_processor_info));

    pinfo->feature = _CPU_FEATURE_MMX | _CPU_FEATURE_SSE;
    return pinfo->feature;
}
#else

int _cpuid( _processor_info *pinfo )
{
	ZeroMemory(pinfo, sizeof(_processor_info));

  unsigned int regs[4];

  // Get vendor name
  nativeCpuId(0, regs);
  xr_strcat(pinfo->v_name, 4, (const char *)&regs[1]);
  xr_strcat(pinfo->v_name, 4, (const char *)&regs[3]);
  xr_strcat(pinfo->v_name, 4, (const char *)&regs[2]);

  // Get model name
  for(unsigned int i = 0x80000002; i <= 0x80000004; i++)
  {
      nativeCpuId(i, regs);
      xr_strcat(pinfo->model_name, 4, (const char *)&regs[0]);
      xr_strcat(pinfo->model_name, 4, (const char *)&regs[1]);
      xr_strcat(pinfo->model_name, 4, (const char *)&regs[2]);
      xr_strcat(pinfo->model_name, 4, (const char *)&regs[3]);
  }

  // Get features
  nativeCpuId(1, regs);
  unsigned int cpuFeatures = regs[3]; // edx
  unsigned int cpuFeaturesExtended = regs[2]; // ecx

  pinfo->feature = cpuFeatures & _CPU_FEATURE_MMX;
  pinfo->feature = cpuFeatures & _CPU_FEATURE_SSE;
  pinfo->feature = cpuFeatures & _CPU_FEATURE_SSE2;
  pinfo->feature = cpuFeatures & _CPU_FEATURE_HTT;

  pinfo->feature = cpuFeaturesExtended & _CPU_FEATURE_SSE3;
  pinfo->feature = cpuFeaturesExtended & _CPU_FEATURE_SSSE3;
  pinfo->feature = cpuFeaturesExtended & _CPU_FEATURE_SSE4_1;
  pinfo->feature = cpuFeaturesExtended & _CPU_FEATURE_SSE4_2;
  pinfo->feature = cpuFeaturesExtended & _CPU_FEATURE_MWAIT;

  pinfo->family =(regs[0] >> 8) & 0xF;
  pinfo->model = (regs[0] >> 4) & 0xF;
  pinfo->stepping = regs[0] & 0xF;

  int cpu_cores;
#ifdef WINDOWS
  SYSTEM_INFO systeminfo;
  GetSystemInfo( &systeminfo );
  cpu_cores = systeminfo.dwNumberOfProcessors;
#elif defined(LINUX) // POSIX
  cpu_cores = sysconf( _SC_NPROCESSORS_ONLN );
#else
#warning Get cpu_cores not implemented
  cpu_cores = 1;
#endif // WINDOWS

  if (cpuFeatures & _CPU_FEATURE_HTT)
  {
    pinfo->n_cores = cpu_cores / 2;
  }
  else
  {
    pinfo->n_cores = cpu_cores;
  }

  pinfo->n_threads = std::thread::hardware_concurrency();

  // TODO: Implement
  // pinfo->affinity_mask =

	return pinfo->feature;
}
#endif // _EDITOR
