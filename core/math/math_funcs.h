/*************************************************************************/
/*  math_funcs.h                                                         */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2018 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2018 Godot Engine contributors (cf. AUTHORS.md)    */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef MATH_FUNCS_H
#define MATH_FUNCS_H

#include "core/math/math_defs.h"
#include "core/typedefs.h"

#include "thirdparty/misc/pcg.h"

#include <float.h>
#include <math.h>

class Math {

	static pcg32_random_t default_pcg;

public:
	Math() {} // useless to instance

	static const uint64_t RANDOM_MAX = 0xFFFFFFFF;

	static _ALWAYS_INLINE_ double sin(double p_x) { return ::sin(p_x); }
	static _ALWAYS_INLINE_ float sin(float p_x) { return ::sinf(p_x); }

	static _ALWAYS_INLINE_ double cos(double p_x) { return ::cos(p_x); }
	static _ALWAYS_INLINE_ float cos(float p_x) { return ::cosf(p_x); }

	static _ALWAYS_INLINE_ double tan(double p_x) { return ::tan(p_x); }
	static _ALWAYS_INLINE_ float tan(float p_x) { return ::tanf(p_x); }

	static _ALWAYS_INLINE_ double sinh(double p_x) { return ::sinh(p_x); }
	static _ALWAYS_INLINE_ float sinh(float p_x) { return ::sinhf(p_x); }

	static _ALWAYS_INLINE_ double cosh(double p_x) { return ::cosh(p_x); }
	static _ALWAYS_INLINE_ float cosh(float p_x) { return ::coshf(p_x); }

	static _ALWAYS_INLINE_ double tanh(double p_x) { return ::tanh(p_x); }
	static _ALWAYS_INLINE_ float tanh(float p_x) { return ::tanhf(p_x); }

	static _ALWAYS_INLINE_ double asin(double p_x) { return ::asin(p_x); }
	static _ALWAYS_INLINE_ float asin(float p_x) { return ::asinf(p_x); }

	static _ALWAYS_INLINE_ double acos(double p_x) { return ::acos(p_x); }
	static _ALWAYS_INLINE_ float acos(float p_x) { return ::acosf(p_x); }

	static _ALWAYS_INLINE_ double atan(double p_x) { return ::atan(p_x); }
	static _ALWAYS_INLINE_ float atan(float p_x) { return ::atanf(p_x); }

	static _ALWAYS_INLINE_ double atan2(double p_y, double p_x) { return ::atan2(p_y, p_x); }
	static _ALWAYS_INLINE_ float atan2(float p_y, float p_x) { return ::atan2f(p_y, p_x); }

	static _ALWAYS_INLINE_ double sqrt(double p_x) { return ::sqrt(p_x); }
	static _ALWAYS_INLINE_ float sqrt(float p_x) { return ::sqrtf(p_x); }

	static _ALWAYS_INLINE_ double fmod(double p_x, double p_y) { return ::fmod(p_x, p_y); }
	static _ALWAYS_INLINE_ float fmod(float p_x, float p_y) { return ::fmodf(p_x, p_y); }

	static _ALWAYS_INLINE_ double floor(double p_x) { return ::floor(p_x); }
	static _ALWAYS_INLINE_ float floor(float p_x) { return ::floorf(p_x); }

	static _ALWAYS_INLINE_ double ceil(double p_x) { return ::ceil(p_x); }
	static _ALWAYS_INLINE_ float ceil(float p_x) { return ::ceilf(p_x); }

	static _ALWAYS_INLINE_ double pow(double p_x, double p_y) { return ::pow(p_x, p_y); }
	static _ALWAYS_INLINE_ float pow(float p_x, float p_y) { return ::powf(p_x, p_y); }

	static _ALWAYS_INLINE_ double log(double p_x) { return ::log(p_x); }
	static _ALWAYS_INLINE_ float log(float p_x) { return ::logf(p_x); }

	static _ALWAYS_INLINE_ double exp(double p_x) { return ::exp(p_x); }
	static _ALWAYS_INLINE_ float exp(float p_x) { return ::expf(p_x); }

	static _ALWAYS_INLINE_ bool is_nan(double p_val) {
#ifdef _MSC_VER
		return _isnan(p_val);
#elif defined(__GNUC__) && __GNUC__ < 6
		union {
			uint64_t u;
			double f;
		} ieee754;
		ieee754.f = p_val;
		// (unsigned)(0x7ff0000000000001 >> 32) : 0x7ff00000
		return ((((unsigned)(ieee754.u >> 32) & 0x7fffffff) + ((unsigned)ieee754.u != 0)) > 0x7ff00000);
#else
		return isnan(p_val);
#endif
	}

	static _ALWAYS_INLINE_ bool is_nan(float p_val) {
#ifdef _MSC_VER
		return _isnan(p_val);
#elif defined(__GNUC__) && __GNUC__ < 6
		union {
			uint32_t u;
			float f;
		} ieee754;
		ieee754.f = p_val;
		// -----------------------------------
		// (single-precision floating-point)
		// NaN : s111 1111 1xxx xxxx xxxx xxxx xxxx xxxx
		//     : (> 0x7f800000)
		// where,
		//   s : sign
		//   x : non-zero number
		// -----------------------------------
		return ((ieee754.u & 0x7fffffff) > 0x7f800000);
#else
		return isnan(p_val);
#endif
	}

	static _ALWAYS_INLINE_ bool is_inf(double p_val) {
#ifdef _MSC_VER
		return !_finite(p_val);
// use an inline implementation of isinf as a workaround for problematic libstdc++ versions from gcc 5.x era
#elif defined(__GNUC__) && __GNUC__ < 6
		union {
			uint64_t u;
			double f;
		} ieee754;
		ieee754.f = p_val;
		return ((unsigned)(ieee754.u >> 32) & 0x7fffffff) == 0x7ff00000 &&
			   ((unsigned)ieee754.u == 0);
#else
		return isinf(p_val);
#endif
	}

	static _ALWAYS_INLINE_ bool is_inf(float p_val) {
#ifdef _MSC_VER
		return !_finite(p_val);
// use an inline implementation of isinf as a workaround for problematic libstdc++ versions from gcc 5.x era
#elif defined(__GNUC__) && __GNUC__ < 6
		union {
			uint32_t u;
			float f;
		} ieee754;
		ieee754.f = p_val;
		return (ieee754.u & 0x7fffffff) == 0x7f800000;
#else
		return isinf(p_val);
#endif
	}

	static _ALWAYS_INLINE_ double abs(double g) { return absd(g); }
	static _ALWAYS_INLINE_ float abs(float g) { return absf(g); }
	static _ALWAYS_INLINE_ int abs(int g) { return g > 0 ? g : -g; }

	static _ALWAYS_INLINE_ double fposmod(double p_x, double p_y) {
		double value = Math::fmod(p_x, p_y);
		if ((value < 0 && p_y > 0) || (value > 0 && p_y < 0)) {
			value += p_y;
		}
		value += 0.0;
		return value;
	}
	static _ALWAYS_INLINE_ float fposmod(float p_x, float p_y) {
		float value = Math::fmod(p_x, p_y);
		if ((value < 0 && p_y > 0) || (value > 0 && p_y < 0)) {
			value += p_y;
		}
		value += 0.0;
		return value;
	}

	static _ALWAYS_INLINE_ double deg2rad(double p_y) { return p_y * Math_PI / 180.0; }
	static _ALWAYS_INLINE_ float deg2rad(float p_y) { return p_y * Math_PI / 180.0; }

	static _ALWAYS_INLINE_ double rad2deg(double p_y) { return p_y * 180.0 / Math_PI; }
	static _ALWAYS_INLINE_ float rad2deg(float p_y) { return p_y * 180.0 / Math_PI; }

	static _ALWAYS_INLINE_ double lerp(double p_from, double p_to, double p_weight) { return p_from + (p_to - p_from) * p_weight; }
	static _ALWAYS_INLINE_ float lerp(float p_from, float p_to, float p_weight) { return p_from + (p_to - p_from) * p_weight; }

	static _ALWAYS_INLINE_ double inverse_lerp(double p_from, double p_to, double p_value) { return (p_value - p_from) / (p_to - p_from); }
	static _ALWAYS_INLINE_ float inverse_lerp(float p_from, float p_to, float p_value) { return (p_value - p_from) / (p_to - p_from); }

	static _ALWAYS_INLINE_ double range_lerp(double p_value, double p_istart, double p_istop, double p_ostart, double p_ostop) { return Math::lerp(p_ostart, p_ostop, Math::inverse_lerp(p_istart, p_istop, p_value)); }
	static _ALWAYS_INLINE_ float range_lerp(float p_value, float p_istart, float p_istop, float p_ostart, float p_ostop) { return Math::lerp(p_ostart, p_ostop, Math::inverse_lerp(p_istart, p_istop, p_value)); }

	static _ALWAYS_INLINE_ double linear2db(double p_linear) { return Math::log(p_linear) * 8.6858896380650365530225783783321; }
	static _ALWAYS_INLINE_ float linear2db(float p_linear) { return Math::log(p_linear) * 8.6858896380650365530225783783321; }

	static _ALWAYS_INLINE_ double db2linear(double p_db) { return Math::exp(p_db * 0.11512925464970228420089957273422); }
	static _ALWAYS_INLINE_ float db2linear(float p_db) { return Math::exp(p_db * 0.11512925464970228420089957273422); }

	static _ALWAYS_INLINE_ double round(double p_val) { return (p_val >= 0) ? Math::floor(p_val + 0.5) : -Math::floor(-p_val + 0.5); }
	static _ALWAYS_INLINE_ float round(float p_val) { return (p_val >= 0) ? Math::floor(p_val + 0.5) : -Math::floor(-p_val + 0.5); }

	static _ALWAYS_INLINE_ int wrapi(int value, int min, int max) {
		int rng = max - min;
		return min + ((((value - min) % rng) + rng) % rng);
	}
	static _ALWAYS_INLINE_ double wrapf(double value, double min, double max) {
		double rng = max - min;
		return value - (rng * Math::floor((value - min) / rng));
	}
	static _ALWAYS_INLINE_ float wrapf(float value, float min, float max) {
		float rng = max - min;
		return value - (rng * Math::floor((value - min) / rng));
	}

	// double only, as these functions are mainly used by the editor and not performance-critical,
	static double ease(double p_x, double p_c);
	static int step_decimals(double p_step);
	static double stepify(double p_value, double p_step);
	static double dectime(double p_value, double p_amount, double p_step);

	static uint32_t larger_prime(uint32_t p_val);

	static void seed(uint64_t x);
	static void randomize();
	static uint32_t rand_from_seed(uint64_t *seed);
	static uint32_t rand();
	static _ALWAYS_INLINE_ double randf() { return (double)rand() / (double)Math::RANDOM_MAX; }
	static _ALWAYS_INLINE_ float randd() { return (float)rand() / (float)Math::RANDOM_MAX; }

	static double random(double from, double to);
	static float random(float from, float to);
	static real_t random(int from, int to) { return (real_t)random((real_t)from, (real_t)to); }

	static _ALWAYS_INLINE_ bool is_equal_approx(real_t a, real_t b) {
		// TODO: Comparing floats for approximate-equality is non-trivial.
		// Using epsilon should cover the typical cases in Godot (where a == b is used to compare two reals), such as matrix and vector comparison operators.
		// A proper implementation in terms of ULPs should eventually replace the contents of this function.
		// See https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/ for details.

		return abs(a - b) < CMP_EPSILON;
	}

	static _ALWAYS_INLINE_ float absf(float g) {

		union {
			float f;
			uint32_t i;
		} u;

		u.f = g;
		u.i &= 2147483647u;
		return u.f;
	}

	static _ALWAYS_INLINE_ double absd(double g) {

		union {
			double d;
			uint64_t i;
		} u;
		u.d = g;
		u.i &= (uint64_t)9223372036854775807ll;
		return u.d;
	}

	//this function should be as fast as possible and rounding mode should not matter
	static _ALWAYS_INLINE_ int fast_ftoi(float a) {

		static int b;

#if (defined(_WIN32_WINNT) && _WIN32_WINNT >= 0x0603) || WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP // windows 8 phone?
		b = (int)((a > 0.0) ? (a + 0.5) : (a - 0.5));

#elif defined(_MSC_VER) && _MSC_VER < 1800
		__asm fld a __asm fistp b
		/*#elif defined( __GNUC__ ) && ( defined( __i386__ ) || defined( __x86_64__ ) )
		// use AT&T inline assembly style, document that
		// we use memory as output (=m) and input (m)
		__asm__ __volatile__ (
		"flds %1        \n\t"
		"fistpl %0      \n\t"
		: "=m" (b)
		: "m" (a));*/

#else
		b = lrintf(a); //assuming everything but msvc 2012 or earlier has lrint
#endif
		return b;
	}

#if defined(__GNUC__)

	static _ALWAYS_INLINE_ int64_t dtoll(double p_double) { return (int64_t)p_double; } ///@TODO OPTIMIZE
	static _ALWAYS_INLINE_ int64_t dtoll(float p_float) { return (int64_t)p_float; } ///@TODO OPTIMIZE and rename
#else

	static _ALWAYS_INLINE_ int64_t dtoll(double p_double) { return (int64_t)p_double; } ///@TODO OPTIMIZE
	static _ALWAYS_INLINE_ int64_t dtoll(float p_float) { return (int64_t)p_float; } ///@TODO OPTIMIZE and rename
#endif

	static _ALWAYS_INLINE_ uint32_t halfbits_to_floatbits(uint16_t h) {
		uint16_t h_exp, h_sig;
		uint32_t f_sgn, f_exp, f_sig;

		h_exp = (h & 0x7c00u);
		f_sgn = ((uint32_t)h & 0x8000u) << 16;
		switch (h_exp) {
			case 0x0000u: /* 0 or subnormal */
				h_sig = (h & 0x03ffu);
				/* Signed zero */
				if (h_sig == 0) {
					return f_sgn;
				}
				/* Subnormal */
				h_sig <<= 1;
				while ((h_sig & 0x0400u) == 0) {
					h_sig <<= 1;
					h_exp++;
				}
				f_exp = ((uint32_t)(127 - 15 - h_exp)) << 23;
				f_sig = ((uint32_t)(h_sig & 0x03ffu)) << 13;
				return f_sgn + f_exp + f_sig;
			case 0x7c00u: /* inf or NaN */
				/* All-ones exponent and a copy of the significand */
				return f_sgn + 0x7f800000u + (((uint32_t)(h & 0x03ffu)) << 13);
			default: /* normalized */
				/* Just need to adjust the exponent and shift */
				return f_sgn + (((uint32_t)(h & 0x7fffu) + 0x1c000u) << 13);
		}
	}

	static _ALWAYS_INLINE_ float halfptr_to_float(const uint16_t *h) {

		union {
			uint32_t u32;
			float f32;
		} u;

		u.u32 = halfbits_to_floatbits(*h);
		return u.f32;
	}

	static _ALWAYS_INLINE_ float half_to_float(const uint16_t h) {
		return halfptr_to_float(&h);
	}

	static _ALWAYS_INLINE_ uint16_t make_half_float(float f) {

		union {
			float fv;
			uint32_t ui;
		} ci;
		ci.fv = f;

		uint32_t x = ci.ui;
		uint32_t sign = (unsigned short)(x >> 31);
		uint32_t mantissa;
		uint32_t exp;
		uint16_t hf;

		// get mantissa
		mantissa = x & ((1 << 23) - 1);
		// get exponent bits
		exp = x & (0xFF << 23);
		if (exp >= 0x47800000) {
			// check if the original single precision float number is a NaN
			if (mantissa && (exp == (0xFF << 23))) {
				// we have a single precision NaN
				mantissa = (1 << 23) - 1;
			} else {
				// 16-bit half-float representation stores number as Inf
				mantissa = 0;
			}
			hf = (((uint16_t)sign) << 15) | (uint16_t)((0x1F << 10)) |
				 (uint16_t)(mantissa >> 13);
		}
		// check if exponent is <= -15
		else if (exp <= 0x38000000) {

			/*// store a denorm half-float value or zero
		exp = (0x38000000 - exp) >> 23;
		mantissa >>= (14 + exp);

		hf = (((uint16_t)sign) << 15) | (uint16_t)(mantissa);
		*/
			hf = 0; //denormals do not work for 3D, convert to zero
		} else {
			hf = (((uint16_t)sign) << 15) |
				 (uint16_t)((exp - 0x38000000) >> 13) |
				 (uint16_t)(mantissa >> 13);
		}

		return hf;
	}

	static _ALWAYS_INLINE_ float snap_scalar(float p_offset, float p_step, float p_target) {
		return p_step != 0 ? Math::stepify(p_target - p_offset, p_step) + p_offset : p_target;
	}

	static _ALWAYS_INLINE_ float snap_scalar_seperation(float p_offset, float p_step, float p_target, float p_separation) {
		if (p_step != 0) {
			float a = Math::stepify(p_target - p_offset, p_step + p_separation) + p_offset;
			float b = a;
			if (p_target >= 0)
				b -= p_separation;
			else
				b += p_step;
			return (Math::abs(p_target - a) < Math::abs(p_target - b)) ? a : b;
		}
		return p_target;
	}
};

#endif // MATH_FUNCS_H
