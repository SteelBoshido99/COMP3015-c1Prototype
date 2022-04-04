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
   
    Texture texRender;
    Plane plane;

    float Rotation;

    std::unique_ptr<ObjMesh> bear;
    std::unique_ptr<ObjMesh> tree;
    std::unique_ptr<ObjMesh> fox;
    std::unique_ptr<ObjMesh> racoon;


    //Bear Texture
    GLuint bearTex = Texture::loadTexture("../Project_Template/media/texture/Bear.png");
    //Fox Texture
    GLuint foxTex = Texture::loadTexture("../Project_Template/media/texture/Fox.png");
    //Tree Texture
    GLuint treeTex = Texture::loadTexture("../Project_Template/media/texture/Tree.png");
    //Floor texture
    GLuint floorTex = Texture::loadTexture("../Project_Template/media/texture/Floor.jpg");
    //Racoon texture
    GLuint racoonTex = Texture::loadTexture("../Project_Template/media/texture/Racoon.png");

    void setMatrices();

    void compile();

public:
    SceneBasic_Uniform();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};

#endif // SCENEBASIC_UNIFORM_H
