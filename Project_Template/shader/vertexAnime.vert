#version 460

//in variables, this are in model coordinates
layout (location = 0) in vec3 VertexPosition; 
layout (location = 1) in vec3 VertexNormal; 
layout (location = 2) in vec2 VertexTexCoord;

//out vector needed for the fragment shader
out vec4 Position;
out vec3 Normal;
out vec2 TexCoord;

uniform float Time;

//wave parametres
uniform float waveFreq = 1.5;
uniform float waveVelocity = 0.5;
uniform float waveAmp = 0.6;

//uniforms for matrices required in the shader
uniform mat4 ModelViewMatrix;   //model view matrix
uniform mat3 NormalMatrix;		//normal matrix
uniform mat4 MVP;				//model view projection matrix


void main() 
{ 
    vec4 pos = vec4(VertexPosition,1.0);

    //translate verteces on y coordinates
    float u = waveFreq * pos.x - waveVelocity * Time;
    pos.y = waveAmp * sin(u);

    //Compute the normal Vector
    vec3 n = vec3(0.0);
    n.xy = normalize(vec2(cos( u ), 1.0));

    Position = ModelViewMatrix * pos;
    Normal = NormalMatrix * n;
    TexCoord = VertexTexCoord;

    //Assign the position using the MVP data passed in
    gl_Position = MVP * pos;
} 