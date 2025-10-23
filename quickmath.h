/* ------------------------------------------------------------------------
 *
 * quickmath.h
 * author: Daniel Elwell (2022)
 * license: MIT
 * description: a single-header library for common vector, matrix, and quaternion math
 * functions designed for games and graphics programming.
 * 
 * ------------------------------------------------------------------------
 * 
 * to change or disable the function prefix (the default is "qm_"), you must
 * "#define QM_FUNC_PREFIX(name) myprefix_##name" before including the library
 *
 * to define your own function attributes (like a __device__ decorator for CUDA), you
 * must "#define QM_FUNC_ATTRIBS my_attribs" before including the library. Note that you
 * almost always want to include "static" as an attrib
 * 
 * to disable the need to link with the C runtime library, you must
 * "#define QM_SQRTF(x) my_sqrtf(x)", "#define QM_SINF(x) my_sinf(x)", "#define QM_COSF(x) my_cosf(x)",
 * "#define QM_TANF(x) my_tanf(x)", and "#define QM_ACOSF(x) my_acosf(x)" before 
 * including the library
 * 
 * ------------------------------------------------------------------------
 * 
 * the following functions are defined:
 * (QMvecn means a vector of dimension, 2, 3, or 4, named QMvec2, QMvec3, and QMvec4)
 * (QMmatn means a matrix of dimensions 3x3 or 4x4, named QMmat3 and QMmat4)
 * (QMbboxn means a bounding box of dimensions 2 or 3)
 * 
 * QMvecn       qm_vecn_load                  (const float* in);
 * void         qm_vecn_store                 (QMvecn v, float* out);
 * QMvecn       qm_vecn_full                  (float val);
 * QMvecn       qm_vecn_add                   (QMvecn v1, QMvecn v2);
 * QMvecn       qm_vecn_sub                   (QMvecn v1, QMvecn v2);
 * QMvecn       qm_vecn_mult                  (QMvecn v1, QMvecn v2);
 * QMvecn       qm_vecn_div                   (QMvecn v1, QMvecn v2);
 * QMvecn       qm_vecn_scale                 (QMvecn v , float  s );
 * QMvecn       qm_vecn_dot                   (QMvecn v1, QMvecn v2);
 * QMvec3       qm_vec3_cross                 (QMvec3 v1, QMvec3 v2);
 * float        qm_vecn_length                (QMvecn v);
 * QMvecn       qm_vecn_normalize             (QMvecn v);
 * float        qm_vecn_distance              (QMvecn v1, QMvecn v2);
 * int          qm_vecn_equals                (QMvecn v1, QMvecn v2);
 * QMvecn       qm_vecn_min                   (QMvecn v1, QMvecn v2);
 * QMvecn       qm_vecn_max                   (QMvecn v1, QMvecn v2);
 * 
 * QMmatn       qm_matn_load                  (const float* in);
 * QMmatn       qm_matn_load_row_major        (const float* in);
 * void         qm_matn_store                 (QMmatn m, float* out);
 * void         qm_matn_store_row_major       (QMmatn m, float* out);
 * QMmatn       qm_matn_identity              ();
 * QMmatn       qm_matn_add                   (QMmatn m1, QMmatn m2);
 * QMmatn       qm_matn_sub                   (QMmatn m1, QMmatn m2);
 * QMmatn       qm_matn_mult                  (QMmatn m1, QMmatn m2);
 * QMvecn       qm_matn_mult_vecn             (QMmatn m , QMvecn v );
 * QMvec3       qm_mat4_transform_vec3        (QMmat4 m , QMvec3 v );
 * QMmatn       qm_matn_transpose             (QMmatn m);
 * QMmatn       qm_matn_inv                   (QMmatn m);
 * 
 * QMmat3       qm_mat3_translate             (QMvec2 t);
 * QMmat4       qm_mat4_translate             (QMvec3 t);
 * QMmat3       qm_mat3_scale                 (QMvec2 s);
 * QMmat4       qm_mat4_scale                 (QMvec3 s);
 * QMmat3       qm_mat3_rotate                (float angle);
 * QMmat4       qm_mat4_rotate                (QMvec3 axis, float angle);
 * QMmat4       qm_mat4_rotate_euler          (QMvec3 angles);
 * QMmat3       qm_mat4_top_left              (QMmat4 m);
 *
 * QMmat4       qm_mat4_prespective           (float fov, float aspect, float near, float far);
 * QMmat4       qm_mat4_orthographic          (float left, float right, float bot, float top, float near, float far);
 * QMmat4       qm_mat4_look                  (QMvec3 pos, QMvec3 dir   , QMvec3 up);
 * QMmat4       qm_mat4_lookat                (QMvec3 pos, QMvec3 target, QMvec3 up);
 * 
 * QMquaternion qm_quaternion_load            (const float* in);
 * void         qm_quaternion_store           (QMquaternion q, float* out);
 * QMquaternion qm_quaternion_identity        ();
 * QMquaternion qm_quaternion_add             (QMquaternion q1, QMquaternion q2);
 * QMquaternion qm_quaternion_sub             (QMquaternion q1, QMquaternion q2);
 * QMquaternion qm_quaternion_mult            (QMquaternion q1, QMquaternion q2);
 * QMquaternion qm_quaternion_scale           (QMquaternion q, float s);
 * QMquaternion qm_quaternion_dot             (QMquaternion q1, QMquaternion q2);
 * float        qm_quaternion_length          (QMquaternion q);
 * QMquaternion qm_quaternion_normalize       (QMquaternion q);
 * QMquaternion qm_quaternion_conjugate       (QMquaternion q);
 * QMquaternion qm_quaternion_inv             (QMquaternion q);
 * QMquaternion qm_quaternion_slerp           (QMquaternion q1, QMquaternion q2, float a);
 * QMquaternion qm_quaternion_from_axis_angle (QMvec3 axis, float angle);
 * QMquaternion qm_quaternion_from_euler      (QMvec3 angles);
 * QMmat4       qm_quaternion_to_mat4         (QMquaternion q);
 * 
 * QMbboxn      qm_bboxn_load                 (const float* b);
 * void         qm_bboxn_store                (QMbboxn b, float* out);
 * QMbboxn      qm_bboxn_initialized          ();
 * QMbboxn      qm_bboxn_union                (QMbboxn b1, QMbboxn b2);
 * void         qm_bboxn_union_inplace        (QMbboxn* b1, QMbboxn b2);
 * QMbboxn      qm_bboxn_union_vecn           (QMbboxn b, QMvecn v);
 * void         qm_bboxn_union_vecn_inplace   (QMbboxn* b, QMvecn v);
 * QMvecn       qm_bboxn_extent               (QMbboxn b);
 * QMvecn       qm_bboxn_centroid             (QMbboxn b);
 * QMvecn       qm_bboxn_offset               (QMbboxn b, QMvecn v);
 * 
 * float        qm_bbox2_perimeter            (QMbbox2 b);
 * float        qm_bbox3_surface_area         (QMbbox3 b);
 */

#ifndef QM_MATH_H
#define QM_MATH_H

#ifdef __cplusplus
extern "C"
{
#endif

//check for SSE support
#if defined(__SSE3__)
	#include <xmmintrin.h>
	#include <pmmintrin.h>

	#define QM_USE_SSE 1
#else
	#define QM_USE_SSE 0
#endif

//define customizeable function prefix
#ifndef QM_FUNC_PREFIX
	#define QM_FUNC_PREFIX(name) qm_##name
#endif
#ifndef QM_FUNC_ATTRIBS
	#define QM_FUNC_ATTRIBS static inline
#endif

//include crt math if needed
#if !defined(QM_SQRTF) || !defined(QM_SINF) || !defined(QM_COSF) || !defined(QM_TANF) || !defined(QM_ACOSF)
	#include <math.h>

	#define QM_SQRTF(x) sqrtf(x)
	#define QM_SINF(x)  sinf(x)
	#define QM_COSF(x)  cosf(x)
	#define QM_TANF(x)  tanf(x)
	#define QM_ACOSF(x) acosf(x)
#endif

//remove troublesome win32 #defines
#ifdef _WIN32
	#undef near
	#undef far
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

	#if QM_USE_SSE

	__m128 packed;

	#endif
} QMvec4;

//-----------------------------//
//matrices are column-major

//a 3x3 matrix of floats
typedef union
{
	float m[3][3];
	QMvec3 v[3];
} QMmat3;

//a 4x4 matrix of floats
typedef union
{
	float m[4][4];
	QMvec4 v[4];

	#if QM_USE_SSE

	__m128 packed[4]; //array of columns

	#endif
} QMmat4;

//-----------------------------//

//a quaternion
typedef union
{
	float q[4];
	struct{ float x, y, z, w; };

	#if QM_USE_SSE

	__m128 packed;

	#endif
} QMquaternion;

//-----------------------------//

//a 2-dimensional bounding box
typedef struct
{
	QMvec2 min;
	QMvec2 max;
} QMbbox2;

//a 3-dimensional bounding box
typedef struct
{
	QMvec3 min;
	QMvec3 max;
} QMbbox3;

//----------------------------------------------------------------------//
//HELPER FUNCS:

#define QM_MIN(x, y) ((x) < (y) ? (x) : (y))
#define QM_MAX(x, y) ((x) > (y) ? (x) : (y))
#define QM_ABS(x) ((x) > 0 ? (x) : -(x))

QM_FUNC_ATTRIBS float QM_FUNC_PREFIX(rad_to_deg)(float rad)
{
	return rad * 57.2957795131f;
}

QM_FUNC_ATTRIBS float QM_FUNC_PREFIX(deg_to_rad)(float deg)
{
	return deg * 0.01745329251f;
}

#if QM_USE_SSE

QM_FUNC_ATTRIBS __m128 QM_FUNC_PREFIX(mat4_mult_column_sse)(__m128 c1, QMmat4 m2)
{
	__m128 result;

	result =                    _mm_mul_ps(_mm_shuffle_ps(c1, c1, _MM_SHUFFLE(0, 0, 0, 0)), m2.packed[0]);
	result = _mm_add_ps(result, _mm_mul_ps(_mm_shuffle_ps(c1, c1, _MM_SHUFFLE(1, 1, 1, 1)), m2.packed[1]));
	result = _mm_add_ps(result, _mm_mul_ps(_mm_shuffle_ps(c1, c1, _MM_SHUFFLE(2, 2, 2, 2)), m2.packed[2]));
	result = _mm_add_ps(result, _mm_mul_ps(_mm_shuffle_ps(c1, c1, _MM_SHUFFLE(3, 3, 3, 3)), m2.packed[3]));

	return result;
}

#endif

//----------------------------------------------------------------------//
//VECTOR FUNCTIONS:

//loading:

QM_FUNC_ATTRIBS QMvec2 QM_FUNC_PREFIX(vec2_load)(const float* in)
{
	return (QMvec2){ in[0], in[1] };
}

QM_FUNC_ATTRIBS QMvec3 QM_FUNC_PREFIX(vec3_load)(const float* in)
{
	return (QMvec3){ in[0], in[1], in[2] };
}

QM_FUNC_ATTRIBS QMvec4 QM_FUNC_PREFIX(vec4_load)(const float* in)
{
	return (QMvec4){ in[0], in[1], in[2], in[3] };
}

//storing:

QM_FUNC_ATTRIBS void QM_FUNC_PREFIX(vec2_store)(QMvec2 v, float* out)
{
	out[0] = v.x;
	out[1] = v.y;
}

QM_FUNC_ATTRIBS void QM_FUNC_PREFIX(vec3_store)(QMvec3 v, float* out)
{
	out[0] = v.x;
	out[1] = v.y;
	out[2] = v.z;
}

QM_FUNC_ATTRIBS void QM_FUNC_PREFIX(vec4_store)(QMvec4 v, float* out)
{
	out[0] = v.x;
	out[1] = v.y;
	out[2] = v.z;
	out[3] = v.w;
}

//full:

QM_FUNC_ATTRIBS QMvec2 QM_FUNC_PREFIX(vec2_full)(float val)
{
	return (QMvec2){ val, val };
}

QM_FUNC_ATTRIBS QMvec3 QM_FUNC_PREFIX(vec3_full)(float val)
{
	return (QMvec3){ val, val, val };
}

QM_FUNC_ATTRIBS QMvec4 QM_FUNC_PREFIX(vec4_full)(float val)
{
	return (QMvec4){ val, val, val, val };
}

//addition:

QM_FUNC_ATTRIBS QMvec2 QM_FUNC_PREFIX(vec2_add)(QMvec2 v1, QMvec2 v2)
{
	QMvec2 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;

	return result;
}

QM_FUNC_ATTRIBS QMvec3 QM_FUNC_PREFIX(vec3_add)(QMvec3 v1, QMvec3 v2)
{
	QMvec3 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;
}

QM_FUNC_ATTRIBS QMvec4 QM_FUNC_PREFIX(vec4_add)(QMvec4 v1, QMvec4 v2)
{
	QMvec4 result;

	#if QM_USE_SSE

	result.packed = _mm_add_ps(v1.packed, v2.packed);

	#else

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	result.w = v1.w + v2.w;

	#endif

	return result;
}

//subtraction:

QM_FUNC_ATTRIBS QMvec2 QM_FUNC_PREFIX(vec2_sub)(QMvec2 v1, QMvec2 v2)
{
	QMvec2 result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;

	return result;
}

QM_FUNC_ATTRIBS QMvec3 QM_FUNC_PREFIX(vec3_sub)(QMvec3 v1, QMvec3 v2)
{
	QMvec3 result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;

	return result;
}

QM_FUNC_ATTRIBS QMvec4 QM_FUNC_PREFIX(vec4_sub)(QMvec4 v1, QMvec4 v2)
{
	QMvec4 result;

	#if QM_USE_SSE

	result.packed = _mm_sub_ps(v1.packed, v2.packed);

	#else

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	result.w = v1.w - v2.w;

	#endif

	return result;
}

//multiplication:

QM_FUNC_ATTRIBS QMvec2 QM_FUNC_PREFIX(vec2_mult)(QMvec2 v1, QMvec2 v2)
{
	QMvec2 result;

	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;

	return result;
}

QM_FUNC_ATTRIBS QMvec3 QM_FUNC_PREFIX(vec3_mult)(QMvec3 v1, QMvec3 v2)
{
	QMvec3 result;

	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;

	return result;
}

QM_FUNC_ATTRIBS QMvec4 QM_FUNC_PREFIX(vec4_mult)(QMvec4 v1, QMvec4 v2)
{
	QMvec4 result;

	#if QM_USE_SSE

	result.packed = _mm_mul_ps(v1.packed, v2.packed);

	#else

	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;
	result.w = v1.w * v2.w;

	#endif

	return result;
}

//division:

QM_FUNC_ATTRIBS QMvec2 QM_FUNC_PREFIX(vec2_div)(QMvec2 v1, QMvec2 v2)
{
	QMvec2 result;

	result.x = v1.x / v2.x;
	result.y = v1.y / v2.y;

	return result;
}

QM_FUNC_ATTRIBS QMvec3 QM_FUNC_PREFIX(vec3_div)(QMvec3 v1, QMvec3 v2)
{
	QMvec3 result;

	result.x = v1.x / v2.x;
	result.y = v1.y / v2.y;
	result.z = v1.z / v2.z;

	return result;
}

QM_FUNC_ATTRIBS QMvec4 QM_FUNC_PREFIX(vec4_div)(QMvec4 v1, QMvec4 v2)
{
	QMvec4 result;

	#if QM_USE_SSE

	result.packed = _mm_div_ps(v1.packed, v2.packed);

	#else

	result.x = v1.x / v2.x;
	result.y = v1.y / v2.y;
	result.z = v1.z / v2.z;
	result.w = v1.w / v2.w;

	#endif

	return result;
}

//scalar multiplication:

QM_FUNC_ATTRIBS QMvec2 QM_FUNC_PREFIX(vec2_scale)(QMvec2 v, float s)
{
	QMvec2 result;

	result.x = v.x * s;
	result.y = v.y * s;

	return result;
}

QM_FUNC_ATTRIBS QMvec3 QM_FUNC_PREFIX(vec3_scale)(QMvec3 v, float s)
{
	QMvec3 result;

	result.x = v.x * s;
	result.y = v.y * s;
	result.z = v.z * s;

	return result;
}

QM_FUNC_ATTRIBS QMvec4 QM_FUNC_PREFIX(vec4_scale)(QMvec4 v, float s)
{
	QMvec4 result;

	#if QM_USE_SSE

	__m128 scale = _mm_set1_ps(s);
	result.packed = _mm_mul_ps(v.packed, scale);

	#else

	result.x = v.x * s;
	result.y = v.y * s;
	result.z = v.z * s;
	result.w = v.w * s;

	#endif

	return result;
}

//dot product:

QM_FUNC_ATTRIBS float QM_FUNC_PREFIX(vec2_dot)(QMvec2 v1, QMvec2 v2)
{
	float result;

	result = v1.x * v2.x + v1.y * v2.y;

	return result;
}

QM_FUNC_ATTRIBS float QM_FUNC_PREFIX(vec3_dot)(QMvec3 v1, QMvec3 v2)
{
	float result;

	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

	return result;
}

QM_FUNC_ATTRIBS float QM_FUNC_PREFIX(vec4_dot)(QMvec4 v1, QMvec4 v2)
{
	float result;

	#if QM_USE_SSE

	__m128 r = _mm_mul_ps(v1.packed, v2.packed);
	r = _mm_hadd_ps(r, r);
	r = _mm_hadd_ps(r, r);
	_mm_store_ss(&result, r);

	#else

	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;

	#endif

	return result;
}

//cross product

QM_FUNC_ATTRIBS QMvec3 QM_FUNC_PREFIX(vec3_cross)(QMvec3 v1, QMvec3 v2)
{
	QMvec3 result;

	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);

	return result;
}

//length:

QM_FUNC_ATTRIBS float QM_FUNC_PREFIX(vec2_length)(QMvec2 v)
{
	float result;

	result = QM_SQRTF(QM_FUNC_PREFIX(vec2_dot)(v, v));

	return result;
}

QM_FUNC_ATTRIBS float QM_FUNC_PREFIX(vec3_length)(QMvec3 v)
{
	float result;

	result = QM_SQRTF(QM_FUNC_PREFIX(vec3_dot)(v, v));

	return result;
}

QM_FUNC_ATTRIBS float QM_FUNC_PREFIX(vec4_length)(QMvec4 v)
{
	float result;

	result = QM_SQRTF(QM_FUNC_PREFIX(vec4_dot)(v, v));

	return result;
}

//normalize:

QM_FUNC_ATTRIBS QMvec2 QM_FUNC_PREFIX(vec2_normalize)(QMvec2 v)
{
	QMvec2 result = {0};

	float invLen = QM_FUNC_PREFIX(vec2_length)(v);
	if(invLen != 0.0f)
	{
		invLen = 1.0f / invLen;
		result.x = v.x * invLen;
		result.y = v.y * invLen;
	}

	return result;
}

QM_FUNC_ATTRIBS QMvec3 QM_FUNC_PREFIX(vec3_normalize)(QMvec3 v)
{
	QMvec3 result = {0};

	float invLen = QM_FUNC_PREFIX(vec3_length)(v);
	if(invLen != 0.0f)
	{
		invLen = 1.0f / invLen;
		result.x = v.x * invLen;
		result.y = v.y * invLen;
		result.z = v.z * invLen;
	}

	return result;
}

QM_FUNC_ATTRIBS QMvec4 QM_FUNC_PREFIX(vec4_normalize)(QMvec4 v)
{
	QMvec4 result = {0};

	float len = QM_FUNC_PREFIX(vec4_length)(v);
	if(len != 0.0f)
	{
		#if QM_USE_SSE

		__m128 scale = _mm_set1_ps(len);
		result.packed = _mm_div_ps(v.packed, scale);

		#else

		float invLen = 1.0f / len;

		result.x = v.x * invLen;
		result.y = v.y * invLen;
		result.z = v.z * invLen;
		result.w = v.w * invLen;

		#endif
	}

	return result;
}

//distance:

QM_FUNC_ATTRIBS float QM_FUNC_PREFIX(vec2_distance)(QMvec2 v1, QMvec2 v2)
{
	float result;

	QMvec2 to = QM_FUNC_PREFIX(vec2_sub)(v1, v2);
	result = QM_FUNC_PREFIX(vec2_length)(to);

	return result;
}

QM_FUNC_ATTRIBS float QM_FUNC_PREFIX(vec3_distance)(QMvec3 v1, QMvec3 v2)
{
	float result;

	QMvec3 to = QM_FUNC_PREFIX(vec3_sub)(v1, v2);
	result = QM_FUNC_PREFIX(vec3_length)(to);

	return result;
}

QM_FUNC_ATTRIBS float QM_FUNC_PREFIX(vec4_distance)(QMvec4 v1, QMvec4 v2)
{
	float result;

	QMvec4 to = QM_FUNC_PREFIX(vec4_sub)(v1, v2);
	result = QM_FUNC_PREFIX(vec4_length)(to);

	return result;
}

//equality:

QM_FUNC_ATTRIBS QMbool QM_FUNC_PREFIX(vec2_equals)(QMvec2 v1, QMvec2 v2)
{
	QMbool result;

	result = (v1.x == v2.x) && (v1.y == v2.y); 

	return result;	
}

QM_FUNC_ATTRIBS QMbool QM_FUNC_PREFIX(vec3_equals)(QMvec3 v1, QMvec3 v2)
{
	QMbool result;

	result = (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z); 

	return result;	
}

QM_FUNC_ATTRIBS QMbool QM_FUNC_PREFIX(vec4_equals)(QMvec4 v1, QMvec4 v2)
{
	QMbool result;

	//TODO: there are SIMD instructions for floating point equality, find a way to get a single bool from them
	result = (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z) && (v1.w == v2.w); 

	return result;	
}

//min:

QM_FUNC_ATTRIBS QMvec2 QM_FUNC_PREFIX(vec2_min)(QMvec2 v1, QMvec2 v2)
{
	QMvec2 result;

	result.x = QM_MIN(v1.x, v2.x);
	result.y = QM_MIN(v1.y, v2.y);

	return result;
}

QM_FUNC_ATTRIBS QMvec3 QM_FUNC_PREFIX(vec3_min)(QMvec3 v1, QMvec3 v2)
{
	QMvec3 result;

	result.x = QM_MIN(v1.x, v2.x);
	result.y = QM_MIN(v1.y, v2.y);
	result.z = QM_MIN(v1.z, v2.z);

	return result;
}

QM_FUNC_ATTRIBS QMvec4 QM_FUNC_PREFIX(vec4_min)(QMvec4 v1, QMvec4 v2)
{
	QMvec4 result;

	#if QM_USE_SSE

	result.packed = _mm_min_ps(v1.packed, v2.packed);

	#else

	result.x = QM_MIN(v1.x, v2.x);
	result.y = QM_MIN(v1.y, v2.y);
	result.z = QM_MIN(v1.z, v2.z);
	result.w = QM_MIN(v1.w, v2.w);

	#endif

	return result;
}

//max:

QM_FUNC_ATTRIBS QMvec2 QM_FUNC_PREFIX(vec2_max)(QMvec2 v1, QMvec2 v2)
{
	QMvec2 result;

	result.x = QM_MAX(v1.x, v2.x);
	result.y = QM_MAX(v1.y, v2.y);

	return result;
}

QM_FUNC_ATTRIBS QMvec3 QM_FUNC_PREFIX(vec3_max)(QMvec3 v1, QMvec3 v2)
{
	QMvec3 result;

	result.x = QM_MAX(v1.x, v2.x);
	result.y = QM_MAX(v1.y, v2.y);
	result.z = QM_MAX(v1.z, v2.z);

	return result;
}

QM_FUNC_ATTRIBS QMvec4 QM_FUNC_PREFIX(vec4_max)(QMvec4 v1, QMvec4 v2)
{
	QMvec4 result;

	#if QM_USE_SSE

	result.packed = _mm_max_ps(v1.packed, v2.packed);

	#else

	result.x = QM_MAX(v1.x, v2.x);
	result.y = QM_MAX(v1.y, v2.y);
	result.z = QM_MAX(v1.z, v2.z);
	result.w = QM_MAX(v1.w, v2.w);

	#endif

	return result;
}

//----------------------------------------------------------------------//
//MATRIX FUNCTIONS:

//loading:

QM_FUNC_ATTRIBS QMmat3 QM_FUNC_PREFIX(mat3_load)(const float* in)
{
	return (QMmat3){
		in[0], in[1], in[2],
		in[3], in[4], in[5],
		in[6], in[7], in[8]
	};
}

QM_FUNC_ATTRIBS QMmat3 QM_FUNC_PREFIX(mat3_load_row_major)(const float* in)
{
	return (QMmat3){
		in[0], in[3], in[6],
		in[1], in[4], in[7],
		in[2], in[5], in[8]
	};
}

QM_FUNC_ATTRIBS QMmat4 QM_FUNC_PREFIX(mat4_load)(const float* in)
{
	return (QMmat4){
		in[0 ], in[1 ], in[2 ], in[3 ],
		in[4 ], in[5 ], in[6 ], in[7 ],
		in[8 ], in[9 ], in[10], in[11],
		in[12], in[13], in[14], in[15]
	};
}

QM_FUNC_ATTRIBS QMmat4 QM_FUNC_PREFIX(mat4_load_row_major)(const float* in)
{
	return (QMmat4){
		in[0], in[4], in[8 ], in[12],
		in[1], in[5], in[9 ], in[13],
		in[2], in[6], in[10], in[14],
		in[3], in[7], in[11], in[15]
	};
}

//storing:

QM_FUNC_ATTRIBS void QM_FUNC_PREFIX(mat3_store)(QMmat3 m, float* out)
{
	out[0] = m.m[0][0];
	out[1] = m.m[0][1];
	out[2] = m.m[0][2];

	out[3] = m.m[1][0];
	out[4] = m.m[1][1];
	out[5] = m.m[1][2];

	out[6] = m.m[2][0];
	out[7] = m.m[2][1];
	out[8] = m.m[2][2];
}

QM_FUNC_ATTRIBS void QM_FUNC_PREFIX(mat3_store_row_major)(QMmat3 m, float* out)
{
	out[0] = m.m[0][0];
	out[1] = m.m[1][0];
	out[2] = m.m[2][0];

	out[3] = m.m[0][1];
	out[4] = m.m[1][1];
	out[5] = m.m[2][1];

	out[6] = m.m[0][2];
	out[7] = m.m[1][2];
	out[8] = m.m[2][2];
}

QM_FUNC_ATTRIBS void QM_FUNC_PREFIX(mat4_store)(QMmat4 m, float* out)
{
	out[0] = m.m[0][0];
	out[1] = m.m[0][1];
	out[2] = m.m[0][2];
	out[3] = m.m[0][3];

	out[4] = m.m[1][0];
	out[5] = m.m[1][1];
	out[6] = m.m[1][2];
	out[7] = m.m[1][3];

	out[ 8] = m.m[2][0];
	out[ 9] = m.m[2][1];
	out[10] = m.m[2][2];
	out[11] = m.m[2][3];

	out[12] = m.m[3][0];
	out[13] = m.m[3][1];
	out[14] = m.m[3][2];
	out[15] = m.m[3][3];
}

QM_FUNC_ATTRIBS void QM_FUNC_PREFIX(mat4_store_row_major)(QMmat4 m, float* out)
{
	out[0] = m.m[0][0];
	out[1] = m.m[1][0];
	out[2] = m.m[2][0];
	out[3] = m.m[3][0];

	out[4] = m.m[0][1];
	out[5] = m.m[1][1];
	out[6] = m.m[2][1];
	out[7] = m.m[3][1];

	out[ 8] = m.m[0][2];
	out[ 9] = m.m[1][2];
	out[10] = m.m[2][2];
	out[11] = m.m[3][2];

	out[12] = m.m[0][3];
	out[13] = m.m[1][3];
	out[14] = m.m[2][3];
	out[15] = m.m[3][3];
}

//initialization:

QM_FUNC_ATTRIBS QMmat3 QM_FUNC_PREFIX(mat3_identity)()
{
	QMmat3 result = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	return result;
}

QM_FUNC_ATTRIBS QMmat4 QM_FUNC_PREFIX(mat4_identity)()
{
	QMmat4 result = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	return result;
}

//addition:

QM_FUNC_ATTRIBS QMmat3 QM_FUNC_PREFIX(mat3_add)(QMmat3 m1, QMmat3 m2)
{
	QMmat3 result;

	result.m[0][0] = m1.m[0][0] + m2.m[0][0];
	result.m[0][1] = m1.m[0][1] + m2.m[0][1];
	result.m[0][2] = m1.m[0][2] + m2.m[0][2];
	result.m[1][0] = m1.m[1][0] + m2.m[1][0];
	result.m[1][1] = m1.m[1][1] + m2.m[1][1];
	result.m[1][2] = m1.m[1][2] + m2.m[1][2];
	result.m[2][0] = m1.m[2][0] + m2.m[2][0];
	result.m[2][1] = m1.m[2][1] + m2.m[2][1];
	result.m[2][2] = m1.m[2][2] + m2.m[2][2];

	return result;
}

QM_FUNC_ATTRIBS QMmat4 QM_FUNC_PREFIX(mat4_add)(QMmat4 m1, QMmat4 m2)
{
	QMmat4 result;

	#if QM_USE_SSE

	result.packed[0] = _mm_add_ps(m1.packed[0], m2.packed[0]);
	result.packed[1] = _mm_add_ps(m1.packed[1], m2.packed[1]);
	result.packed[2] = _mm_add_ps(m1.packed[2], m2.packed[2]);
	result.packed[3] = _mm_add_ps(m1.packed[3], m2.packed[3]);

	#else

	result.m[0][0] = m1.m[0][0] + m2.m[0][0];
	result.m[0][1] = m1.m[0][1] + m2.m[0][1];
	result.m[0][2] = m1.m[0][2] + m2.m[0][2];
	result.m[0][3] = m1.m[0][3] + m2.m[0][3];
	result.m[1][0] = m1.m[1][0] + m2.m[1][0];
	result.m[1][1] = m1.m[1][1] + m2.m[1][1];
	result.m[1][2] = m1.m[1][2] + m2.m[1][2];
	result.m[1][3] = m1.m[1][3] + m2.m[1][3];
	result.m[2][0] = m1.m[2][0] + m2.m[2][0];
	result.m[2][1] = m1.m[2][1] + m2.m[2][1];
	result.m[2][2] = m1.m[2][2] + m2.m[2][2];
	result.m[2][3] = m1.m[2][3] + m2.m[2][3];
	result.m[3][0] = m1.m[3][0] + m2.m[3][0];
	result.m[3][1] = m1.m[3][1] + m2.m[3][1];
	result.m[3][2] = m1.m[3][2] + m2.m[3][2];
	result.m[3][3] = m1.m[3][3] + m2.m[3][3];

	#endif

	return result;
}

//subtraction:

QM_FUNC_ATTRIBS QMmat3 QM_FUNC_PREFIX(mat3_sub)(QMmat3 m1, QMmat3 m2)
{
	QMmat3 result;

	result.m[0][0] = m1.m[0][0] - m2.m[0][0];
	result.m[0][1] = m1.m[0][1] - m2.m[0][1];
	result.m[0][2] = m1.m[0][2] - m2.m[0][2];
	result.m[1][0] = m1.m[1][0] - m2.m[1][0];
	result.m[1][1] = m1.m[1][1] - m2.m[1][1];
	result.m[1][2] = m1.m[1][2] - m2.m[1][2];
	result.m[2][0] = m1.m[2][0] - m2.m[2][0];
	result.m[2][1] = m1.m[2][1] - m2.m[2][1];
	result.m[2][2] = m1.m[2][2] - m2.m[2][2];

	return result;
}

QM_FUNC_ATTRIBS QMmat4 QM_FUNC_PREFIX(mat4_sub)(QMmat4 m1, QMmat4 m2)
{
	QMmat4 result;

	#if QM_USE_SSE

	result.packed[0] = _mm_sub_ps(m1.packed[0], m2.packed[0]);
	result.packed[1] = _mm_sub_ps(m1.packed[1], m2.packed[1]);
	result.packed[2] = _mm_sub_ps(m1.packed[2], m2.packed[2]);
	result.packed[3] = _mm_sub_ps(m1.packed[3], m2.packed[3]);

	#else

	result.m[0][0] = m1.m[0][0] - m2.m[0][0];
	result.m[0][1] = m1.m[0][1] - m2.m[0][1];
	result.m[0][2] = m1.m[0][2] - m2.m[0][2];
	result.m[0][3] = m1.m[0][3] - m2.m[0][3];
	result.m[1][0] = m1.m[1][0] - m2.m[1][0];
	result.m[1][1] = m1.m[1][1] - m2.m[1][1];
	result.m[1][2] = m1.m[1][2] - m2.m[1][2];
	result.m[1][3] = m1.m[1][3] - m2.m[1][3];
	result.m[2][0] = m1.m[2][0] - m2.m[2][0];
	result.m[2][1] = m1.m[2][1] - m2.m[2][1];
	result.m[2][2] = m1.m[2][2] - m2.m[2][2];
	result.m[2][3] = m1.m[2][3] - m2.m[2][3];
	result.m[3][0] = m1.m[3][0] - m2.m[3][0];
	result.m[3][1] = m1.m[3][1] - m2.m[3][1];
	result.m[3][2] = m1.m[3][2] - m2.m[3][2];
	result.m[3][3] = m1.m[3][3] - m2.m[3][3];

	#endif

	return result;
}

//multiplication:

QM_FUNC_ATTRIBS QMmat3 QM_FUNC_PREFIX(mat3_mult)(QMmat3 m1, QMmat3 m2)
{
	QMmat3 result;

	result.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[1][0] * m2.m[0][1] + m1.m[2][0] * m2.m[0][2];
	result.m[0][1] = m1.m[0][1] * m2.m[0][0] + m1.m[1][1] * m2.m[0][1] + m1.m[2][1] * m2.m[0][2];
	result.m[0][2] = m1.m[0][2] * m2.m[0][0] + m1.m[1][2] * m2.m[0][1] + m1.m[2][2] * m2.m[0][2];
	result.m[1][0] = m1.m[0][0] * m2.m[1][0] + m1.m[1][0] * m2.m[1][1] + m1.m[2][0] * m2.m[1][2];
	result.m[1][1] = m1.m[0][1] * m2.m[1][0] + m1.m[1][1] * m2.m[1][1] + m1.m[2][1] * m2.m[1][2];
	result.m[1][2] = m1.m[0][2] * m2.m[1][0] + m1.m[1][2] * m2.m[1][1] + m1.m[2][2] * m2.m[1][2];
	result.m[2][0] = m1.m[0][0] * m2.m[2][0] + m1.m[1][0] * m2.m[2][1] + m1.m[2][0] * m2.m[2][2];
	result.m[2][1] = m1.m[0][1] * m2.m[2][0] + m1.m[1][1] * m2.m[2][1] + m1.m[2][1] * m2.m[2][2];
	result.m[2][2] = m1.m[0][2] * m2.m[2][0] + m1.m[1][2] * m2.m[2][1] + m1.m[2][2] * m2.m[2][2];

	return result;
}

QM_FUNC_ATTRIBS QMmat4 QM_FUNC_PREFIX(mat4_mult)(QMmat4 m1, QMmat4 m2)
{
	QMmat4 result;

	#if QM_USE_SSE

	result.packed[0] = QM_FUNC_PREFIX(mat4_mult_column_sse)(m2.packed[0], m1);
	result.packed[1] = QM_FUNC_PREFIX(mat4_mult_column_sse)(m2.packed[1], m1);
	result.packed[2] = QM_FUNC_PREFIX(mat4_mult_column_sse)(m2.packed[2], m1);
	result.packed[3] = QM_FUNC_PREFIX(mat4_mult_column_sse)(m2.packed[3], m1);

	#else

	result.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[1][0] * m2.m[0][1] + m1.m[2][0] * m2.m[0][2] + m1.m[3][0] * m2.m[0][3];
	result.m[0][1] = m1.m[0][1] * m2.m[0][0] + m1.m[1][1] * m2.m[0][1] + m1.m[2][1] * m2.m[0][2] + m1.m[3][1] * m2.m[0][3];
	result.m[0][2] = m1.m[0][2] * m2.m[0][0] + m1.m[1][2] * m2.m[0][1] + m1.m[2][2] * m2.m[0][2] + m1.m[3][2] * m2.m[0][3];
	result.m[0][3] = m1.m[0][3] * m2.m[0][0] + m1.m[1][3] * m2.m[0][1] + m1.m[2][3] * m2.m[0][2] + m1.m[3][3] * m2.m[0][3];
	result.m[1][0] = m1.m[0][0] * m2.m[1][0] + m1.m[1][0] * m2.m[1][1] + m1.m[2][0] * m2.m[1][2] + m1.m[3][0] * m2.m[1][3];
	result.m[1][1] = m1.m[0][1] * m2.m[1][0] + m1.m[1][1] * m2.m[1][1] + m1.m[2][1] * m2.m[1][2] + m1.m[3][1] * m2.m[1][3];
	result.m[1][2] = m1.m[0][2] * m2.m[1][0] + m1.m[1][2] * m2.m[1][1] + m1.m[2][2] * m2.m[1][2] + m1.m[3][2] * m2.m[1][3];
	result.m[1][3] = m1.m[0][3] * m2.m[1][0] + m1.m[1][3] * m2.m[1][1] + m1.m[2][3] * m2.m[1][2] + m1.m[3][3] * m2.m[1][3];
	result.m[2][0] = m1.m[0][0] * m2.m[2][0] + m1.m[1][0] * m2.m[2][1] + m1.m[2][0] * m2.m[2][2] + m1.m[3][0] * m2.m[2][3];
	result.m[2][1] = m1.m[0][1] * m2.m[2][0] + m1.m[1][1] * m2.m[2][1] + m1.m[2][1] * m2.m[2][2] + m1.m[3][1] * m2.m[2][3];
	result.m[2][2] = m1.m[0][2] * m2.m[2][0] + m1.m[1][2] * m2.m[2][1] + m1.m[2][2] * m2.m[2][2] + m1.m[3][2] * m2.m[2][3];
	result.m[2][3] = m1.m[0][3] * m2.m[2][0] + m1.m[1][3] * m2.m[2][1] + m1.m[2][3] * m2.m[2][2] + m1.m[3][3] * m2.m[2][3];
	result.m[3][0] = m1.m[0][0] * m2.m[3][0] + m1.m[1][0] * m2.m[3][1] + m1.m[2][0] * m2.m[3][2] + m1.m[3][0] * m2.m[3][3];
	result.m[3][1] = m1.m[0][1] * m2.m[3][0] + m1.m[1][1] * m2.m[3][1] + m1.m[2][1] * m2.m[3][2] + m1.m[3][1] * m2.m[3][3];
	result.m[3][2] = m1.m[0][2] * m2.m[3][0] + m1.m[1][2] * m2.m[3][1] + m1.m[2][2] * m2.m[3][2] + m1.m[3][2] * m2.m[3][3];
	result.m[3][3] = m1.m[0][3] * m2.m[3][0] + m1.m[1][3] * m2.m[3][1] + m1.m[2][3] * m2.m[3][2] + m1.m[3][3] * m2.m[3][3];

	#endif

	return result;
}

QM_FUNC_ATTRIBS QMvec3 QM_FUNC_PREFIX(mat3_mult_vec3)(QMmat3 m, QMvec3 v)
{
	QMvec3 result;

	result.x = m.m[0][0] * v.x + m.m[1][0] * v.y + m.m[2][0] * v.z;
	result.y = m.m[0][1] * v.x + m.m[1][1] * v.y + m.m[2][1] * v.z;
	result.z = m.m[0][2] * v.x + m.m[1][2] * v.y + m.m[2][2] * v.z;

	return result;
}

QM_FUNC_ATTRIBS QMvec4 QM_FUNC_PREFIX(mat4_mult_vec4)(QMmat4 m, QMvec4 v)
{
	QMvec4 result;

	#if QM_USE_SSE

	result.packed = QM_FUNC_PREFIX(mat4_mult_column_sse)(v.packed, m);

	#else

	result.x = m.m[0][0] * v.x + m.m[1][0] * v.y + m.m[2][0] * v.z + m.m[3][0] * v.w;
	result.y = m.m[0][1] * v.x + m.m[1][1] * v.y + m.m[2][1] * v.z + m.m[3][1] * v.w;
	result.z = m.m[0][2] * v.x + m.m[1][2] * v.y + m.m[2][2] * v.z + m.m[3][2] * v.w;
	result.w = m.m[0][3] * v.x + m.m[1][3] * v.y + m.m[2][3] * v.z + m.m[3][3] * v.w;

	#endif

	return result;
}

QM_FUNC_ATTRIBS QMvec3 QM_FUNC_PREFIX(mat4_transform_vec3)(QMmat4 m, QMvec3 v)
{
	QMvec3 result;

	result.x = m.m[0][0] * v.x + m.m[1][0] * v.y + m.m[2][0] * v.z + m.m[3][0];
	result.y = m.m[0][1] * v.x + m.m[1][1] * v.y + m.m[2][1] * v.z + m.m[3][1];
	result.z = m.m[0][2] * v.x + m.m[1][2] * v.y + m.m[2][2] * v.z + m.m[3][2];

	return result;	
}

//transpose:

QM_FUNC_ATTRIBS QMmat3 QM_FUNC_PREFIX(mat3_transpose)(QMmat3 m)
{
	QMmat3 result;

	result.m[0][0] = m.m[0][0];
	result.m[0][1] = m.m[1][0];
	result.m[0][2] = m.m[2][0];
	result.m[1][0] = m.m[0][1];
	result.m[1][1] = m.m[1][1];
	result.m[1][2] = m.m[2][1];
	result.m[2][0] = m.m[0][2];
	result.m[2][1] = m.m[1][2];
	result.m[2][2] = m.m[2][2];

	return result;
}

QM_FUNC_ATTRIBS QMmat4 QM_FUNC_PREFIX(mat4_transpose)(QMmat4 m)
{
	QMmat4 result = m;

	#if QM_USE_SSE

	_MM_TRANSPOSE4_PS(result.packed[0], result.packed[1], result.packed[2], result.packed[3]);

	#else

	result.m[0][0] = m.m[0][0];
	result.m[0][1] = m.m[1][0];
	result.m[0][2] = m.m[2][0];
	result.m[0][3] = m.m[3][0];
	result.m[1][0] = m.m[0][1];
	result.m[1][1] = m.m[1][1];
	result.m[1][2] = m.m[2][1];
	result.m[1][3] = m.m[3][1];
	result.m[2][0] = m.m[0][2];
	result.m[2][1] = m.m[1][2];
	result.m[2][2] = m.m[2][2];
	result.m[2][3] = m.m[3][2];
	result.m[3][0] = m.m[0][3];
	result.m[3][1] = m.m[1][3];
	result.m[3][2] = m.m[2][3];
	result.m[3][3] = m.m[3][3];

	#endif

	return result;
}

//inverse:

QM_FUNC_ATTRIBS QMmat3 QM_FUNC_PREFIX(mat3_inv)(QMmat3 m)
{
	QMmat3 result;

	float det;
  	float a = m.m[0][0], b = m.m[0][1], c = m.m[0][2],
	      d = m.m[1][0], e = m.m[1][1], f = m.m[1][2],
	      g = m.m[2][0], h = m.m[2][1], i = m.m[2][2];

	result.m[0][0] =   e * i - f * h;
	result.m[0][1] = -(b * i - h * c);
	result.m[0][2] =   b * f - e * c;
	result.m[1][0] = -(d * i - g * f);
	result.m[1][1] =   a * i - c * g;
	result.m[1][2] = -(a * f - d * c);
	result.m[2][0] =   d * h - g * e;
	result.m[2][1] = -(a * h - g * b);
	result.m[2][2] =   a * e - b * d;

	det = 1.0f / (a * result.m[0][0] + b * result.m[1][0] + c * result.m[2][0]);

	result.m[0][0] *= det;
	result.m[0][1] *= det;
	result.m[0][2] *= det;
	result.m[1][0] *= det;
	result.m[1][1] *= det;
	result.m[1][2] *= det;
	result.m[2][0] *= det;
	result.m[2][1] *= det;
	result.m[2][2] *= det;

	return result;
}

QM_FUNC_ATTRIBS QMmat4 QM_FUNC_PREFIX(mat4_inv)(QMmat4 mat)
{
	//TODO: this function is not SIMD optimized, figure out how to do it

	QMmat4 result;

	float tmp[6];
	float det;
	float a = mat.m[0][0], b = mat.m[0][1], c = mat.m[0][2], d = mat.m[0][3],
	      e = mat.m[1][0], f = mat.m[1][1], g = mat.m[1][2], h = mat.m[1][3],
	      i = mat.m[2][0], j = mat.m[2][1], k = mat.m[2][2], l = mat.m[2][3],
	      m = mat.m[3][0], n = mat.m[3][1], o = mat.m[3][2], p = mat.m[3][3];

	tmp[0] = k * p - o * l; 
	tmp[1] = j * p - n * l; 
	tmp[2] = j * o - n * k;
	tmp[3] = i * p - m * l; 
	tmp[4] = i * o - m * k; 
	tmp[5] = i * n - m * j;

	result.m[0][0] =   f * tmp[0] - g * tmp[1] + h * tmp[2];
	result.m[1][0] = -(e * tmp[0] - g * tmp[3] + h * tmp[4]);
	result.m[2][0] =   e * tmp[1] - f * tmp[3] + h * tmp[5];
	result.m[3][0] = -(e * tmp[2] - f * tmp[4] + g * tmp[5]);

	result.m[0][1] = -(b * tmp[0] - c * tmp[1] + d * tmp[2]);
	result.m[1][1] =   a * tmp[0] - c * tmp[3] + d * tmp[4];
	result.m[2][1] = -(a * tmp[1] - b * tmp[3] + d * tmp[5]);
	result.m[3][1] =   a * tmp[2] - b * tmp[4] + c * tmp[5];

	tmp[0] = g * p - o * h;
	tmp[1] = f * p - n * h;
	tmp[2] = f * o - n * g;
	tmp[3] = e * p - m * h;
	tmp[4] = e * o - m * g;
	tmp[5] = e * n - m * f;

	result.m[0][2] =   b * tmp[0] - c * tmp[1] + d * tmp[2];
	result.m[1][2] = -(a * tmp[0] - c * tmp[3] + d * tmp[4]);
	result.m[2][2] =   a * tmp[1] - b * tmp[3] + d * tmp[5];
	result.m[3][2] = -(a * tmp[2] - b * tmp[4] + c * tmp[5]);

	tmp[0] = g * l - k * h;
	tmp[1] = f * l - j * h;
	tmp[2] = f * k - j * g;
	tmp[3] = e * l - i * h;
	tmp[4] = e * k - i * g;
	tmp[5] = e * j - i * f;

	result.m[0][3] = -(b * tmp[0] - c * tmp[1] + d * tmp[2]);
	result.m[1][3] =   a * tmp[0] - c * tmp[3] + d * tmp[4];
	result.m[2][3] = -(a * tmp[1] - b * tmp[3] + d * tmp[5]);
  	result.m[3][3] =   a * tmp[2] - b * tmp[4] + c * tmp[5];

  	det = 1.0f / (a * result.m[0][0] + b * result.m[1][0]
                + c * result.m[2][0] + d * result.m[3][0]);

	#if QM_USE_SSE

	__m128 scale = _mm_set1_ps(det);
	result.packed[0] = _mm_mul_ps(result.packed[0], scale);
	result.packed[1] = _mm_mul_ps(result.packed[1], scale);
	result.packed[2] = _mm_mul_ps(result.packed[2], scale);
	result.packed[3] = _mm_mul_ps(result.packed[3], scale);

	#else

	result.m[0][0] = result.m[0][0] * det;
	result.m[0][1] = result.m[0][1] * det;
	result.m[0][2] = result.m[0][2] * det;
	result.m[0][3] = result.m[0][3] * det;
	result.m[1][0] = result.m[1][0] * det;
	result.m[1][1] = result.m[1][1] * det;
	result.m[1][2] = result.m[1][2] * det;
	result.m[1][3] = result.m[1][3] * det;
	result.m[2][0] = result.m[2][0] * det;
	result.m[2][1] = result.m[2][1] * det;
	result.m[2][2] = result.m[2][2] * det;
	result.m[2][3] = result.m[2][3] * det;
	result.m[3][0] = result.m[3][0] * det;
	result.m[3][1] = result.m[3][1] * det;
	result.m[3][2] = result.m[3][2] * det;
	result.m[3][3] = result.m[3][3] * det;

	#endif

  	return result;
}

//translation:

QM_FUNC_ATTRIBS QMmat3 QM_FUNC_PREFIX(mat3_translate)(QMvec2 t)
{
	QMmat3 result = QM_FUNC_PREFIX(mat3_identity)();

	result.m[2][0] = t.x;
	result.m[2][1] = t.y;

	return result;
}

QM_FUNC_ATTRIBS QMmat4 QM_FUNC_PREFIX(mat4_translate)(QMvec3 t)
{
	QMmat4 result = QM_FUNC_PREFIX(mat4_identity)();

	result.m[3][0] = t.x;
	result.m[3][1] = t.y;
	result.m[3][2] = t.z;

	return result;
}

//scaling:

QM_FUNC_ATTRIBS QMmat3 QM_FUNC_PREFIX(mat3_scale)(QMvec2 s)
{
	QMmat3 result = QM_FUNC_PREFIX(mat3_identity)();

	result.m[0][0] = s.x;
	result.m[1][1] = s.y;

	return result;
}

QM_FUNC_ATTRIBS QMmat4 QM_FUNC_PREFIX(mat4_scale)(QMvec3 s)
{
	QMmat4 result = QM_FUNC_PREFIX(mat4_identity)();

	result.m[0][0] = s.x;
	result.m[1][1] = s.y;
	result.m[2][2] = s.z;

	return result;
}

//rotation:

QM_FUNC_ATTRIBS QMmat3 QM_FUNC_PREFIX(mat3_rotate)(float angle)
{
	QMmat3 result = QM_FUNC_PREFIX(mat3_identity)();

	float radians = QM_FUNC_PREFIX(deg_to_rad)(angle);
	float sine   = QM_SINF(radians);
	float cosine = QM_COSF(radians);

	result.m[0][0] = cosine;
	result.m[1][0] =   sine;
	result.m[0][1] =  -sine;
	result.m[1][1] = cosine;

	return result;
}

QM_FUNC_ATTRIBS QMmat4 QM_FUNC_PREFIX(mat4_rotate)(QMvec3 axis, float angle)
{
	QMmat4 result = QM_FUNC_PREFIX(mat4_identity)();

	axis = QM_FUNC_PREFIX(vec3_normalize)(axis);

	float radians = QM_FUNC_PREFIX(deg_to_rad)(angle);
	float sine    = QM_SINF(radians);
	float cosine  = QM_COSF(radians);
	float cosine2 = 1.0f - cosine;

	result.m[0][0] = axis.x * axis.x * cosine2 + cosine;
	result.m[0][1] = axis.x * axis.y * cosine2 + axis.z * sine;
	result.m[0][2] = axis.x * axis.z * cosine2 - axis.y * sine;
	result.m[1][0] = axis.y * axis.x * cosine2 - axis.z * sine;
	result.m[1][1] = axis.y * axis.y * cosine2 + cosine;
	result.m[1][2] = axis.y * axis.z * cosine2 + axis.x * sine;
	result.m[2][0] = axis.z * axis.x * cosine2 + axis.y * sine;
	result.m[2][1] = axis.z * axis.y * cosine2 - axis.x * sine;
	result.m[2][2] = axis.z * axis.z * cosine2 + cosine;

	return result;
}

QM_FUNC_ATTRIBS QMmat4 QM_FUNC_PREFIX(mat4_rotate_euler)(QMvec3 angles)
{
	QMmat4 result = QM_FUNC_PREFIX(mat4_identity)();

	QMvec3 radians;
	radians.x = QM_FUNC_PREFIX(deg_to_rad)(angles.x);
	radians.y = QM_FUNC_PREFIX(deg_to_rad)(angles.y);
	radians.z = QM_FUNC_PREFIX(deg_to_rad)(angles.z);

	float sinX = QM_SINF(radians.x);
	float cosX = QM_COSF(radians.x);
	float sinY = QM_SINF(radians.y);
	float cosY = QM_COSF(radians.y);
	float sinZ = QM_SINF(radians.z);
	float cosZ = QM_COSF(radians.z);

	result.m[0][0] = cosY * cosZ;
	result.m[0][1] = cosY * sinZ;
	result.m[0][2] = -sinY;
	result.m[1][0] = sinX * sinY * cosZ - cosX * sinZ;
	result.m[1][1] = sinX * sinY * sinZ + cosX * cosZ;
	result.m[1][2] = sinX * cosY;
	result.m[2][0] = cosX * sinY * cosZ + sinX * sinZ;
	result.m[2][1] = cosX * sinY * sinZ - sinX * cosZ;
	result.m[2][2] = cosX * cosY;

	return result;
}

//to mat3:

QM_FUNC_ATTRIBS QMmat3 QM_FUNC_PREFIX(mat4_top_left)(QMmat4 m)
{
	QMmat3 result;

	result.m[0][0] = m.m[0][0];
	result.m[0][1] = m.m[0][1];
	result.m[0][2] = m.m[0][2];
	result.m[1][0] = m.m[1][0];
	result.m[1][1] = m.m[1][1];
	result.m[1][2] = m.m[1][2];
	result.m[2][0] = m.m[2][0];
	result.m[2][1] = m.m[2][1];
	result.m[2][2] = m.m[2][2];

	return result;
}

//projection:

QM_FUNC_ATTRIBS QMmat4 QM_FUNC_PREFIX(mat4_perspective)(float fov, float aspect, float near, float far)
{
	QMmat4 result = {0};

	float scale = QM_TANF(QM_FUNC_PREFIX(deg_to_rad)(fov * 0.5f)) * near;

	float right = aspect * scale;
	float top   = scale;

	result.m[0][0] = near / right;
	result.m[1][1] = near / top;
	result.m[2][2] = -(far + near) / (far - near);
	result.m[3][2] = -2.0f * far * near / (far - near);
	result.m[2][3] = -1.0f;

	return result;
}

QM_FUNC_ATTRIBS QMmat4 QM_FUNC_PREFIX(mat4_orthographic)(float left, float right, float bot, float top, float near, float far)
{
	QMmat4 result = QM_FUNC_PREFIX(mat4_identity)();

	result.m[0][0] = 2.0f / (right - left);
	result.m[1][1] = 2.0f / (top - bot);
	result.m[2][2] = 2.0f / (near - far);

	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (bot  + top  ) / (bot  - top  );
	result.m[3][2] = (near + far  ) / (near - far  );

	return result;
}

//view matrix:

QM_FUNC_ATTRIBS QMmat4 QM_FUNC_PREFIX(mat4_look)(QMvec3 pos, QMvec3 dir, QMvec3 up)
{
	QMmat4 result;

	QMvec3 r = QM_FUNC_PREFIX(vec3_normalize)(QM_FUNC_PREFIX(vec3_cross)(up, dir));
	QMvec3 u = QM_FUNC_PREFIX(vec3_cross)(dir, r);

	QMmat4 RUD = QM_FUNC_PREFIX(mat4_identity)();
	RUD.m[0][0] = r.x;
	RUD.m[1][0] = r.y;
	RUD.m[2][0] = r.z;
	RUD.m[0][1] = u.x;
	RUD.m[1][1] = u.y;
	RUD.m[2][1] = u.z;
	RUD.m[0][2] = -dir.x;
	RUD.m[1][2] = -dir.y;
	RUD.m[2][2] = -dir.z;

	QMvec3 oppPos = {-pos.x, -pos.y, -pos.z};	
	result = QM_FUNC_PREFIX(mat4_mult)(RUD, QM_FUNC_PREFIX(mat4_translate)(oppPos));

	return result;
}

QM_FUNC_ATTRIBS QMmat4 QM_FUNC_PREFIX(mat4_lookat)(QMvec3 pos, QMvec3 target, QMvec3 up)
{
	QMmat4 result;

	QMvec3 dir = QM_FUNC_PREFIX(vec3_normalize)(QM_FUNC_PREFIX(vec3_sub)(pos, target));
	result = QM_FUNC_PREFIX(mat4_look)(pos, dir, up);

	return result;
}

//----------------------------------------------------------------------//
//QUATERNION FUNCTIONS:

QM_FUNC_ATTRIBS QMquaternion QM_FUNC_PREFIX(quaternion_load)(const float* in)
{
	return (QMquaternion){ in[0], in[1], in[2], in[3] };
}

QM_FUNC_ATTRIBS void QM_FUNC_PREFIX(quaternion_store)(QMquaternion q, float* out)
{
	out[0] = q.x;
	out[1] = q.y;
	out[2] = q.z;
	out[3] = q.w;
}

QM_FUNC_ATTRIBS QMquaternion QM_FUNC_PREFIX(quaternion_identity)()
{
	QMquaternion result;

	result.x = 0.0f;
	result.y = 0.0f;
	result.z = 0.0f;
	result.w = 1.0f;

	return result;
}

QM_FUNC_ATTRIBS QMquaternion QM_FUNC_PREFIX(quaternion_add)(QMquaternion q1, QMquaternion q2)
{
	QMquaternion result;

	#if QM_USE_SSE

	result.packed = _mm_add_ps(q1.packed, q2.packed);

	#else

	result.x = q1.x + q2.x;
	result.y = q1.y + q2.y;
	result.z = q1.z + q2.z;
	result.w = q1.w + q2.w;

	#endif

	return result;
}

QM_FUNC_ATTRIBS QMquaternion QM_FUNC_PREFIX(quaternion_sub)(QMquaternion q1, QMquaternion q2)
{
	QMquaternion result;

	#if QM_USE_SSE

	result.packed = _mm_sub_ps(q1.packed, q2.packed);

	#else

	result.x = q1.x - q2.x;
	result.y = q1.y - q2.y;
	result.z = q1.z - q2.z;
	result.w = q1.w - q2.w;

	#endif

	return result;
}

QM_FUNC_ATTRIBS QMquaternion QM_FUNC_PREFIX(quaternion_mult)(QMquaternion q1, QMquaternion q2)
{
	QMquaternion result;

	#if QM_USE_SSE

	__m128 temp1;
	__m128 temp2;

	temp1 = _mm_shuffle_ps(q1.packed, q1.packed, _MM_SHUFFLE(3, 3, 3, 3));
	temp2 = q2.packed;
	result.packed = _mm_mul_ps(temp1, temp2);

	temp1 = _mm_xor_ps(_mm_shuffle_ps(q1.packed, q1.packed, _MM_SHUFFLE(0, 0, 0, 0)), _mm_setr_ps(0.0f, -0.0f, 0.0f, -0.0f));
	temp2 = _mm_shuffle_ps(q2.packed, q2.packed, _MM_SHUFFLE(0, 1, 2, 3));
	result.packed = _mm_add_ps(result.packed, _mm_mul_ps(temp1, temp2));

	temp1 = _mm_xor_ps(_mm_shuffle_ps(q1.packed, q1.packed, _MM_SHUFFLE(1, 1, 1, 1)), _mm_setr_ps(0.0f, 0.0f, -0.0f, -0.0f));
	temp2 = _mm_shuffle_ps(q2.packed, q2.packed, _MM_SHUFFLE(1, 0, 3, 2));
	result.packed = _mm_add_ps(result.packed, _mm_mul_ps(temp1, temp2));

	temp1 = _mm_xor_ps(_mm_shuffle_ps(q1.packed, q1.packed, _MM_SHUFFLE(2, 2, 2, 2)), _mm_setr_ps(-0.0f, 0.0f, 0.0f, -0.0f));
	temp2 = _mm_shuffle_ps(q2.packed, q2.packed, _MM_SHUFFLE(2, 3, 0, 1));
	result.packed = _mm_add_ps(result.packed, _mm_mul_ps(temp1, temp2));

	#else

	result.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
    result.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
    result.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
    result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;

	#endif

	return result;
}

QM_FUNC_ATTRIBS QMquaternion QM_FUNC_PREFIX(quaternion_scale)(QMquaternion q, float s)
{
	QMquaternion result;

	#if QM_USE_SSE

	__m128 scale = _mm_set1_ps(s);
	result.packed = _mm_mul_ps(q.packed, scale);

	#else

	result.x = q.x * s;
	result.y = q.y * s;
	result.z = q.z * s;
	result.w = q.w * s;

	#endif

	return result;
}

QM_FUNC_ATTRIBS float QM_FUNC_PREFIX(quaternion_dot)(QMquaternion q1, QMquaternion q2)
{
	float result;

	#if QM_USE_SSE

	__m128 r = _mm_mul_ps(q1.packed, q2.packed);
	r = _mm_hadd_ps(r, r);
	r = _mm_hadd_ps(r, r);
	_mm_store_ss(&result, r);

	#else

	result = q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;

	#endif

	return result;
}

QM_FUNC_ATTRIBS float QM_FUNC_PREFIX(quaternion_length)(QMquaternion q)
{
	float result;

	result = QM_SQRTF(QM_FUNC_PREFIX(quaternion_dot)(q, q));

	return result;
}

QM_FUNC_ATTRIBS QMquaternion QM_FUNC_PREFIX(quaternion_normalize)(QMquaternion q)
{
	QMquaternion result = {0};

	float len = QM_FUNC_PREFIX(quaternion_length)(q);
	if(len != 0.0f)
	{
		#if QM_USE_SSE

		__m128 scale = _mm_set1_ps(len);
		result.packed = _mm_div_ps(q.packed, scale);

		#else

		float invLen = 1.0f / len;

		result.x = q.x * invLen;
		result.y = q.y * invLen;
		result.z = q.z * invLen;
		result.w = q.w * invLen;

		#endif
	}

	return result;
}

QM_FUNC_ATTRIBS QMquaternion QM_FUNC_PREFIX(quaternion_conjugate)(QMquaternion q)
{
	QMquaternion result;

	result.x = -q.x;
	result.y = -q.y;
	result.z = -q.z;
	result.w = q.w;

	return result;
}

QM_FUNC_ATTRIBS QMquaternion QM_FUNC_PREFIX(quaternion_inv)(QMquaternion q)
{
	QMquaternion result;

	result.x = -q.x;
	result.y = -q.y;
	result.z = -q.z;
	result.w = q.w;

	#if QM_USE_SSE

	__m128 scale = _mm_set1_ps(QM_FUNC_PREFIX(quaternion_dot)(q, q));
	_mm_div_ps(result.packed, scale);

	#else

	float invLen2 = 1.0f / QM_FUNC_PREFIX(quaternion_dot)(q, q);

	result.x *= invLen2;
	result.y *= invLen2;
	result.z *= invLen2;
	result.w *= invLen2;

	#endif

	return result;
}

QM_FUNC_ATTRIBS QMquaternion QM_FUNC_PREFIX(quaternion_slerp)(QMquaternion q1, QMquaternion q2, float a)
{
	QMquaternion result;

	float cosine = QM_FUNC_PREFIX(quaternion_dot)(q1, q2);
	float angle = QM_ACOSF(cosine);

	float sine1 = QM_SINF((1.0f - a) * angle);
	float sine2 = QM_SINF(a * angle);
	float invSine = 1.0f / QM_SINF(angle);

	q1 = QM_FUNC_PREFIX(quaternion_scale)(q1, sine1);
	q2 = QM_FUNC_PREFIX(quaternion_scale)(q2, sine2);

	result = QM_FUNC_PREFIX(quaternion_add)(q1, q2);
	result = QM_FUNC_PREFIX(quaternion_scale)(result, invSine);

	return result;
}

QM_FUNC_ATTRIBS QMquaternion QM_FUNC_PREFIX(quaternion_from_axis_angle)(QMvec3 axis, float angle)
{
	QMquaternion result;

	float radians = QM_FUNC_PREFIX(deg_to_rad)(angle * 0.5f);
	axis = QM_FUNC_PREFIX(vec3_normalize)(axis);
	float sine = QM_SINF(radians);

	result.x = axis.x * sine;
	result.y = axis.y * sine;
	result.z = axis.z * sine;
	result.w = QM_COSF(radians);

	return result;
}

QM_FUNC_ATTRIBS QMquaternion QM_FUNC_PREFIX(quaternion_from_euler)(QMvec3 angles)
{
	QMquaternion result;

	QMvec3 radians;
	radians.x = QM_FUNC_PREFIX(deg_to_rad)(angles.x * 0.5f);
	radians.y = QM_FUNC_PREFIX(deg_to_rad)(angles.y * 0.5f);
	radians.z = QM_FUNC_PREFIX(deg_to_rad)(angles.z * 0.5f);

	float sinx = QM_SINF(radians.x);
	float cosx = QM_COSF(radians.x);
	float siny = QM_SINF(radians.y);
	float cosy = QM_COSF(radians.y);
	float sinz = QM_SINF(radians.z);
	float cosz = QM_COSF(radians.z);

	#if QM_USE_SSE

	__m128 packedx = _mm_setr_ps(sinx, cosx, cosx, cosx);
	__m128 packedy = _mm_setr_ps(cosy, siny, cosy, cosy);
	__m128 packedz = _mm_setr_ps(cosz, cosz, sinz, cosz);

	result.packed = _mm_mul_ps(_mm_mul_ps(packedx, packedy), packedz);

	packedx = _mm_shuffle_ps(packedx, packedx, _MM_SHUFFLE(0, 0, 0, 1));
	packedy = _mm_shuffle_ps(packedy, packedy, _MM_SHUFFLE(1, 1, 0, 1));
	packedz = _mm_shuffle_ps(packedz, packedz, _MM_SHUFFLE(2, 0, 2, 2));

	result.packed = _mm_addsub_ps(result.packed, _mm_mul_ps(_mm_mul_ps(packedx, packedy), packedz));

	#else

	result.x = sinx * cosy * cosz - cosx * siny * sinz;
	result.y = cosx * siny * cosz + sinx * cosy * sinz;
	result.z = cosx * cosy * sinz - sinx * siny * cosz;
	result.w = cosx * cosy * cosz + sinx * siny * sinz;

	#endif

	return result;
}

QM_FUNC_ATTRIBS QMmat4 QM_FUNC_PREFIX(quaternion_to_mat4)(QMquaternion q)
{
	QMmat4 result = QM_FUNC_PREFIX(mat4_identity)();

	float x2  = q.x + q.x;
    float y2  = q.y + q.y;
    float z2  = q.z + q.z;
    float xx2 = q.x * x2;
    float xy2 = q.x * y2;
    float xz2 = q.x * z2;
    float yy2 = q.y * y2;
    float yz2 = q.y * z2;
    float zz2 = q.z * z2;
    float sx2 = q.w * x2;
    float sy2 = q.w * y2;
    float sz2 = q.w * z2;

	result.m[0][0] = 1.0f - (yy2 + zz2);
	result.m[0][1] = xy2 - sz2;
	result.m[0][2] = xz2 + sy2;
	result.m[1][0] = xy2 + sz2;
	result.m[1][1] = 1.0f - (xx2 + zz2);
	result.m[1][2] = yz2 - sx2;
	result.m[2][0] = xz2 - sy2;
	result.m[2][1] = yz2 + sx2;
	result.m[2][2] = 1.0f - (xx2 + yy2);

	return result;
}

//----------------------------------------------------------------------//
//BOUNING BOX FUNCTIONS:

//loading:

QM_FUNC_ATTRIBS QMbbox2 QM_FUNC_PREFIX(bbox2_load)(const float* in)
{
	return (QMbbox2){ { in[0], in[1] }, { in[2], in[3] } };
}

QM_FUNC_ATTRIBS QMbbox3 QM_FUNC_PREFIX(bbox3_load)(const float* in)
{
	return (QMbbox3){ { in[0], in[1], in[2] }, { in[3], in[4], in[5] } };
}

//storing:

QM_FUNC_ATTRIBS void QM_FUNC_PREFIX(bbox2_store)(QMbbox2 b, float* out)
{
	out[0] = b.min.x;
	out[1] = b.min.y;
	out[2] = b.max.x;
	out[3] = b.max.y;
}

QM_FUNC_ATTRIBS void QM_FUNC_PREFIX(bbox3_store)(QMbbox3 b, float* out)
{
	out[0] = b.min.x;
	out[1] = b.min.y;
	out[2] = b.min.z;
	out[3] = b.max.x;
	out[4] = b.max.y;
	out[5] = b.max.z;
}

//initialized:

QM_FUNC_ATTRIBS QMbbox2 QM_FUNC_PREFIX(bbox2_initialized)()
{
	return (QMbbox2){ { INFINITY, INFINITY }, { -INFINITY, -INFINITY } };
}

QM_FUNC_ATTRIBS QMbbox3 QM_FUNC_PREFIX(bbox3_initialized)()
{
	return (QMbbox3){ { INFINITY, INFINITY, INFINITY }, { -INFINITY, -INFINITY, -INFINITY } };
}

//union:

QM_FUNC_ATTRIBS QMbbox2 QM_FUNC_PREFIX(bbox2_union)(QMbbox2 b1, QMbbox2 b2)
{
	QMbbox2 result;

	result.min = QM_FUNC_PREFIX(vec2_min)(b1.min, b2.min);
	result.max = QM_FUNC_PREFIX(vec2_max)(b1.max, b2.max);

	return result;
}

QM_FUNC_ATTRIBS QMbbox3 QM_FUNC_PREFIX(bbox3_union)(QMbbox3 b1, QMbbox3 b2)
{
	QMbbox3 result;

	result.min = QM_FUNC_PREFIX(vec3_min)(b1.min, b2.min);
	result.max = QM_FUNC_PREFIX(vec3_max)(b1.max, b2.max);

	return result;
}

QM_FUNC_ATTRIBS void QM_FUNC_PREFIX(bbox2_union_inplace)(QMbbox2* b1, QMbbox2 b2)
{
	b1->min = QM_FUNC_PREFIX(vec2_min)(b1->min, b2.min);
	b1->max = QM_FUNC_PREFIX(vec2_max)(b1->max, b2.max);
}

QM_FUNC_ATTRIBS void QM_FUNC_PREFIX(bbox3_union_inplace)(QMbbox3* b1, QMbbox3 b2)
{
	b1->min = QM_FUNC_PREFIX(vec3_min)(b1->min, b2.min);
	b1->max = QM_FUNC_PREFIX(vec3_max)(b1->max, b2.max);
}

//vector union:

QM_FUNC_ATTRIBS QMbbox2 QM_FUNC_PREFIX(bbox2_union_vec2)(QMbbox2 b, QMvec2 v)
{
	QMbbox2 result;

	result.min = QM_FUNC_PREFIX(vec2_min)(b.min, v);
	result.max = QM_FUNC_PREFIX(vec2_max)(b.max, v);

	return result;
}

QM_FUNC_ATTRIBS QMbbox3 QM_FUNC_PREFIX(bbox3_union_vec3)(QMbbox3 b, QMvec3 v)
{
	QMbbox3 result;

	result.min = QM_FUNC_PREFIX(vec3_min)(b.min, v);
	result.max = QM_FUNC_PREFIX(vec3_max)(b.max, v);

	return result;
}

QM_FUNC_ATTRIBS void QM_FUNC_PREFIX(bbox2_union_vec2_inplace)(QMbbox2* b, QMvec2 v)
{
	b->min = QM_FUNC_PREFIX(vec2_min)(b->min, v);
	b->max = QM_FUNC_PREFIX(vec2_max)(b->max, v);
}

QM_FUNC_ATTRIBS void QM_FUNC_PREFIX(bbox3_union_vec3_inplace)(QMbbox3* b, QMvec3 v)
{
	b->min = QM_FUNC_PREFIX(vec3_min)(b->min, v);
	b->max = QM_FUNC_PREFIX(vec3_max)(b->max, v);
}

//extent:

QM_FUNC_ATTRIBS QMvec2 QM_FUNC_PREFIX(bbox2_extent)(QMbbox2 b)
{
	return QM_FUNC_PREFIX(vec2_sub)(b.max, b.min);
}

QM_FUNC_ATTRIBS QMvec3 QM_FUNC_PREFIX(bbox3_extent)(QMbbox3 b)
{
	return QM_FUNC_PREFIX(vec3_sub)(b.max, b.min);
}

//centroid:

QM_FUNC_ATTRIBS QMvec2 QM_FUNC_PREFIX(bbox2_centroid)(QMbbox2 b)
{
	return QM_FUNC_PREFIX(vec2_scale)(QM_FUNC_PREFIX(vec2_add)(b.max, b.min), 0.5f);
}

QM_FUNC_ATTRIBS QMvec3 QM_FUNC_PREFIX(bbox3_centroid)(QMbbox3 b)
{
	return QM_FUNC_PREFIX(vec3_scale)(QM_FUNC_PREFIX(vec3_add)(b.max, b.min), 0.5f);
}

//offset:

QM_FUNC_ATTRIBS QMvec2 QM_FUNC_PREFIX(bbox2_offset)(QMbbox2 b, QMvec2 v)
{
	return QM_FUNC_PREFIX(vec2_div)(QM_FUNC_PREFIX(vec2_sub)(v, b.min), QM_FUNC_PREFIX(bbox2_extent)(b));
}

QM_FUNC_ATTRIBS QMvec3 QM_FUNC_PREFIX(bbox3_offset)(QMbbox3 b, QMvec3 v)
{
	return QM_FUNC_PREFIX(vec3_div)(QM_FUNC_PREFIX(vec3_sub)(v, b.min), QM_FUNC_PREFIX(bbox3_extent)(b));
}

//perimeter/sa:

QM_FUNC_ATTRIBS float QM_FUNC_PREFIX(bbox2_perimeter)(QMbbox2 b)
{
	float result = 0.0f;

	QMvec2 extent = QM_FUNC_PREFIX(bbox2_extent)(b);
	
	result += extent.x;
	result += extent.y;
	result *= 2.0f;

	return result;
}

QM_FUNC_ATTRIBS float QM_FUNC_PREFIX(bbox3_surface_area)(QMbbox3 b)
{
	float result = 0.0f;

	QMvec3 extent = QM_FUNC_PREFIX(bbox3_extent)(b);

	result += extent.x * extent.y;
	result += extent.x * extent.z;
	result += extent.y * extent.z;
	result *= 2.0f;

	return result;
}

#ifdef __cplusplus
} //extern "C"
#endif

#endif //QM_MATH_H
