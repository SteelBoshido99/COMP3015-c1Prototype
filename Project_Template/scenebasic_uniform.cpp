#include "scenebasic_uniform.h"
#include <sstream>
#include <iostream>
using std::cerr;
using std::endl;

#include <glm/gtc/matrix_transform.hpp>
using glm::vec3;
using glm::mat4;

//constructor for Racoon
SceneBasic_Uniform::SceneBasic_Uniform() : plane(10.0f, 10.0f, 100, 100) {
    bear = ObjMesh::load("../Project_Template/media/Bear.obj", true);
    tree = ObjMesh::load("../Project_Template/media/Tree.obj", true);
    fox = ObjMesh::load("../Project_Template/media/Fox.obj", true); 
    floor = ObjMesh::load("../Project_Template/media/Floor.obj", true);
}

void SceneBasic_Uniform::initScene()
{
    compile();
	glEnable(GL_DEPTH_TEST);
   
    //initialise the model matrix
    model = mat4(1.0f);

    //Setting the coords for the camera view
    view = glm::lookAt(vec3(5.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 5.0f, 0.0f));
    projection = mat4(1.0f);

    vec3 lightSource = vec3(3.0f, 2.0f, 0.0f);

    prog.setUniform("lights.La", 1.0f, 1.0f, 0.5f);
    prog.setUniform("lights.L", 1.0f, 1.0f, 0.9f);
    prog.setUniform("lights.Position", lightSource);

    //Bear Texture
    GLuint bear = Texture::loadTexture("../Project_Template/media/texture/Bear.png");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, bear);

    //Fox Texture
    GLuint foxTex = Texture::loadTexture("../Project_Template/media/texture/Fox.png");
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, foxTex);

    //Tree Texture
    GLuint treeTex = Texture::loadTexture("../Project_Template/media/texture/Tree.png");
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, treeTex);


    //Floor Texture
    GLuint floorTex = Texture::loadTexture("../Project_Template/media/texture/Floor.png");
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, floorTex);
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
	//update your angle here
}

void SceneBasic_Uniform::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Renddering the bear
    prog.setUniform("Material.Kd", 0.3f, 0.3f, 0.3f);
    prog.setUniform("Material.Ks", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Ka", 0.2f, 0.2f, 0.2f);
    prog.setUniform("Material.Shininess", 1.0f);

    model = mat4(1.0f);
    model = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f));
    model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, vec3(0.0f, 0.0f, -6.5f));
    setMatrices(); 
    bear->render();
    prog.setUniform("texRender", 0);


    //Rendering the Fox
    prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Shininess", 30.0f);


    model = mat4(1.0f);
    model = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f));
    model = glm::rotate(model, glm::radians(180.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, vec3(5.0f, 0.0f, -5.5f));
    setMatrices(); 
    fox->render();
    prog.setUniform("texRender", 1);


    //Rendering the tree
    prog.setUniform("Material.Kd", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Ks", 0.8f, 0.8f, 0.8f);
    prog.setUniform("Material.Ka", 0.6f, 0.6f, 0.6f);
    prog.setUniform("Material.Shininess", 50.0f);
    prog.setUniform("texRender", 2);


    //Tree 1
    model = mat4(1.0f);
    model = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, vec3(5.0f, 0.0f, -6.5f));
    setMatrices();  
    tree->render();


    //Tree2
    model = mat4(1.0f);
    model = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, vec3(-5.0f, 0.0f, -8.5f));
    setMatrices(); 
    tree->render();


    //Floor
    prog.setUniform("Material.Kd", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Ks", 0.8f, 0.8f, 0.8f);
    prog.setUniform("Material.Ka", 0.6f, 0.6f, 0.6f);
    prog.setUniform("Material.Shininess", 1.0f);
    prog.setUniform("texRender", 3);

    model = mat4(1.0f);
    model = glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 10.0f, 10.0f));
    model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, vec3(0.0f, -5.0f, 0.0f));
    setMatrices();
    floor->render();

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



