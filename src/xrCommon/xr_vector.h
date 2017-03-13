#pragma once
#include <vector>
#include "xalloc.h"
#include "xrCore/xrDebug_macros.h"

#ifdef XR_X64
#define M_DONTDEFERCLEAR_EXT
#endif

#define M_DONTDEFERCLEAR_EXT //. for mem-debug only


#define DEF_VECTOR(N,T) typedef xr_vector< T > N; typedef N::iterator N##_it;
#define DEFINE_VECTOR(T,N,I) typedef xr_vector< T > N; typedef N::iterator I;


// vector
template <typename T, typename allocator = xalloc<T> >
class xr_vector : public std::vector < T, allocator >
{
private:
	typedef std::vector<T, allocator> inherited;

public:
	typedef allocator allocator_type;
	typedef size_t size_type;

public:
	xr_vector() : inherited() {}
	xr_vector(size_t _count, const T& _value) : inherited(_count, _value) {}
	explicit xr_vector(size_t _count) : inherited(_count) {}
	u32 size() const noexcept { return (u32)inherited::size(); }

	void clear_and_free() noexcept { inherited::clear(); }
	void clear_not_free() { inherited::erase(inherited::begin(), inherited::end()); }
	void clear_and_reserve() { if (inherited::capacity() <= (size() + size() / 4)) clear_not_free(); else { u32 old = size(); clear_and_free(); inherited::reserve(old); } }

#ifdef M_DONTDEFERCLEAR_EXT // defined (or not) by xalloc.h
	void clear() { clear_and_free(); }
#else
	void clear() { clear_not_free(); }
#endif

	typename inherited::const_reference operator[] (size_type _Pos) const { check_idx(_Pos); return (*(inherited::begin() + _Pos)); }
	typename inherited::reference operator[] (size_type _Pos) { check_idx(_Pos); return (*(inherited::begin() + _Pos)); }

private:
	void check_idx(size_type _Pos) const
	{
		VERIFY2(_Pos < size(), make_string("index is out of range: index requested[%d], size of container[%d]", _Pos, size()).c_str());
	}
};

// vector<bool>
template <>
class xr_vector<bool, xalloc<bool> > : public std::vector < bool, xalloc<bool> >
{
private:
	typedef std::vector<bool, xalloc<bool> > inherited;

public:
	u32 size() const { return (u32)inherited::size(); }
	void clear() { erase(begin(), end()); }
};

template <typename allocator>
class xr_vector<bool, allocator> : public std::vector < bool, allocator >
{
private:
	typedef std::vector<bool, allocator> inherited;

public:
	u32 size() const { return (u32)inherited::size(); }
	void clear() { erase(inherited::begin(), inherited::end()); }
};
