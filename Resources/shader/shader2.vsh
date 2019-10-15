// attribute vec2 a_texCoord;
attribute vec3 v_color;
attribute vec3 v_position;

// varying vec2 v_texCoord;
// varying vec4 v_position;
varying vec3 color;;
void main()
{	
	// vec4 ss = CC_MVPMatrix*vec4(a_position,1.0f);
	// gl_Position = ss;
    // v_texCoord = a_texCoord;
    gl_Position = vec4(v_position,1.0);
    color = v_color;
}