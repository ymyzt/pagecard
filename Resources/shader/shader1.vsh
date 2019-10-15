// attribute vec2 a_texCoord;
attribute vec3 a_position;
// attribute vec2 v_texCoord;
 //attribute vec4 a_color;
attribute vec2 a_texCoord;

varying vec2 v_texCoord;
// varying vec4 v_position;
// varying vec2 v_texCoord2;
varying vec4 v_color;
void main()
{	
	// vec4 ss = CC_MVPMatrix*vec4(a_position,1.0f);
	// gl_Position = ss;
    // v_texCoord = a_texCoord;
    gl_Position = CC_PMatrix*vec4(a_position,1.0);//vec4(v_position,1.0);
    // gl_Position = vec4(v_position,1.0);
   v_texCoord = a_texCoord;
   // v_color = a_color;
}