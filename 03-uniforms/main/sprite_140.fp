in vec2 var_texcoord0;

out vec4 color;

uniform fs_uniforms
{
    vec4 tint;
};    

void main()
{
    color = tint;
    color.a = 1.0;
}
