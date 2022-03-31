#version 460

//in variables, this are in model coordinates
layout (location = 0) in vec3 VertexPosition; 
layout (location = 1) in vec3 VertexNormal;
//layout (location = 2) in vec2 VertexTexCoord;

//out vector needed for the fragment shader
out vec3 Colour;
out vec2 TexCoord;

 //light information struct
uniform struct LightInfo 
{
  vec4 Position; // Light position in eye coords.
  vec3 La; //Ambient light intensity
  vec3 L; //Diffuse and Specular light intensity 
  vec3 Ld;       // Diffuse light intensity
} lights[4];

//material information struct
uniform struct MaterialInfo 
{
	vec3 Ka; //Ambient reflectivity
	vec3 Kd; // Diffuse reflectivity
	vec3 Ks; //Specular Reflectivity
	float Shininess;
} Material;

//uniforms for matrices required in the shader
uniform mat4 ModelViewMatrix;   //model view matrix
uniform mat3 NormalMatrix;		//normal matrix
uniform mat4 MVP;				//model view projection matrix


//Calculation variables
vec4 pos;
vec3 diffuse;
vec3 camCoords;
 
 vec3 phongModel(int light, vec3 position, vec3 n)
{
    //calculate ambient here, to access each light La value use this:
        vec3 ambient = lights[light].La * Material.Ka;


     //calculate diffuse here
     vec3 s = normalize(vec3(lights[light].Position - pos)); //find out s vector
     float sDotN = max( dot(s,n), 0.0 );//calculate dot product between s & n
     vec3 diffuse = Material.Kd * sDotN;

    //calculate specular here
    vec3 spec = vec3(0.0);

    if (sDotN > 0.0)
    {
        vec3 v = normalize(-position.xyz);
        vec3 r = reflect(-s, n);

        spec = Material.Ks * pow(max(dot(r, v), 0.0),
            Material.Shininess);
    }
    return ambient + lights[light].L * (diffuse + spec);
}



void main() 
{ 
  //transfrom normal from model coordinates to view coordinates
  vec3 n = normalize( NormalMatrix * VertexNormal);

  //transform vertex position from model coordinates to view coordinates
  pos = ModelViewMatrix * vec4(VertexPosition,1.0);

  vec4 position = ModelViewMatrix * vec4(VertexPosition, 1.0f);

  //Light equation
  Colour = vec3(0.0);
    for( int i = 0; i < 3; i++ ){
         Colour += phongModel( i, camCoords, n );
    }
    
  gl_Position = MVP * vec4(VertexPosition,1.0); 
} 