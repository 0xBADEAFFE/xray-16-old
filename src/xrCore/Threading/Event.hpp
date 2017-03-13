#pragma once
#include "xrCore/_types.h"
#include "xrCore/xrCore_impexp.h"

class XRCORE_API Event
{
private:
#ifdef WINDOWS
    void *handle;
#else
    bool signalled;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
#endif // WINDOWS

public:
    Event() noexcept;
    ~Event() noexcept;

    // Reset the event to the unsignalled state.
    void Reset() noexcept;
    // Set the event to the signalled state.
    void Set() noexcept;
    // Wait indefinitely for the object to become signalled.
    void Wait() const noexcept;
    // Wait, with a time limit, for the object to become signalled.
    bool Wait(u32 millisecondsTimeout) const noexcept;

// NOTE: This is not used anywhere
#ifdef WINDOWS
    void *GetHandle() const noexcept { return handle; }
#endif
};
