#pragma once

#ifndef M_NOSTDCONTAINERS_EXT
#ifndef _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#endif
#include <hash_map>

template <typename K, class V, class _Traits = stdext::hash_compare<K, std::less<K> >, typename allocator = xalloc<std::pair<K, V> > >
class xr_hash_map : public stdext::hash_map < K, V, _Traits, allocator > { public: u32 size() const { return (u32)__super::size(); } };
#else
#ifdef WINDOWS
#include <hash_map>

#define xr_hash_map std::hash_map
#else // POSIX
#include <unordered_map>

#define xr_hash_map std::unordered_map
#endif // WINDOWS
#endif // M_NOSTDCONTAINERS_EXT
