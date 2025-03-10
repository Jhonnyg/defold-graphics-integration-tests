#version 450

layout (local_size_x = 8, local_size_y = 8, local_size_z = 8) in;

uniform uniforms
{
    vec4 color;
};

layout(rgba32f) uniform image3D texture_out;

// uniform sampler2D texture_in;

void main()
{
    ivec3 storePos = ivec3(gl_GlobalInvocationID.xyz);  // Current voxel position

    ivec3 textureSize = ivec3(32,32,32);

    // Check bounds
    if (any(greaterThanEqual(storePos, textureSize))) {
        return;  // Avoid out-of-bounds access
    }

    vec3 uv = vec3(storePos) / vec3(textureSize - 1);

    // Example: simple 3D hash-based noise
    // float noiseValue = hash(uv * 16.0);  // 16.0: scale factor for noise frequency

    vec4 valueOut = vec4(uv, 1.0);

    // Write noise value into red channel, leave others zero
    imageStore(texture_out, storePos, valueOut);
    
    /*
    ivec2 tex_coord   = ivec2(gl_GlobalInvocationID.xy);
    vec4 output_value = vec4(0.0, 0.0, 0.0, 1.0);
    vec2 tex_coord_uv = vec2(float(tex_coord.x)/(gl_NumWorkGroups.x), float(tex_coord.y)/(gl_NumWorkGroups.y));

    vec4 input_value = texture(texture_in, tex_coord_uv); //imageLoad(texture_in, tex_coord_uv);
    output_value.rgb = input_value.rgb;

    output_value.rg *= color.rg;
    output_value.b   = color.b;
    output_value.a   = 1.0;

    imageStore(texture_out, tex_coord, output_value);
    */
}
