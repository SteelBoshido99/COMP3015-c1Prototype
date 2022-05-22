#version 460

layout(location = 0) out vec4 FragColor;
layout(binding = 0) uniform sampler2D RenderTex;

//Coordinaties for the models
in vec3 Position; //World Space
in vec3 Normal;
in vec2 TexCoord;

//Variable to change shader
uniform int shaderNum;

uniform float edgeRange;
uniform int rendPass;
vec4 pass1();
vec4 pass2();

const vec3 lum = vec3(0.2126, 0.7152, 0.0722);

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
    vec3 textureC = texture(RenderTex, TexCoord).rgb;

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

float luminance( vec3 color )
{
 return dot(lum,color);
}

 vec4 pass1(){
        return vec4(blinnPhong(Position, normalize(Normal)),1.0);
    }

vec4 pass2()
{
 ivec2 pix = ivec2(gl_FragCoord.xy); //we grab a pixel to check if edge
//pick neighboutring pixels for convolution filter
//check lecture slides
 float s00 = luminance(texelFetchOffset(RenderTex, pix, 0, ivec2(-1,1)).rgb);
 float s10 = luminance(texelFetchOffset(RenderTex, pix, 0, ivec2(-1,0)).rgb);
 float s20 = luminance(texelFetchOffset(RenderTex, pix, 0, ivec2(-1,-1)).rgb);
 float s01 = luminance(texelFetchOffset(RenderTex, pix, 0, ivec2(0,1)).rgb);
 float s21 = luminance(texelFetchOffset(RenderTex, pix, 0, ivec2(0,-1)).rgb);
 float s02 = luminance(texelFetchOffset(RenderTex, pix, 0, ivec2(1,1)).rgb);
 float s12 = luminance(texelFetchOffset(RenderTex, pix, 0, ivec2(1,0)).rgb);
 float s22 = luminance(texelFetchOffset(RenderTex, pix, 0, ivec2(1,-1)).rgb);
 float sx = s00 + 2 * s10 + s20 - (s02 + 2 * s12 + s22);
 float sy = s00 + 2 * s01 + s02 - (s20 + 2 * s21 + s22);
 float g = sx * sx + sy * sy;
 if( g > edgeRange )
 return vec4(1.0); //edge
 else
 return vec4(0.0,0.0,0.0,1.0); //no edge
}





void main()
{
    if (rendPass == 1){
    FragColor = pass1();
    }
    if(rendPass == 2){
     FragColor = pass2();
     }


   


}
