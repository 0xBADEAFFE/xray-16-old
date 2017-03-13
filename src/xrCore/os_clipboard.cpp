////////////////////////////////////////////////////////////////////////////
// Module : os_clipboard.cpp
// Created : 21.02.2008
// Author : Evgeniy Sokolov
// Description : os clipboard class implementation
////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#pragma hdrstop
#include "os_clipboard.h"
#include "xrCore/_std_extensions.h"

#ifdef CONFIG_USE_SDL
#include <SDL2/SDL_clipboard.h>
#endif // CONFIG_USE_SDL

void os_clipboard::copy_to_clipboard(LPCSTR buf)
{
#ifdef CONFIG_USE_SDL
    SDL_SetClipboardText(buf);
#else
    if (!OpenClipboard(0))
        return;
    u32 handle_size = (xr_strlen(buf) + 1) * sizeof(char);
    HGLOBAL handle = GlobalAlloc(GHND, handle_size);
    if (!handle)
    {
        CloseClipboard();
        return;
    }

    char* memory = (char*)GlobalLock(handle);
    xr_strcpy(memory, handle_size, buf);
    GlobalUnlock(handle);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, handle);
    CloseClipboard();
#endif // CONFIG_USE_SDL
}

void os_clipboard::paste_from_clipboard(LPSTR buffer, u32 const& buffer_size)
{
    VERIFY(buffer);
    VERIFY(buffer_size > 0);

#ifdef CONFIG_USE_SDL
    char *text = SDL_GetClipboardText();
    xr_strcpy(buffer, buffer_size, text);
    SDL_free(text);
#else
    if (!OpenClipboard(0))
        return;

    HGLOBAL hmem = GetClipboardData(CF_TEXT);
    if (!hmem)
        return;

    LPCSTR clipdata = (LPCSTR)GlobalLock(hmem);
    strncpy_s(buffer, buffer_size, clipdata, buffer_size - 1);
    buffer[buffer_size - 1] = 0;
    for (u32 i = 0; i < strlen(buffer); ++i)
    {
        char c = buffer[i];
        if (((isprint(c) == 0) && (c != char(-1))) || c == '\t' || c == '\n')// "�" = -1
        {
            buffer[i] = ' ';
        }
    }

    GlobalUnlock(hmem);
    CloseClipboard();
#endif // CONFIG_USE_SDL
}

void os_clipboard::update_clipboard(LPCSTR string)
{
#ifdef CONFIG_USE_SDL
    if (!SDL_HasClipboardText())
    {
        SDL_SetClipboardText(string);
        return;
    }

    char *text = SDL_GetClipboardText();
    const int buffer_size = strlen(string) + strlen(text);
    char buffer[buffer_size];
    xr_strcpy(buffer, buffer_size, text);
    xr_strcat(buffer, buffer_size, string);
    copy_to_clipboard(buffer);
    SDL_free(text);
#else
    if (!OpenClipboard(0))
        return;

    HGLOBAL handle = GetClipboardData(CF_TEXT);
    if (!handle)
    {
        CloseClipboard();
        copy_to_clipboard(string);
        return;
    }

    LPSTR memory = (LPSTR)GlobalLock(handle);
    int memory_length = (int)strlen(memory);
    int string_length = (int)strlen(string);
    int buffer_size = (memory_length + string_length + 1) * sizeof(char);
#ifndef _EDITOR
    LPSTR buffer = (LPSTR)_alloca(buffer_size);
#else
    LPSTR buffer = (LPSTR)xr_alloc<char>( buffer_size );
#endif // _EDITOR
    xr_strcpy(buffer, buffer_size, memory);
    GlobalUnlock(handle);

    xr_strcat(buffer, buffer_size, string);
    CloseClipboard();
    copy_to_clipboard(buffer);
#ifdef _EDITOR
    xr_free (buffer);
#endif // _EDITOR
#endif // CONFIG_USE_SDL
}
