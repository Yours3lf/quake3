#version 100
precision highp float;

uniform sampler2D tex0;
uniform sampler2D tex1;

#define MODULATE 0
#define REPLACE 1
#define DECAL 2
#define ADD 3

#define ALPHATEST_DISABLE 0
#define ALPHATEST_GREATER 1
#define ALPHATEST_LESS 2
#define ALPHATEST_GREATEREQUAL 3

uniform int use_multitexturing;
uniform int multitexture_mode;
uniform int alphatest_mode;

varying vec2 texcoord0;
varying vec2 texcoord1;
varying vec4 color;

void main()
{
	vec4 result = vec4(0.0);
	
	if(!bool(use_multitexturing))
	{
		result = texture2D(tex0, texcoord0);
	}
	else
	{
		if(multitexture_mode == MODULATE)
		{
			result = texture2D(tex0, texcoord0) * texture2D(tex1, texcoord1);
		}
		else if(multitexture_mode == REPLACE)
		{
			result = texture2D(tex1, texcoord1);
		}
		else if(multitexture_mode == DECAL)
		{
			vec4 data0 = texture2D(tex0, texcoord0);
			vec4 data1 = texture2D(tex1, texcoord1);
			result = vec4(mix(data0.xyz, data1.xyz, data1.w), data0.w);
		}
		else //add
		{
			vec4 data0 = texture2D(tex0, texcoord0);
			vec4 data1 = texture2D(tex1, texcoord1);
			result = vec4(data0.xyz + data1.xyz, data0.w * data1.w);
		}
	}
	
	if(alphatest_mode == ALPHATEST_GREATER)
	{
		if(!(result.w > 0.0))
		{
			discard;
		}
	}
	else if(alphatest_mode == ALPHATEST_LESS)
	{
		if(!(result.w < 0.5))
		{
			discard;
		}
	}
	else if(alphatest_mode == ALPHATEST_GREATEREQUAL)
	{
		if(!(result.w >= 0.5))
		{
			discard;
		}
	}
	
	gl_FragColor = result;
}