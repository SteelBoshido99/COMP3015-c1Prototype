#include "scenebasic_uniform.h"
#include <sstream>
#include <iostream>
using std::cerr;
using std::endl;

#include <glm/gtc/matrix_transform.hpp>
using glm::vec3;
using glm::mat4;
using glm::vec4;
using glm::mat3;


//constructor for Racoon
SceneBasic_Uniform::SceneBasic_Uniform() : Rotation(0.0f), plane(10.0f, 10.0f, 100, 100) {
    bear = ObjMesh::load("../Project_Template/media/Bear.obj", true);
    tree = ObjMesh::load("../Project_Template/media/Tree.obj", true);
    fox = ObjMesh::load("../Project_Template/media/Fox.obj", true); 
    racoon = ObjMesh::load("../Project_Template/media/Racoon.obj", true);
}

void SceneBasic_Uniform::initScene()
{
    compile();
	glEnable(GL_DEPTH_TEST);
   
    //initialise the model matrix
    model = mat4(1.0f);
    projection = mat4(1.0f);

    //vec3 lightSource = vec3(3.0f, 2.0f, 0.0f);
    prog.setUniform("spotLights.L", vec3(0.7f));
    prog.setUniform("spotLights.La", vec3(0.2f));
    prog.setUniform("spotLights.Exponent", 5.0f);
    prog.setUniform("spotLights.Cutoff", glm::radians(2.0f));

   
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, bearTex);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, foxTex);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, treeTex);

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, floorTex);

    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, racoonTex);

  
}

void SceneBasic_Uniform::compile()
{
	try {
		prog.compileShader("shader/basic_uniform.vert");
		prog.compileShader("shader/basic_uniform.frag");
		prog.link();
		prog.use();
	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void SceneBasic_Uniform::update( float t )
{
    Rotation = t;
}

void SceneBasic_Uniform::render()
{
    view = glm::lookAt(vec3(7.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    view = glm::rotate(view, glm::radians(5.0f * Rotation), vec3(0.0f, 1.0f, 0.0f));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //---------Spotlight implementation---------// 
    vec4 lightPos = vec4(0.0f, 50.0f, 0.0f, 0.0f);
    prog.setUniform("spotLights.Position", lightPos);

    mat3 normalMatrix = mat3(vec3(view[0]), vec3(view[1]), vec3(view[2]));
    prog.setUniform("spotLights.Direction", normalMatrix * vec3(-lightPos));
    //---------Spotlight implementation---------//
    
    

    //-----------Renddering the bear-------------//
    prog.setUniform("Material.Kd", 0.3f, 0.3f, 0.3f);
    prog.setUniform("Material.Ks", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Ka", 0.2f, 0.2f, 0.2f);
    prog.setUniform("Material.Shininess", 1.0f);
    model = mat4(1.0f);
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
    model = glm::rotate(model, glm::radians(45.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, vec3(0.2f, 0.9f, -4.0f));

    prog.setUniform("Tex1", 0);

    setMatrices(); 
    bear->render();
    //-----------Renddering the bear-------------//



    //---------Rendering the Fox----------//
    prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Shininess", 30.0f);
    model = mat4(1.0f);
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
    model = glm::rotate(model, glm::radians(125.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, vec3(0.0f, 0.6f, -3.0f));

    prog.setUniform("Tex1", 1);
    setMatrices(); 
    fox->render();
    //---------Rendering the Fox----------//

    //---------Rendering the racoon---------//
    prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Shininess", 30.0f);
    model = mat4(1.0f);
    model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
    model = glm::rotate(model, glm::radians(-90.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, vec3(0.0f, 4.0f, -7.0f));

    prog.setUniform("Tex1", 4);
    setMatrices();
    racoon->render();
    //---------Rendering the racoon---------//
    

    //Rendering the tree
    prog.setUniform("Material.Kd", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Ks", 0.8f, 0.8f, 0.8f);
    prog.setUniform("Material.Ka", 0.6f, 0.6f, 0.6f);
    prog.setUniform("Material.Shininess", 50.0f);
   
    prog.setUniform("Tex1", 2);

    //Tree 1
    model = mat4(1.0f);
    model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
    model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, vec3(5.0f, 3.0f, 6.0f));
    setMatrices();  
    tree->render();

    //Tree2
    model = mat4(1.0f);
    model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
    model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, vec3(-5.0f, 3.0f, -5.5f));
    setMatrices(); 
    tree->render();

    //tree3
    model = mat4(1.0f);
    model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
    model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, vec3(-3.0f, 3.0f, 4.5f));
    setMatrices();
    tree->render();

    //---------Rendering the Plain--------//
    prog.setUniform("Material.Kd", 0.3f, 0.3f, 0.3f);
    prog.setUniform("Material.Ks", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Ka", 0.2f, 0.2f, 0.2f);
    prog.setUniform("Material.Shininess", 0.0f);
    model = mat4(1.0f);
    model = glm::translate(model, vec3(0.0f, 0.0f, 0.0f));
    prog.setUniform("Tex1", 3);
    setMatrices();
    plane.render();
    //---------Rendering the Plain--------//
}

void SceneBasic_Uniform::setMatrices()
{
    mat4 mv = view * model; //we create a model view matrix
    
    prog.setUniform("ModelViewMatrix", mv); //set the uniform for the model view matrix
    
    prog.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2]))); //we set the uniform for normal matrix
    
    prog.setUniform("MVP", projection * mv); //we set the model view matrix by multiplying the mv with the projection matrix
}

void SceneBasic_Uniform::resize(int w, int h)
{
    glViewport(0, 0, w, h);
    width = w;
    height = h;
    projection = glm::perspective(glm::radians(70.0f), (float)w / h, 0.3f, 100.0f);
}



