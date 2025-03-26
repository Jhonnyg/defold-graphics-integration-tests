#version 450

layout (local_size_x = 8, local_size_y = 8, local_size_z = 8) in;

uniform uniforms
{
    vec4 color;
};

layout(rgba32f) uniform image3D texture_out;

void main()
{
    ivec3 storePos = ivec3(gl_GlobalInvocationID.xyz);  // Current voxel position
    ivec3 textureSize = ivec3(32,32,32);

    // Check bounds
    if (any(greaterThanEqual(storePos, textureSize))) {
        return;  // Avoid out-of-bounds access
    }

    vec3 uv = vec3(storePos) / vec3(textureSize - 1);

    vec4 valueOut = vec4(uv, 1.0);

    // Write noise value into red channel, leave others zero
    imageStore(texture_out, storePos, valueOut);
}
