#ifndef FILE_STREAM_READER_H
#define FILE_STREAM_READER_H

#include "Stream_Reader.h"

class CFileStreamReader : public CStreamReader
{
private:
    typedef CStreamReader inherited;

private:
#ifdef WINDOWS
    HANDLE m_file_handle;
#else // POSIX
    int fd;
#endif // WINDOWS

public:
    virtual void construct(LPCSTR file_name, const u32& window_size);
    virtual void destroy();
};

#endif // FILE_STREAM_READER_H
