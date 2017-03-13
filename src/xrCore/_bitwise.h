#pragma once
#ifndef _BITWISE_
#define _BITWISE_
#include "math_constants.h"
#include "_types.h"

// integer math on floats

IC bool negative(const float f) { return f < 0; }
IC bool positive(const float f) { return f >= 0; }
IC void set_negative(float& f) { f = -fabsf(f); }
IC void set_positive(float& f) { f = fabsf(f); }

/*
 * Here are a few nice tricks for 2's complement based machines
 * that I discovered a few months ago.
 */
IC int btwLowestBitMask(int v) { return (v & -v); }
IC u32 btwLowestBitMask(u32 x) { return x & ~(x - 1); }

/* Ok, so now we are cooking on gass. Here we use this function for some */
/* rather useful utility functions */
IC bool btwIsPow2(int v) { return (btwLowestBitMask(v) == v); }
IC bool btwIsPow2(u32 v) { return (btwLowestBitMask(v) == v); }

IC int btwPow2_Ceil(int v)
{
    int i = btwLowestBitMask(v);
    while (i < v) i <<= 1;
    return i;
}
IC u32 btwPow2_Ceil(u32 v)
{
    u32 i = btwLowestBitMask(v);
    while (i < v) i <<= 1;
    return i;
}

// Couple more tricks
// Counting number of nonzero bits for 8bit number:
IC u8 btwCount1(u8 v)
{
    v = (v & 0x55) + ((v >> 1) & 0x55);
    v = (v & 0x33) + ((v >> 2) & 0x33);
    return (v & 0x0f) + ((v >> 4) & 0x0f);
}

//same for 32bit
IC u32 btwCount1(u32 v)
{
    const u32 g31 = 0x49249249ul; // = 0100_1001_0010_0100_1001_0010_0100_1001
    const u32 g32 = 0x381c0e07ul; // = 0011_1000_0001_1100_0000_1110_0000_0111
    v = (v & g31) + ((v >> 1) & g31) + ((v >> 2) & g31);
    v = ((v + (v >> 3)) & g32) + ((v >> 6) & g32);
    return (v + (v >> 9) + (v >> 18) + (v >> 27)) & 0x3f;
}

IC u64 btwCount1(u64 v)
{
    return btwCount1(u32(v&u32(-1))) + btwCount1(u32(v >> u64(32)));
}


// XXX: TODO: This function is WAY too large to inline, much less FORCE inline.
// Additionally, doesn't SSE2 have a fast ftol() ?
ICF int iFloor(float x)
{
    return floor(x);
}

/* intCeil() is a non-interesting variant, since effectively
 ceil(x) == -floor(-x)
 */
ICF int iCeil(float x)
{
    return ceil(x);
}

// Validity checks
IC bool fis_gremlin(const float& f)
{
    u8 value = u8(((*(int*)&f & 0x7f800000) >> 23) - 0x20);
    return value > 0xc0;
}
IC bool fis_denormal(const float& f)
{
    return !(*(int*)&f & 0x7f800000);
}

// Approximated calculations
IC float apx_InvSqrt(const float& n)
{
    return 1 / sqrt(n);
}

// Only for [0..1] (positive) range
IC float apx_asin(const float x)
{
    return asin(x);
}

// Only for [0..1] (positive) range
IC float apx_acos(const float x)
{
    return acos(x);
}

#endif
