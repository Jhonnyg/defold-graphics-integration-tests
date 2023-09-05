
uniform lowp samplerCube tex_skybox;
uniform mediump vec4 camera_pos;

varying mediump vec3 var_normal;
varying mediump vec3 var_position;

void main()
{
    vec3 refl_dir    = normalize(var_position - camera_pos.xyz);
    vec4 refl_sample = textureCube(tex_skybox, refl_dir);
    gl_FragColor = vec4(refl_sample.rgb, 1.0);
}
