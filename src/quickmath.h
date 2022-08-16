#ifndef QM_MATH_H
#define QM_MATH_H

#ifdef __cplusplus
extern "C"
{
#endif

#define QM_INLINE static inline

#ifdef QM_NO_PREFIX
	#define QM_PREFIX(name) name
#else
	#define QM_PREFIX(name) QM##name  //struct prefix
#endif

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

//--------------------------------------------------------------------------------------------------------------------------------//
//STRUCT DEFINITIONS:

//a 2-dimensional vector of floats
typedef union
{
	float v[2];
	struct{ float x, y; };
	struct{ float w, h; };
} QM_PREFIX(vec2);

//a 3-dimensional vector of floats
typedef union
{
	float v[3];
	struct{ float x, y, z; };
	struct{ float w, h, d; };
	struct{ float r, g, b; };
} QM_PREFIX(vec3);

//a 4-dimensional vector of floats
typedef union
{
	float v[4];
	struct{ float x, y, z, w; };
	struct{ float r, g, b, a; };
} QM_PREFIX(vec4);

//-----------------------------//

typedef struct
{
	float m[2][2];
} QM_PREFIX(mat2);

typedef struct
{
	float m[3][3];
} QM_PREFIX(mat3);

typedef struct
{
	float m[4][4];
} QM_PREFIX(mat4);

//-----------------------------//

typedef union
{
	float q[4];
	struct{ float x, y, z, w; };
} QM_PREFIX(quaternion);

//--------------------------------------------------------------------------------------------------------------------------------//
//HELPER FUNCS:



//--------------------------------------------------------------------------------------------------------------------------------//
//VECTOR FUNCTIONS:

//addition:

QM_INLINE QM_PREFIX(vec2) QM_PREFIX(vec2_add)(QM_PREFIX(vec2) v1, QM_PREFIX(vec2) v2)
{
	QM_PREFIX(vec2) result = {v1.x + v2.x, v1.y + v2.y};
	return result;
}

QM_INLINE QM_PREFIX(vec3) QM_PREFIX(vec3_add)(QM_PREFIX(vec3) v1, QM_PREFIX(vec3) v2)
{
	QM_PREFIX(vec3) result = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
	return result;
}

QM_INLINE QM_PREFIX(vec4) QM_PREFIX(vec4_add)(QM_PREFIX(vec4) v1, QM_PREFIX(vec4) v2)
{
	QM_PREFIX(vec4) result = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w};
	return result;
}

//subtraction:

QM_INLINE QM_PREFIX(vec2) QM_PREFIX(vec2_sub)(QM_PREFIX(vec2) v1, QM_PREFIX(vec2) v2)
{
	QM_PREFIX(vec2) result = {v1.x - v2.x, v1.y - v2.y};
	return result;
}

QM_INLINE QM_PREFIX(vec3) QM_PREFIX(vec3_sub)(QM_PREFIX(vec3) v1, QM_PREFIX(vec3) v2)
{
	QM_PREFIX(vec3) result = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
	return result;
}

QM_INLINE QM_PREFIX(vec4) QM_PREFIX(vec4_sub)(QM_PREFIX(vec4) v1, QM_PREFIX(vec4) v2)
{
	QM_PREFIX(vec4) result = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w};
	return result;
}

//multiplication:

QM_INLINE QM_PREFIX(vec2) QM_PREFIX(vec2_mult)(QM_PREFIX(vec2) v1, QM_PREFIX(vec2) v2)
{
	QM_PREFIX(vec2) result = {v1.x * v2.x, v1.y * v2.y};
	return result;
}

QM_INLINE QM_PREFIX(vec3) QM_PREFIX(vec3_mult)(QM_PREFIX(vec3) v1, QM_PREFIX(vec3) v2)
{
	QM_PREFIX(vec3) result = {v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};
	return result;
}

QM_INLINE QM_PREFIX(vec4) QM_PREFIX(vec4_mult)(QM_PREFIX(vec4) v1, QM_PREFIX(vec4) v2)
{
	QM_PREFIX(vec4) result = {v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w};
	return result;
}

//scalar multiplication:



#ifdef __cplusplus
}
#endif

#endif //QM_MATH_H