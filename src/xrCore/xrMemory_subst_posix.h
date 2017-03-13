#ifndef XRMEMORY_SUBST_POSIX
#define XRMEMORY_SUBST_POSIX

template <class T>
IC void xr_delete(T*& ptr)
{
    if (ptr)
    {
        delete ptr;
        const_cast<T*&>(ptr) = NULL;
    }
}
#endif // XRMEMORY_SUBST_POSIX
