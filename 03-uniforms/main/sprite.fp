varying mediump vec2 var_texcoord0;

uniform lowp vec4 tint;

void main()
{
    gl_FragColor = tint;
    gl_FragColor.a = 1.0;
}
