// uniform sampler2D Texture2;
//uniform sampler2D CC_Texture1;
varying vec2 v_texCoord;
//varying vec4 v_position;
// varying vec2 v_texCoord2;
//uniform float x;
// varying vec4 v_color;
void main()
{
    // if(v_position.x<x)
    //     // discard;
    //     gl_FragColor = texture(CC_Texture1, v_texCoord);
    // else
    //     gl_FragColor = texture(CC_Texture0, v_texCoord);
	// gl_FragColor = mix(texture(CC_Texture0, v_texCoord), texture(CC_Texture1, v_texCoord),0.5);
	gl_FragColor = texture(CC_Texture0, v_texCoord);
	// gl_FragColor = v_color;
}