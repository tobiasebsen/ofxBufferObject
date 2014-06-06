#version 120

uniform sampler2DRect tex;
uniform vec2 size;

void main()
{
	vec4 color = texture2DRect(tex, gl_TexCoord[0].xy);

    if(color.a > 0)
        gl_FragData[0] = vec4(color.rgb, 1.0);
    else
        gl_FragData[0] = vec4(0);

    gl_FragData[1] = vec4(gl_TexCoord[0].x/size.x, gl_TexCoord[0].y/size.y, color.a, 1.0);
}
