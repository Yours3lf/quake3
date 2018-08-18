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
//glUniform

#define GL_MODULATE                       0x2100
#define GL_ADD                            0x0104
#define GL_DECAL						0x2101

#define ALPHATEST_DISABLE 0
#define ALPHATEST_GREATER 1
#define ALPHATEST_LESS 2
#define ALPHATEST_GREATEREQUAL 3


extern int MODELVIEW_LOC;
extern int PROJECTION_LOC;
extern int USE_MULTITEXTURING_LOC;
extern int MULTITEXTURE_MODE_LOC;
extern int ALPHATEST_MODE_LOC;

static float identity[16] =
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
	float tx = (right + left) / (right - left);
	float ty = (top + bottom) / (top - bottom);
	float tz = (_far + _near) / (_far - _near);
	float mx[16] = {
		2.0f / (right - left), 0, 0, tx,
		0, 2.0f / (top - bottom), 0, ty,
		0, 0, -2.0f / (_far - _near), tz,
		0, 0, 0, 1
	};
	memcpy(in, mx, sizeof(float) * 16);
}

#endif