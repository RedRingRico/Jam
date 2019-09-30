#version 150
#extension GL_ARB_explicit_attrib_location : enable

uniform sampler2D u_Texture;

in vec2 f_TexCoord;
in vec3 f_Normal;
in vec3 f_WorldPosition;

layout ( location = 0 ) out vec4 o_WorldPosition;
layout ( location = 1 ) out vec4 o_Albedo;
layout ( location = 2 ) out vec4 o_Normal;

void main( )
{
	o_WorldPosition = vec4( f_WorldPosition, 1.0 );
	o_Albedo = texture( u_Texture, f_TexCoord );
	o_Normal = vec4( normalize( f_Normal ), 1.0 );
}

