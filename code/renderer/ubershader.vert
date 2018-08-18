#version 100
precision highp float;

uniform mat4 projection;
uniform mat4 modelview;

attribute vec4 inVertex;
attribute vec2 inTexcoord0;
attribute vec2 inTexcoord1;
attribute vec4 inColor;

varying vec2 texcoord0;
varying vec2 texcoord1;
varying vec4 color;

void main()
{
	texcoord0 = inTexcoord0;
	texcoord1 = inTexcoord1;
	color = inColor;
	gl_Position = vec4(inVertex.xyz, 1.0) * modelview * projection;
}