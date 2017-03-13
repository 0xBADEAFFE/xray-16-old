#include "stdafx.h"
#include "Event.hpp"
#ifdef WINDOWS
#include <windows.h>

Event::Event() noexcept
{
  handle = (void*)CreateEvent(NULL, FALSE, FALSE, NULL);
}

Event::~Event() noexcept
{
  CloseHandle(handle);
}

void Event::Reset() noexcept
{
  ResetEvent(handle);
}

void Event::Set() noexcept
{
  SetEvent(handle);
}

void Event::Wait() const noexcept
{
  WaitForSingleObject(handle, INFINITE);
}

bool Event::Wait(u32 millisecondsTimeout) const noexcept
{
  return WaitForSingleObject(handle, millisecondsTimeout)!=WAIT_TIMEOUT;
}
else // POSIX
Event::Event() noexcept
{
    signalled = false;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
}

Event::~Event() noexcept
{
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);
}

void Event::Reset() noexcept
{
  pthread_mutex_lock(&mutex);
  signalled = false;
  pthread_mutex_unlock(&mutex);
}

void Event::Set() noexcept
{
  pthread_mutex_lock(&mutex);
  signalled = true;
  pthread_mutex_unlock(&mutex);
  pthread_cond_signal(&cond);
}

void Event::Wait() const noexcept
{
  pthread_mutex_lock(&mutex);
  while (!signalled)
  {
    pthread_cond_wait(&cond, &mutex);
  }
  signalled = false;
  pthread_mutex_unlock(&mutex);
}

bool Event::Wait(u32 millisecondsTimeout) const noexcept
{
  bool retval = false;

  clock_gettime(CLOCK_REALTIME, &abstime);
  abstime.tv_sec += millisecondsTimeout;

  pthread_mutex_lock(&mutex);
  while (!signalled)
  {
    retval = ( pthread_cond_timedwait(&cond, &mutex, &abstime) == 0 ) ? true : false;
  }
  signalled = false;
  pthread_mutex_unlock(&mutex);

  return retval;
}
#endif // WINDOWS
