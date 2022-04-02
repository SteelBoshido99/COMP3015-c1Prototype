#version 460

in vec3 Colour;

//Coordinaties for the models
in vec3 Position; //World Space
in vec3 Normal;
in vec2 TexCoord;

layout(location = 0) out vec4 FragColor;
layout(binding=0) uniform sampler2D Tex1;


 //light information struct
uniform struct LightInfo 
{
  vec4 Position;    // Light position in eye coords.
  vec3 La;         //Ambient light intensity
  vec3 L;         //Diffuse and Specular light intensity 
  vec3 Ld;       // Diffuse light intensity
} lights;       //Add an arrey for multiple lights


//material information struct
uniform struct MaterialInfo 
{
	vec3 Ka;        //Ambient reflectivity
	vec3 Kd;       // Diffuse reflectivity
	vec3 Ks;      //Specular Reflectivity
	float Shininess;
} Material;


vec3 blinnPhong( vec3 pos, vec3 n ) { //To add multiple lights do int light

       vec3 textureC = texture(Tex1, TexCoord).rgb;
       vec3 ambient = textureC * lights.La;
       //vec3 ambient = Material.Ka * lights[light].La;

     //calculate diffuse here
     vec3 s = normalize(vec3(lights.Position) - pos); //find out s vector
     float sDotN = max( dot(s,n), 0.0 );//calculate dot product between s & n
     vec3 diffuse = Material.Kd * sDotN;

    //calculate specular here
    vec3 spec = vec3(0.0);
    if (sDotN > 0.0)
    {
        vec3 v = normalize(-Position.xyz);
        vec3 h = normalize (v + s);
        spec = Material.Ks * pow(max(dot(h, n), 0.0), Material.Shininess);
    }
    return ambient + lights.L * (diffuse + spec);
}


void main()
{
    //FragColor += vec4(Colour, 1.0);
    FragColor = vec4(blinnPhong(Position, normalize(Normal)), 1);   
}
