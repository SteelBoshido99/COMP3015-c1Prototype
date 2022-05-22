#ifndef SCENEBASIC_UNIFORM_H
#define SCENEBASIC_UNIFORM_H

#include "helper/scene.h"
#include <glad/glad.h>
#include "helper/glslprogram.h"
#include "helper/plane.h"
#include "helper/objmesh.h"
#include <glm/glm.hpp>
#include "helper/texture.h"



class SceneBasic_Uniform : public Scene
{
private:
    GLSLProgram prog;
    GLSLProgram vertexAnime;
    GLSLProgram edgyDect;
   
    Texture texRender;
    Plane plane;

    float time;

    std::unique_ptr<ObjMesh> bear;
    std::unique_ptr<ObjMesh> fox;
    std::unique_ptr<ObjMesh> racoon;
    std::unique_ptr<ObjMesh> ufo;


    //---Edge detection---//
    GLuint fsQuad, fboHandle, renderTex;

    float tPrev;
    float rotSpeed;
    float angle;

    void edgeSetUp();
    void setupFBO();
    void pass1();
    void pass2();
    //---Edge detection---//

    //---Vertex wave animation---//
    void waterWaves();
    float waveTime;
    //---Vertex wave animation---//


    //Bear Texture
    GLuint bearTex = Texture::loadTexture("../Project_Template/media/texture/Bear.png");
    //Fox Texture
    GLuint foxTex = Texture::loadTexture("../Project_Template/media/texture/Fox.png");
    //Floor texture
    GLuint floorTex = Texture::loadTexture("../Project_Template/media/texture/Floor.jpg");
    //Racoon texture
    GLuint racoonTex = Texture::loadTexture("../Project_Template/media/texture/Racoon.png");
    //UFO texture
    GLuint ufoTex = Texture::loadTexture("../Project_Template/media/texture/ufo.png");
    //Water Texture
    GLuint seaTex = Texture::loadTexture("../Project_Template/media/texture/waterTexture.jpg");

    void setMatrices(GLSLProgram& set);
   
   

    void compile();

public:
    SceneBasic_Uniform();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};

#endif // SCENEBASIC_UNIFORM_H
