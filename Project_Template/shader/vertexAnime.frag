#version 460

layout(location = 0) out vec4 FragColor;
layout(binding = 0) uniform sampler2D Tex1;

//Coordinaties for the models
in vec3 Position; //World Space
in vec3 Normal;
in vec2 TexCoord;

//Variable to change shader
uniform int shaderNum;

uniform struct LightInfo
{
 vec4 Position;   
  vec3 La;         
  vec3 L;   
} light;

//material information struct
uniform struct MaterialInfo 
{
	vec3 Ka;        //Ambient reflectivity
	vec3 Kd;       // Diffuse reflectivity
	vec3 Ks;      //Specular Reflectivity
	float Shininess;
} Material;




vec3 blinnPhong(vec3 position, vec3 n)
{
    vec3 textureC = texture(Tex1, TexCoord).rgb;

    //Calculate the overall Ambient using the light ambient value and the combined texture value, col
    vec3 ambient = light.La * Material.Ka * textureC;

	vec3 s = normalize(light.L -position);

    //Calculating the diffuse output
    float sDotN = max( dot(s,n), 0.0 );
    vec3 diffuse = Material.Kd * sDotN;

    //Calculating the specular output
    vec3 spec = vec3(0.0);
    if( sDotN > 0.0 )
    {
        vec3 v = normalize(-position.xyz);
        vec3 h = normalize(v + s);
        spec = Material.Ks * pow( max( dot(h,n), 0.0 ), Material.Shininess );
    }

    return ambient + light.L * (diffuse + spec);
}


void main()
{
    if(shaderNum == 0){
         FragColor = vec4(blinnPhong(Position, normalize(Normal)), 1);
    }
    
}
