/* quickmath.h
 * author: Daniel Elwell (2022)
 * license: MIT
 * description: a single-header library for common vector, matrix, and quaternion math
 * functions designed for games and graphics programming.
 * 
 * ------------------------------------------------------------------------
 * 
 * to disable the need to link with the C runtime library, you must:
 * "#define QM_SQRTF yourSqrtf"
 * "#define QM_SINF yourSinf"
 * "#define QM_COSF yourCosf"
 * in one source file before this file is "#include"d
 * 
 * to change the function prefixes (default is "QM_"), you must either:
 * "#define QM_PREFIX"                        //for no prefix
 * "#define QM_PREFIX(name) yourPrefix##name" //for a custom prefix
 * in one source file before this file is "#include"d
 * 
 * ------------------------------------------------------------------------
 * the following functions are defined:
 * (QMvecn means a vector of dimension, 2, 3, or 4, named QMvec2, QMvec3, and QMvec4)
 * 
 * QMvecn QM_vecn_add       (QMvecn v1, QMvecn v2); //adds two vectors
 * QMvecn QM_vecn_sub       (QMvecn v1, QMvecn v2); //subtracts two vectors
 * QMvecn QM_vecn_mult      (QMvecn v1, QMvecn v2); //multiplies two vectors
 * QMvecn QM_vecn_div       (QMvecn v1, QMvecn v2); //divides two vectors
 * QMvecn QM_vecn_scale     (QMvecn v , float  s ); //multiplies each of a vector's components
 * QMvecn QM_vecn_dot       (QMvecn v1, QMvecn v2); //computes the dot product of two vectors
 * QMvec3 QM_vec3_cross     (QMvec3 v1, QMvec3 v2); //computes the cross product of two 3D vectors
 * float  QM_vecn_length    (QMvecn v);             //computes the length of a vector
 * QMvecn QM_vecn_normalize (QMvecn v);             //normalizes a vector
 * float  QM_vecn_distance  (QMvecn v1, QMvecn v2); //computes the distance between two vectors
 * int    QM_vecn_equals    (QMvecn v1, QMvecn v2); //checks two vectors for equality
 * QMvecn QM_vecn_min       (QMvecn v1, QMvecn v2); //takes the component-wise minimum of two vectors
 * QMvecn QM_vecn_max       (QMvecn v1, QMvecn v2); //takes the component-wise maximum of two vectors
 */

#ifndef QM_MATH_H
#define QM_MATH_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <xmmintrin.h>
#include <pmmintrin.h>
#define QM_INLINE static inline

//if you wish to set your own function prefix or remove it entirely,
//simple "#define QM_PREFIX(name) [yourPrefix]##name" in one source file 
//before including this file
#ifndef QM_PREFIX
	#define QM_PREFIX(name) QM_##name
#endif

//if you wish to not use any of the CRT functions, you must #define your
//own versions of the below functions in one source file before 
//including this file
#if !defined(QM_SQRTF) || !defined(QM_SINF) || !defined(QM_COSF)
	#include <math.h>
#endif

#ifndef QM_SQRTF
	#define QM_SQRTF sqrtf
#endif

#ifndef QM_SINF
	#define QM_SINF sinf
#endif

#ifndef QM_COSF
	#define QM_COSF cosf
#endif

//----------------------------------------------------------------------//
//STRUCT DEFINITIONS:

typedef int QMbool;

//a 2-dimensional vector of floats
typedef union
{
	float v[2];
	struct{ float x, y; };
	struct{ float w, h; };
} QMvec2;

//a 3-dimensional vector of floats
typedef union
{
	float v[3];
	struct{ float x, y, z; };
	struct{ float w, h, d; };
	struct{ float r, g, b; };
} QMvec3;

//a 4-dimensional vector of floats
typedef union
{
	float v[4];
	struct{ float x, y, z, w; };
	struct{ float r, g, b, a; };
	__m128 packed;
} QMvec4;

//-----------------------------//
//matrices are column-major

typedef struct
{
	float m[3][3];
} QMmat3;

typedef struct
{
	float m[4][4];
	__m128 packed[4]; //array of columns
} QMmat4;

//-----------------------------//

typedef union
{
	float q[4];
	struct{ float x, y, z, w; };
	__m128 packed;
} QMquaternion;

//----------------------------------------------------------------------//
//HELPER FUNCS:

#define QM_MIN(x, y) ((x) < (y) ? (x) : (y))
#define QM_MAX(x, y) ((x) > (y) ? (x) : (y))

//----------------------------------------------------------------------//
//VECTOR FUNCTIONS:

//addition:

QM_INLINE QMvec2 QM_PREFIX(vec2_add)(QMvec2 v1, QMvec2 v2)
{
	QMvec2 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;

	return result;
}

QM_INLINE QMvec3 QM_PREFIX(vec3_add)(QMvec3 v1, QMvec3 v2)
{
	QMvec3 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;
}

QM_INLINE QMvec4 QM_PREFIX(vec4_add)(QMvec4 v1, QMvec4 v2)
{
	QMvec4 result;

	result.packed = _mm_add_ps(v1.packed, v2.packed);

	return result;
}

//subtraction:

QM_INLINE QMvec2 QM_PREFIX(vec2_sub)(QMvec2 v1, QMvec2 v2)
{
	QMvec2 result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;

	return result;
}

QM_INLINE QMvec3 QM_PREFIX(vec3_sub)(QMvec3 v1, QMvec3 v2)
{
	QMvec3 result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;

	return result;
}

QM_INLINE QMvec4 QM_PREFIX(vec4_sub)(QMvec4 v1, QMvec4 v2)
{
	QMvec4 result;

	result.packed = _mm_sub_ps(v1.packed, v2.packed);

	return result;
}

//multiplication:

QM_INLINE QMvec2 QM_PREFIX(vec2_mult)(QMvec2 v1, QMvec2 v2)
{
	QMvec2 result;

	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;

	return result;
}

QM_INLINE QMvec3 QM_PREFIX(vec3_mult)(QMvec3 v1, QMvec3 v2)
{
	QMvec3 result;

	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;

	return result;
}

QM_INLINE QMvec4 QM_PREFIX(vec4_mult)(QMvec4 v1, QMvec4 v2)
{
	QMvec4 result;

	result.packed = _mm_mul_ps(v1.packed, v2.packed);

	return result;
}

//division:

QM_INLINE QMvec2 QM_PREFIX(vec2_div)(QMvec2 v1, QMvec2 v2)
{
	QMvec2 result;

	result.x = v1.x / v2.x;
	result.y = v1.y / v2.y;

	return result;
}

QM_INLINE QMvec3 QM_PREFIX(vec3_div)(QMvec3 v1, QMvec3 v2)
{
	QMvec3 result;

	result.x = v1.x / v2.x;
	result.y = v1.y / v2.y;
	result.z = v1.z / v2.z;

	return result;
}

QM_INLINE QMvec4 QM_PREFIX(vec4_div)(QMvec4 v1, QMvec4 v2)
{
	QMvec4 result;

	result.packed = _mm_div_ps(v1.packed, v2.packed);

	return result;
}

//scalar multiplication:

QM_INLINE QMvec2 QM_PREFIX(vec2_scale)(QMvec2 v, float s)
{
	QMvec2 result;

	result.x = v.x * s;
	result.y = v.y * s;

	return result;
}

QM_INLINE QMvec3 QM_PREFIX(vec3_scale)(QMvec3 v, float s)
{
	QMvec3 result;

	result.x = v.x * s;
	result.y = v.y * s;
	result.z = v.z * s;

	return result;
}

QM_INLINE QMvec4 QM_PREFIX(vec4_scale)(QMvec4 v, float s)
{
	QMvec4 result;

	__m128 scale = _mm_set1_ps(s);
	result.packed = _mm_mul_ps(v.packed, scale);

	return result;
}

//dot product:

QM_INLINE float QM_PREFIX(vec2_dot)(QMvec2 v1, QMvec2 v2)
{
	float result;

	result = v1.x * v2.x + v1.y * v2.y;

	return result;
}

QM_INLINE float QM_PREFIX(vec3_dot)(QMvec3 v1, QMvec3 v2)
{
	float result;

	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

	return result;
}

QM_INLINE float QM_PREFIX(vec4_dot)(QMvec4 v1, QMvec4 v2)
{
	float result;

	__m128 r = _mm_mul_ps(v1.packed, v2.packed);
	r = _mm_hadd_ps(r, r);
	r = _mm_hadd_ps(r, r);
	_mm_store_ss(&result, r);

	return result;
}

//cross product

QM_INLINE QMvec3 QM_PREFIX(vec3_cross)(QMvec3 v1, QMvec3 v2)
{
	QMvec3 result;

	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);

	return result;
}

//length:

QM_INLINE float QM_PREFIX(vec2_length)(QMvec2 v)
{
	float result;

	result = QM_SQRTF(QM_PREFIX(vec2_dot)(v, v));

	return result;
}

QM_INLINE float QM_PREFIX(vec3_length)(QMvec3 v)
{
	float result;

	result = QM_SQRTF(QM_PREFIX(vec3_dot)(v, v));

	return result;
}

QM_INLINE float QM_PREFIX(vec4_length)(QMvec4 v)
{
	float result;

	result = QM_SQRTF(QM_PREFIX(vec4_dot)(v, v));

	return result;
}

//normalize:

QM_INLINE QMvec2 QM_PREFIX(vec2_normalize)(QMvec2 v)
{
	QMvec2 result = {};

	float invLen = QM_PREFIX(vec2_length)(v);
	if(invLen != 0.0f)
	{
		invLen = 1.0f / invLen;
		result.x = v.x * invLen;
		result.y = v.y * invLen;
	}

	return result;
}

QM_INLINE QMvec3 QM_PREFIX(vec3_normalize)(QMvec3 v)
{
	QMvec3 result = {};

	float invLen = QM_PREFIX(vec3_length)(v);
	if(invLen != 0.0f)
	{
		invLen = 1.0f / invLen;
		result.x = v.x * invLen;
		result.y = v.y * invLen;
		result.z = v.z * invLen;
	}

	return result;
}

QM_INLINE QMvec4 QM_PREFIX(vec4_normalize)(QMvec4 v)
{
	QMvec4 result = {};

	float invLen = QM_PREFIX(vec4_length)(v);
	if(invLen != 0.0f)
	{
		invLen = 1.0f / invLen;

		__m128 scale = _mm_set1_ps(invLen);
		result.packed = _mm_mul_ps(v.packed, scale);
	}

	return result;
}

//distance:

QM_INLINE float QM_PREFIX(vec2_distance)(QMvec2 v1, QMvec2 v2)
{
	float result;

	QMvec2 to = QM_PREFIX(vec2_sub)(v1, v2);
	result = QM_PREFIX(vec2_length)(to);

	return result;
}

QM_INLINE float QM_PREFIX(vec3_distance)(QMvec3 v1, QMvec3 v2)
{
	float result;

	QMvec3 to = QM_PREFIX(vec3_sub)(v1, v2);
	result = QM_PREFIX(vec3_length)(to);

	return result;
}

QM_INLINE float QM_PREFIX(vec4_distance)(QMvec4 v1, QMvec4 v2)
{
	float result;

	QMvec4 to = QM_PREFIX(vec4_sub)(v1, v2);
	result = QM_PREFIX(vec4_length)(to);

	return result;
}

//equality:

QM_INLINE QMbool QM_PREFIX(vec2_equals)(QMvec2 v1, QMvec2 v2)
{
	QMbool result;

	result = (v1.x == v2.x) && (v1.y == v2.y); 

	return result;	
}

QM_INLINE QMbool QM_PREFIX(vec3_equals)(QMvec3 v1, QMvec3 v2)
{
	QMbool result;

	result = (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z); 

	return result;	
}

QM_INLINE QMbool QM_PREFIX(vec4_equals)(QMvec4 v1, QMvec4 v2)
{
	QMbool result;

	//TODO: there are SIMD instructions for floating point equality, find a way to get a single bool from them
	result = (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z) && (v1.w == v2.w); 

	return result;	
}

//min:

QM_INLINE QMvec2 QM_PREFIX(vec2_min)(QMvec2 v1, QMvec2 v2)
{
	QMvec2 result;

	result.x = QM_MIN(v1.x, v2.x);
	result.y = QM_MIN(v1.y, v2.y);

	return result;
}

QM_INLINE QMvec3 QM_PREFIX(vec3_min)(QMvec3 v1, QMvec3 v2)
{
	QMvec3 result;

	result.x = QM_MIN(v1.x, v2.x);
	result.y = QM_MIN(v1.y, v2.y);
	result.z = QM_MIN(v1.z, v2.z);

	return result;
}

QM_INLINE QMvec4 QM_PREFIX(vec4_min)(QMvec4 v1, QMvec4 v2)
{
	QMvec4 result;

	result.packed = _mm_min_ps(v1.packed, v2.packed);

	return result;
}

//max:

QM_INLINE QMvec2 QM_PREFIX(vec2_max)(QMvec2 v1, QMvec2 v2)
{
	QMvec2 result;

	result.x = QM_MAX(v1.x, v2.x);
	result.y = QM_MAX(v1.y, v2.y);

	return result;
}

QM_INLINE QMvec3 QM_PREFIX(vec3_max)(QMvec3 v1, QMvec3 v2)
{
	QMvec3 result;

	result.x = QM_MAX(v1.x, v2.x);
	result.y = QM_MAX(v1.y, v2.y);
	result.z = QM_MAX(v1.z, v2.z);

	return result;
}

QM_INLINE QMvec4 QM_PREFIX(vec4_max)(QMvec4 v1, QMvec4 v2)
{
	QMvec4 result;

	result.packed = _mm_max_ps(v1.packed, v2.packed);

	return result;
}

#ifdef __cplusplus
} //extern "C"
#endif

#endif //QM_MATH_H