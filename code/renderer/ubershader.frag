precision highp float;

uniform sampler2D tex0;
uniform sampler2D tex1;

#define NOMULTITEXTURE 0
#define MULTITEXTURE_MODULATE 1
#define MULTITEXTURE_REPLACE 2
#define MULTITEXTURE_DECAL 3
#define MULTITEXTURE_ADD 4

#define NOALPHATEST 0
#define ALPHATEST_GREATER 1
#define ALPHATEST_LESS 2
#define ALPHATEST_GREATEREQUAL 3

#ifndef MULTITEXTURING_MODE
#define MULTITEXTURING_MODE NOMULTITEXTURE
#endif

#ifndef ALPHATEST_MODE
#define ALPHATEST_MODE NOALPHATEST
#endif

#ifndef USEVERTEXCOLOR
#define USEVERTEXCOLOR 0
#endif

varying vec2 texcoord0;
varying vec2 texcoord1;
varying vec4 color;

void main()
{
	vec4 result = vec4(0.0);
	
#if MULTITEXTURING_MODE == NOMULTITEXTURE
	result = texture2D(tex0, texcoord0);
#elif MULTITEXTURING_MODE == MULTITEXTURE_MODULATE
	result = texture2D(tex0, texcoord0) * texture2D(tex1, texcoord1);
#elif MULTITEXTURING_MODE == MULTITEXTURE_REPLACE
	result = texture2D(tex1, texcoord1);
#elif MULTITEXTURING_MODE == MULTITEXTURE_DECAL
	vec4 data0 = texture2D(tex0, texcoord0);
	vec4 data1 = texture2D(tex1, texcoord1);
	result = vec4(mix(data0.xyz, data1.xyz, data1.w), data0.w);
#elif MULTITEXTURING_MODE == MULTITEXTURE_ADD
	vec4 data0 = texture2D(tex0, texcoord0);
	vec4 data1 = texture2D(tex1, texcoord1);
	result = vec4(data0.xyz + data1.xyz, data0.w * data1.w);
#endif
	
#if ALPHATEST_MODE == ALPHATEST_GREATER
	if(!(result.w > 0.0))
	{
		discard;
	}
#elif ALPHATEST_MODE == ALPHATEST_LESS
	if(!(result.w < 0.5))
	{
		discard;
	}
#elif ALPHATEST_MODE == ALPHATEST_GREATEREQUAL
	if(!(result.w >= 0.5))
	{
		discard;
	}
#endif
	
#if USEVERTEXCOLOR == 1
	result *= color/255.0;
#endif
	
	gl_FragColor = result;
}