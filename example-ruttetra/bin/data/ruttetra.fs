uniform sampler2DRect tex;
uniform vec2 size;
const vec4 lumcoeff = vec4(0.299,0.587,0.114,0.);
void main()
{
	vec4 color = texture2DRect(tex, gl_TexCoord[0].xy);
	float luma = dot(color, lumcoeff);
	gl_FragColor = vec4(gl_TexCoord[0].x / size.x, gl_TexCoord[0].y / size.y, luma, 1.0);
}
