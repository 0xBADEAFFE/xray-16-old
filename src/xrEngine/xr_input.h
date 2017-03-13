#ifndef __XR_INPUT__
#define __XR_INPUT__

#ifndef CONFIG_USE_SDL
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#endif

class ENGINE_API IInputReceiver;

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//�������� ������
const int mouse_device_key = 1;
const int keyboard_device_key = 2;
const int all_device_key = mouse_device_key | keyboard_device_key;
const int default_key = mouse_device_key | keyboard_device_key;

class ENGINE_API CInput
#ifndef M_BORLAND
    :
    public pureFrame,
    public pureAppActivate,
    public pureAppDeactivate
#endif
{
public:
    enum
    {
        COUNT_MOUSE_BUTTONS = 8,
        COUNT_MOUSE_AXIS = 3,
        COUNT_KB_BUTTONS = 256
    };
    struct sxr_mouse
    {
#ifndef CONFIG_USE_SDL
        DIDEVCAPS capabilities;
        DIDEVICEINSTANCE deviceInfo;
        DIDEVICEOBJECTINSTANCE objectInfo;
#endif
        u32 mouse_dt;

    };
    struct sxr_key
    {
#ifndef CONFIG_USE_SDL
        DIDEVCAPS capabilities;
        DIDEVICEINSTANCE deviceInfo;
        DIDEVICEOBJECTINSTANCE objectInfo;
#endif
    };
    struct InputStatistics
    {
        CStatTimer FrameTime;

        void FrameStart() { FrameTime.FrameStart(); }
        void FrameEnd() { FrameTime.FrameEnd(); }
    };
private:
    BENCH_SEC_SCRAMBLEMEMBER1
#ifndef CONFIG_USE_SDL
    LPDIRECTINPUT8 pDI; // The DInput object
    LPDIRECTINPUTDEVICE8 pMouse; // The DIDevice7 interface
    LPDIRECTINPUTDEVICE8 pKeyboard; // The DIDevice7 interface

    HRESULT CreateInputDevice(LPDIRECTINPUTDEVICE8* device, GUID guidDevice,
                              const DIDATAFORMAT* pdidDataFormat, u32 dwFlags,
                              u32 buf_size);
#endif
    u32 timeStamp[COUNT_MOUSE_AXIS];
    u32 timeSave[COUNT_MOUSE_AXIS];
    int offs[COUNT_MOUSE_AXIS];
    BOOL mouseState[COUNT_MOUSE_BUTTONS];
    BOOL KBState[COUNT_KB_BUTTONS];

    // xr_stack<IInputReceiver*> cbStack;
    xr_vector<IInputReceiver*> cbStack;

    void MouseUpdate();
    void KeyUpdate();

    InputStatistics stats;

public:
    sxr_mouse mouse_property;
    sxr_key key_property;
    u32 dwCurTime;

    const InputStatistics &GetStats() const { return stats; }
    void DumpStatistics(class IGameFont &font, class IPerformanceAlert *alert);
    void SetAllAcquire(BOOL bAcquire = TRUE);
    void SetMouseAcquire(BOOL bAcquire);
    void SetKBDAcquire(BOOL bAcquire);

    void iCapture(IInputReceiver* pc);
    void iRelease(IInputReceiver* pc);
    BOOL iGetAsyncKeyState(int dik);
    BOOL iGetAsyncBtnState(int btn);
    void iGetLastMouseDelta(Ivector2& p) { p.set(offs[0], offs[1]); }
    void ClipCursor(bool clip);

    CInput(BOOL bExclusive = true, int deviceForInit = default_key);
    ~CInput();

    virtual void OnFrame(void);
    virtual void OnAppActivate(void);
    virtual void OnAppDeactivate(void);

    IInputReceiver* CurrentIR();

public:
    void exclusive_mode(const bool& exclusive);
    IC bool get_exclusive_mode();
    void unacquire();
    void acquire(const bool& exclusive);
    bool get_dik_name(int dik, LPSTR dest, int dest_sz);

    void feedback(u16 s1, u16 s2, float time);
};

extern ENGINE_API CInput* pInput;

#endif //__XR_INPUT__