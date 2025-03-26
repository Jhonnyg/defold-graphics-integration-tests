#version 140

in mediump vec2 var_texcoord0;

out vec4 out_fragColor;

uniform mediump sampler3D texture_sampler;

uniform fs_uniforms
{
    mediump vec4 depth;
};

void main()
{
    out_fragColor = texture(texture_sampler, vec3(var_texcoord0, depth.x));
}
