#version 100
precision highp float;

uniform sampler2D tex0;
uniform sampler2D tex1;

#define MODULATE 0
#define REPLACE 1
#define DECAL 2
#define ADD 3

uniform int use_multitexturing;
uniform int multitexture_mode;

varying vec2 texcoord0;
varying vec2 texcoord1;
varying vec4 color;

void main()
{
	if(!bool(use_multitexturing))
	{
		gl_FragColor = texture2D(tex0, texcoord0);
	}
	else
	{
		if(multitexture_mode == MODULATE)
		{
			gl_FragColor = texture2D(tex0, texcoord0) * texture2D(tex1, texcoord1);
		}
		else if(multitexture_mode == REPLACE)
		{
			gl_FragColor = texture2D(tex1, texcoord1);
		}
		else if(multitexture_mode == DECAL)
		{
			vec4 data0 = texture2D(tex0, texcoord0);
			vec4 data1 = texture2D(tex1, texcoord1);
			gl_FragColor = vec4(mix(data0.xyz, data1.xyz, data1.w), data0.w);
		}
		else //add
		{
			vec4 data0 = texture2D(tex0, texcoord0);
			vec4 data1 = texture2D(tex1, texcoord1);
			gl_FragColor = vec4(data0.xyz + data1.xyz, data0.w * data1.w);
		}
	}
}