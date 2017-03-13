#ifndef SoundRender_CoreAH
#define SoundRender_CoreAH
#pragma once

#include "SoundRender_Core.h"
#include "OpenALDeviceList.h"
#ifdef WINDOWS
#define EAXSUPPORT
#include <eax/eax.h>
#endif // WINDOWS


#ifdef DEBUG
#	define A_CHK(expr)		{ alGetError(); 		expr; ALenum err_=alGetError(); 			VERIFY2(err_==AL_NO_ERROR, (LPCSTR)alGetString(err_)); }
#	define AC_CHK(expr)		{ alcGetError(pDevice); expr; ALCenum err_=alcGetError(pDevice); 	VERIFY2(err_==ALC_NO_ERROR,(LPCSTR)alcGetString(pDevice,err_)); }
#else
#	define A_CHK(expr)		{ expr; }
#	define AC_CHK(expr)		{ expr; }
#endif

class CSoundRender_CoreA: public CSoundRender_Core
{
	typedef CSoundRender_Core inherited;
#ifdef EAXSUPPORT
	EAXSet					eaxSet;					// EAXSet function, retrieved if EAX Extension is supported
	EAXGet					eaxGet;					// EAXGet function, retrieved if EAX Extension is supported
#endif // EAXSUPPORT
	ALCdevice* 				pDevice;
  ALCcontext*				pContext;
	ALDeviceList*			pDeviceList;

	struct SListener{
		Fvector				position;
		Fvector				orientation[2];
	};
	SListener				Listener;

    BOOL 					EAXQuerySupport			(BOOL bDeferred, const GUID* guid, u32 prop, void* val, u32 sz);
	BOOL 					EAXTestSupport			(BOOL bDeferred);
protected:
	virtual void			i_eax_set				(const GUID* guid, u32 prop, void* val, u32 sz);
	virtual void			i_eax_get				(const GUID* guid, u32 prop, void* val, u32 sz);
	virtual void			update_listener			( const Fvector& P, const Fvector& D, const Fvector& N, float dt );
public:
						    CSoundRender_CoreA		();
    virtual					~CSoundRender_CoreA		();

	virtual void			_initialize				();
	virtual void			_clear					( );
	virtual void			_restart				( );

	virtual void			set_master_volume		( float f		);

	virtual const Fvector&	listener_position		( ){return Listener.position;}
};
extern CSoundRender_CoreA* SoundRenderA;
#endif
