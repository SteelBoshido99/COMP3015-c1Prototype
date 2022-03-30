#version 460

//in variable that receives the diffuse calculation from the vertex shader
//in vec3 LightIntensity;
in vec3 Colour;
//in vec2 TexCoord;

//out variable, this typical for all fragment shaders
layout (location = 0) out vec4 FragColor;
//layout(binding=0) uniform sampler2D Tex1;

void main()
{
    //we pass LightInyensity to outr FragColor, notice the difference between vector types
    // vec3 and vec4 and how we solved the problem
    FragColor = vec4(Colour, 1.0);
    //vec3 texColor = texture(Tex1, TexCoord). rgb;
}
