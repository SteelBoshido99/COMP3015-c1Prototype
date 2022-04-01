#ifndef SCENEBASIC_UNIFORM_H
#define SCENEBASIC_UNIFORM_H

#include "helper/scene.h"

#include <glad/glad.h>
#include "helper/glslprogram.h"


#include "helper/plane.h"
#include "helper/objmesh.h"
#include <glm/glm.hpp>


class SceneBasic_Uniform : public Scene
{
private:
    GLSLProgram prog;
    

    //Cube cube;

    Plane plane;

    std::unique_ptr<ObjMesh> bear;
    std::unique_ptr<ObjMesh> tree;
    std::unique_ptr<ObjMesh> fox;
    std::unique_ptr<ObjMesh> moon;

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
