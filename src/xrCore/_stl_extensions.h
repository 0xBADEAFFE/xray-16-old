#pragma once
#ifndef _STL_EXTENSIONS_H
#define _STL_EXTENSIONS_H

#include <string>
#include <vector>
#include <list>
#include <set>
#include "_types.h"
#include "_rect.h"
#include "_plane.h"
#include "_vector2.h"
#include "_vector3d.h"
#include "_color.h"
#include "_std_extensions.h"
#include "xrMemory.h"
#include "xrCommon/xalloc.h"
#include "xrCommon/xr_vector.h"
#include "xrCommon/xr_map.h"
#include "xrCommon/xr_set.h"
#include "xrCommon/xr_stack.h"
#include "xrCommon/xr_list.h"
#include "xrCommon/xr_deque.h"
#include "xrstring.h"
#include "xrCommon/inlining_macros.h"
#include "xrCommon/xr_string.h"
#include "xrDebug_macros.h" // only for pragma todo. Remove once handled.

#pragma todo("tamlin: This header includes pretty much every std collection there are. Compiler-hog! FIX!")

using std::swap;

#if defined(__BORLANDC__) || defined(LINUX)
#ifndef M_NOSTDCONTAINERS_EXT
#define M_NOSTDCONTAINERS_EXT
#endif // M_NOSTDCONTAINERS_EXT
#endif // __BORLANDC__

#ifdef M_NOSTDCONTAINERS_EXT
#define xr_list std::list
#define xr_deque std::deque
#define xr_stack std::stack
#define xr_set std::set
#define xr_multiset std::multiset
#define xr_map std::map
#ifdef WINDOWS
#define xr_hash_map std::hash_map
#else // POSIX
#include <unordered_map>
#define xr_hash_map std::unordered_map
#endif // WINDOWS
#define xr_multimap std::multimap
#define xr_string std::string

template <class T>
class xr_vector : public std::vector < T >
{
public:
	typedef size_t size_type;
	typedef T& reference;
	typedef const T& const_reference;
public:
	xr_vector() : std::vector<T>() {}
	xr_vector(size_t _count, const T& _value) : std::vector<T>(_count, _value) {}
	explicit xr_vector(size_t _count) : std::vector<T>(_count) {}
	void clear() { std::vector<T>::erase(std::vector<T>::begin(), std::vector<T>::end()); }
	void clear_and_free() { std::vector<T>::clear(); }
	void clear_not_free() { std::vector<T>::erase(std::vector<T>::begin(), std::vector<T>::end()); }

	void clear_and_reserve()
	{
	  if (std::vector<T>::capacity() <= (std::vector<T>::size() + std::vector<T>::size() / 4))
	  	clear_not_free();
	  else
	  {
	    u32 old = std::vector<T>::size();
	    clear_and_free();
	    std::vector<T>::reserve(old);
	  }
	}
	ICF const_reference operator[] (size_type _Pos) const { {VERIFY(_Pos < std::vector<T>::size()); } return (*(std::vector<T>::begin() + _Pos)); }
	ICF reference operator[] (size_type _Pos) { {VERIFY(_Pos < std::vector<T>::size()); } return (*(std::vector<T>::begin() + _Pos)); }
};

template <>
class xr_vector<bool> : public std::vector < bool >
{
	typedef bool T;
public:
	xr_vector<T>() : std::vector<T>() {}
	xr_vector<T>(size_t _count, const T& _value) : std::vector<T>(_count, _value) {}
	explicit xr_vector<T>(size_t _count) : std::vector<T>(_count) {}
	u32 size() const { return (u32)std::vector<T>::size(); }
	void clear() { erase(begin(), end()); }
};

#else // !M_NOSTDCONTAINERS_EXT

#ifdef STLPORT
namespace std
{
	template<class _Tp1, class _Tp2> inline xalloc<_Tp2>& __stl_alloc_rebind(xalloc<_Tp1>& __a, const _Tp2*) { return (xalloc<_Tp2>&)(__a); }
	template<class _Tp1, class _Tp2> inline xalloc<_Tp2> __stl_alloc_create(xalloc<_Tp1>&, const _Tp2*) { return xalloc<_Tp2>(); }
}

template <typename V, class _HashFcn = std::hash<V>, class _EqualKey = std::equal_to<V>, typename allocator = xalloc<V> > class xr_hash_set : public std::hash_set < V, _HashFcn, _EqualKey, allocator > { public: u32 size() const { return (u32)__super::size(); } };
template <typename V, class _HashFcn = std::hash<V>, class _EqualKey = std::equal_to<V>, typename allocator = xalloc<V> > class xr_hash_multiset : public std::hash_multiset < V, _HashFcn, _EqualKey, allocator > { public: u32 size() const { return (u32)__super::size(); } };

template <typename K, class V, class _HashFcn = std::hash<K>, class _EqualKey = std::equal_to<K>, typename allocator = xalloc<std::pair<K, V> > > class xr_hash_map : public std::hash_map < K, V, _HashFcn, _EqualKey, allocator > { public: u32 size() const { return (u32)__super::size(); } };
template <typename K, class V, class _HashFcn = std::hash<K>, class _EqualKey = std::equal_to<K>, typename allocator = xalloc<std::pair<K, V> > > class xr_hash_multimap : public std::hash_multimap < K, V, _HashFcn, _EqualKey, allocator > { public: u32 size() const { return (u32)__super::size(); } };
#else
#include "xrCommon/xr_hash_map.h"
#endif // STLPORT
#endif // M_NOSTDCONTAINERS_EXT


//#pragma todo("tamlin: Why define our own std::make_pair? What's wrong with std::make_pair")
//template <class _Ty1, class _Ty2> inline std::pair<_Ty1, _Ty2> std::make_pair(_Ty1 _Val1, _Ty2 _Val2) { return (std::pair<_Ty1, _Ty2>(_Val1, _Val2)); }

#include "xrCommon/predicates.h"

// tamlin: TODO (low priority, for a rainy day): Rename these macros from DEFINE_* to DECLARE_*

// STL extensions
#define DEFINE_SVECTOR(T,C,N,I) typedef svector< T, C > N; typedef N::iterator I;

#include "FixedVector.h"
#include "buffer_vector.h"
#include "xr_vector_defs.h"

#endif // include guard
