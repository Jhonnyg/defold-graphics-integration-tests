#version 450

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

uniform uniforms
{
    vec4 color;
};

layout(rgba32f) uniform image2D texture_out;
uniform sampler2D texture_in;

void main()
{
    ivec2 tex_coord   = ivec2(gl_GlobalInvocationID.xy);
    vec4 output_value = vec4(0.0, 0.0, 0.0, 1.0);
    vec2 tex_coord_uv = vec2(float(tex_coord.x)/(gl_NumWorkGroups.x), float(tex_coord.y)/(gl_NumWorkGroups.y));

    vec4 input_value = texture(texture_in, tex_coord_uv); //imageLoad(texture_in, tex_coord_uv);
    output_value.rgb = input_value.rgb;

    output_value.rg *= color.rg;
    output_value.b   = color.b;
    output_value.a   = 1.0;

    imageStore(texture_out, tex_coord, output_value);
}
