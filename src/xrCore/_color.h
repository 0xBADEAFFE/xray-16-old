#pragma once
#ifndef XRCORE_COLOR_H
#define XRCORE_COLOR_H
#include "_types.h"
#include "xrCommon/inlining_macros.h"
#include "xrCore/math_constants.h"

// maps unsigned 8 bits/channel to D3DCOLOR
ICF u32 color_argb(u32 a, u32 r, u32 g, u32 b) noexcept { return ((a & 0xff) << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff); }
ICF u32 color_rgba(u32 r, u32 g, u32 b, u32 a) noexcept { return color_argb(a, r, g, b); }
u32 color_argb_f(f32 a, f32 r, f32 g, f32 b) noexcept;
ICF u32 color_rgba_f(f32 r, f32 g, f32 b, f32 a) noexcept { return color_argb_f(a, r, g, b); }
ICF u32 color_xrgb(u32 r, u32 g, u32 b) { return color_argb(0xff, r, g, b); }
ICF u32 color_get_R(u32 rgba) noexcept { return ((rgba >> 16) & 0xff); }
ICF u32 color_get_G(u32 rgba) noexcept { return ((rgba >> 8) & 0xff); }
ICF u32 color_get_B(u32 rgba) noexcept { return (rgba & 0xff); }
ICF u32 color_get_A(u32 rgba) noexcept { return (rgba >> 24); }
ICF u32 subst_alpha(u32 rgba, u32 a) { return (rgba & ~color_rgba(0, 0, 0, 0xff)) | color_rgba(0, 0, 0, a); }
ICF u32 bgr2rgb(u32 bgr) { return color_rgba(color_get_B(bgr), color_get_G(bgr), color_get_R(bgr), 0); }
ICF u32 rgb2bgr(u32 rgb) { return bgr2rgb(rgb); }

struct Fcolor
{
    float r, g, b, a;

    Fcolor& set(u32 dw) noexcept;
    Fcolor& set(float _r, float _g, float _b, float _a)
    {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
        return *this;
    };
	Fcolor& set(const Fcolor& rhs) noexcept;
    u32 get() const noexcept;
    u32 get_windows() const noexcept; // Get color as a Windows DWORD value.
	Fcolor& set_windows(u32 dw) noexcept; // Set color from a Windows DWORD color value.
	Fcolor& adjust_contrast(float f) noexcept; // >1 - contrast will be increased
	Fcolor& adjust_contrast(const Fcolor& in, float f) noexcept; // >1 - contrast will be increased
    Fcolor& adjust_saturation(float s) noexcept;
    Fcolor& adjust_saturation(const Fcolor& in, float s) noexcept;
    Fcolor& modulate(Fcolor& in) noexcept;
	Fcolor& modulate(const Fcolor& in1, const Fcolor& in2) noexcept;
    Fcolor& negative(const Fcolor& in) noexcept;
    Fcolor& negative() noexcept;
	Fcolor& sub_rgb(float s) noexcept;
	Fcolor& add_rgb(float s) noexcept;
    Fcolor& add_rgba(float s) noexcept;
    Fcolor& mul_rgba(float s) noexcept;
    Fcolor& mul_rgb(float s) noexcept;
    Fcolor& mul_rgba(const Fcolor& c, float s) noexcept;
    Fcolor& mul_rgb(const Fcolor& c, float s) noexcept;

    // SQ magnitude
    float magnitude_sqr_rgb() const noexcept;
    // magnitude
    float magnitude_rgb() const noexcept;
    float intensity() const noexcept;

    // Normalize
	Fcolor& normalize_rgb();
	Fcolor& normalize_rgb(const Fcolor& c);
	Fcolor& lerp(const Fcolor& c1, const Fcolor& c2, float t) noexcept;
	Fcolor& lerp(const Fcolor& c1, const Fcolor& c2, const Fcolor& c3, float t) noexcept;
	bool similar_rgba(const Fcolor& v, float E = EPS_L) const noexcept;
	bool similar_rgb(const Fcolor& v, float E = EPS_L) const noexcept;
};

bool _valid(const Fcolor& c) noexcept;

#endif // XRCORE_COLOR_H
