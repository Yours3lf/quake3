#ifndef QGL_CUSTOM_H
#define QGL_CUSTOM_H

#define qglUseProgram glUseProgram
#define qglCompileShader glCompileShader
#define qglCreateProgram glCreateProgram
#define qglCreateShader glCreateShader
#define qglAttachShader glAttachShader
#define qglShaderSource glShaderSource
#define qglLinkProgram glLinkProgram 
#define qglEnableVertexAttribArray glEnableVertexAttribArray
#define	qglVertexAttribPointer glVertexAttribPointer
#define qglUniformMatrix4fv glUniformMatrix4fv
#define qglGetUniformLocation glGetUniformLocation
#define qglUniform1i glUniform1i
#define qglGetUniformfv	glGetUniformfv
//glUniform

#define GL_MODULATE                       0x2100
#define GL_ADD                            0x0104
#define GL_DECAL						0x2101

#define NOMULTITEXTURE 0
#define MULTITEXTURE_MODULATE 1
#define MULTITEXTURE_REPLACE 2
#define MULTITEXTURE_DECAL 3
#define MULTITEXTURE_ADD 4

#define NOALPHATEST 0
#define ALPHATEST_GREATER 1
#define ALPHATEST_LESS 2
#define ALPHATEST_GREATEREQUAL 3

extern float UNIFORM_MODELVIEW[16];
extern float UNIFORM_PROJECTION[16];
extern float UNIFORM_MVP[16];
extern int MULTITEXTURING_MODE;
extern int ALPHATEST_MODE;
extern int USE_VERTEXCOLOR;
extern int MVP_LOC;
extern GLuint PROGRAMS[5][4][2];

static float IDENTITY[16] =
{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

static void getOrtho(float* in, 
	float left,
	float right,
	float bottom,
	float top,
	float _near,
	float _far)
{
	float tx = -(right + left) / (right - left);
	float ty = -(top + bottom) / (top - bottom);
	float tz = -(_far + _near) / (_far - _near);
	float mx[16] = {
		2.0f / (right - left), 0, 0, 0,
		0, 2.0f / (top - bottom), 0, 0,
		0, 0, -2.0f / (_far - _near), 0,
		tx, ty, tz, 1
	};
	memcpy(in, mx, sizeof(float) * 16);
}

static void setModelview(float* mx)
{
	memcpy(UNIFORM_MODELVIEW, mx, sizeof(float) * 16);
}

static void getModelview(float* mx)
{
	memcpy(mx, UNIFORM_MODELVIEW, sizeof(float) * 16);
}

static void setProjection(float* mx)
{
	memcpy(UNIFORM_PROJECTION, mx, sizeof(float) * 16);
}

static void getProjection(float* mx)
{
	memcpy(mx, UNIFORM_PROJECTION, sizeof(float) * 16);
}

#define O(y,x) (y + (x<<2))
static inline void Matrix4x4MultiplyBy4x4(float *src1, float *src2, float *dest)
{
	*(dest + O(0, 0)) = (*(src1 + O(0, 0)) * *(src2 + O(0, 0))) + (*(src1 + O(0, 1)) * *(src2 + O(1, 0))) + (*(src1 + O(0, 2)) * *(src2 + O(2, 0))) + (*(src1 + O(0, 3)) * *(src2 + O(3, 0)));
	*(dest + O(0, 1)) = (*(src1 + O(0, 0)) * *(src2 + O(0, 1))) + (*(src1 + O(0, 1)) * *(src2 + O(1, 1))) + (*(src1 + O(0, 2)) * *(src2 + O(2, 1))) + (*(src1 + O(0, 3)) * *(src2 + O(3, 1)));
	*(dest + O(0, 2)) = (*(src1 + O(0, 0)) * *(src2 + O(0, 2))) + (*(src1 + O(0, 1)) * *(src2 + O(1, 2))) + (*(src1 + O(0, 2)) * *(src2 + O(2, 2))) + (*(src1 + O(0, 3)) * *(src2 + O(3, 2)));
	*(dest + O(0, 3)) = (*(src1 + O(0, 0)) * *(src2 + O(0, 3))) + (*(src1 + O(0, 1)) * *(src2 + O(1, 3))) + (*(src1 + O(0, 2)) * *(src2 + O(2, 3))) + (*(src1 + O(0, 3)) * *(src2 + O(3, 3)));
	*(dest + O(1, 0)) = (*(src1 + O(1, 0)) * *(src2 + O(0, 0))) + (*(src1 + O(1, 1)) * *(src2 + O(1, 0))) + (*(src1 + O(1, 2)) * *(src2 + O(2, 0))) + (*(src1 + O(1, 3)) * *(src2 + O(3, 0)));
	*(dest + O(1, 1)) = (*(src1 + O(1, 0)) * *(src2 + O(0, 1))) + (*(src1 + O(1, 1)) * *(src2 + O(1, 1))) + (*(src1 + O(1, 2)) * *(src2 + O(2, 1))) + (*(src1 + O(1, 3)) * *(src2 + O(3, 1)));
	*(dest + O(1, 2)) = (*(src1 + O(1, 0)) * *(src2 + O(0, 2))) + (*(src1 + O(1, 1)) * *(src2 + O(1, 2))) + (*(src1 + O(1, 2)) * *(src2 + O(2, 2))) + (*(src1 + O(1, 3)) * *(src2 + O(3, 2)));
	*(dest + O(1, 3)) = (*(src1 + O(1, 0)) * *(src2 + O(0, 3))) + (*(src1 + O(1, 1)) * *(src2 + O(1, 3))) + (*(src1 + O(1, 2)) * *(src2 + O(2, 3))) + (*(src1 + O(1, 3)) * *(src2 + O(3, 3)));
	*(dest + O(2, 0)) = (*(src1 + O(2, 0)) * *(src2 + O(0, 0))) + (*(src1 + O(2, 1)) * *(src2 + O(1, 0))) + (*(src1 + O(2, 2)) * *(src2 + O(2, 0))) + (*(src1 + O(2, 3)) * *(src2 + O(3, 0)));
	*(dest + O(2, 1)) = (*(src1 + O(2, 0)) * *(src2 + O(0, 1))) + (*(src1 + O(2, 1)) * *(src2 + O(1, 1))) + (*(src1 + O(2, 2)) * *(src2 + O(2, 1))) + (*(src1 + O(2, 3)) * *(src2 + O(3, 1)));
	*(dest + O(2, 2)) = (*(src1 + O(2, 0)) * *(src2 + O(0, 2))) + (*(src1 + O(2, 1)) * *(src2 + O(1, 2))) + (*(src1 + O(2, 2)) * *(src2 + O(2, 2))) + (*(src1 + O(2, 3)) * *(src2 + O(3, 2)));
	*(dest + O(2, 3)) = (*(src1 + O(2, 0)) * *(src2 + O(0, 3))) + (*(src1 + O(2, 1)) * *(src2 + O(1, 3))) + (*(src1 + O(2, 2)) * *(src2 + O(2, 3))) + (*(src1 + O(2, 3)) * *(src2 + O(3, 3)));
	*(dest + O(3, 0)) = (*(src1 + O(3, 0)) * *(src2 + O(0, 0))) + (*(src1 + O(3, 1)) * *(src2 + O(1, 0))) + (*(src1 + O(3, 2)) * *(src2 + O(2, 0))) + (*(src1 + O(3, 3)) * *(src2 + O(3, 0)));
	*(dest + O(3, 1)) = (*(src1 + O(3, 0)) * *(src2 + O(0, 1))) + (*(src1 + O(3, 1)) * *(src2 + O(1, 1))) + (*(src1 + O(3, 2)) * *(src2 + O(2, 1))) + (*(src1 + O(3, 3)) * *(src2 + O(3, 1)));
	*(dest + O(3, 2)) = (*(src1 + O(3, 0)) * *(src2 + O(0, 2))) + (*(src1 + O(3, 1)) * *(src2 + O(1, 2))) + (*(src1 + O(3, 2)) * *(src2 + O(2, 2))) + (*(src1 + O(3, 3)) * *(src2 + O(3, 2)));
	*(dest + O(3, 3)) = (*(src1 + O(3, 0)) * *(src2 + O(0, 3))) + (*(src1 + O(3, 1)) * *(src2 + O(1, 3))) + (*(src1 + O(3, 2)) * *(src2 + O(2, 3))) + (*(src1 + O(3, 3)) * *(src2 + O(3, 3)));
};

static void getMVP(float* mvp)
{
	Matrix4x4MultiplyBy4x4(UNIFORM_PROJECTION, UNIFORM_MODELVIEW, mvp);
}

#endif