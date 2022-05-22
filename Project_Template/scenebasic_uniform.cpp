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



//GUI Variables


//Change Variables
int modelNum = 2;
int shaderNum = 1;


//constructor for Racoon
SceneBasic_Uniform::SceneBasic_Uniform() : time(0.0f), plane(10.0f, 10.0f, 100, 100) {
    bear = ObjMesh::load("../Project_Template/media/Bear.obj", true);
    fox = ObjMesh::load("../Project_Template/media/Fox.obj", true);
    racoon = ObjMesh::load("../Project_Template/media/Racoon.obj", true);
    ufo = ObjMesh::load("../Project_Template/media/UFO.obj", true);
}

void SceneBasic_Uniform::initScene()
{
    compile();
	glEnable(GL_DEPTH_TEST);
   
    //initialise the model matrix
    model = mat4(1.0f);
    projection = mat4(1.0f);

    prog.use();
    //---------Spotlight implementation---------// 
        //Lighthing
        prog.setUniform("spotLights.L", vec3(0.7f));
        prog.setUniform("spotLights.La", vec3(0.2f));
        prog.setUniform("spotLights.Exponent", 5.0f);
        prog.setUniform("spotLights.Cutoff", glm::radians(2.0f));

        mat4 spotLightPos = glm::lookAt(vec3(1.0f, -0.1f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
        vec4 lightPos = vec4(0.0f, 50.0f, 1.0f, 0.0f);
        prog.setUniform("spotLights.Position", vec4(spotLightPos * lightPos));
        mat3 normalMatrix = mat3(vec3(spotLightPos[0]), vec3(spotLightPos[0]), vec3(spotLightPos[0]));
        prog.setUniform("spotLights.Direction", normalMatrix * vec3(-lightPos));
    //---------Spotlight implementation---------//

}

void SceneBasic_Uniform::compile()
{
	try {
		prog.compileShader("shader/basic_uniform.vert");
		prog.compileShader("shader/basic_uniform.frag");
        prog.link();

        vertexAnime.compileShader("shader/vertexAnime.frag");
        vertexAnime.compileShader("shader/vertexAnime.vert");
        vertexAnime.link();

		prog.use();
	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void SceneBasic_Uniform::update( float t )
{
    time = t;
    waveTime = t;
}

void SceneBasic_Uniform::render()
{
    //------Pseudo code of how this should flow------//
   /* if shader = x
    {
    Render shader
    Render UFO ship
        if model = x
        {
            Render fox || bear || racoon
        }
    }*/

    view = glm::lookAt(vec3(8.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    view = glm::rotate(view, glm::radians(5.0f * time), vec3(0.0f, 1.0f, 0.0f));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (shaderNum == 0) { //-----Blinn-Phong------//

        //Send Shader Index to Frag Shader
        prog.use();
        prog.setUniform("ShaderIndex", 0);

        //Lighthing
        prog.setUniform("light.L", vec3(0.5f));
        prog.setUniform("light.La", vec3(2.0f));
        prog.setUniform("light.Position", view * glm::vec4(0.0f, 1.2f, 0.0f + 1.0f, 1.0f));
             
        if (modelNum == 0) {

           
            //-----------Renddering the bear-------------//
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, bearTex);

            prog.setUniform("Material.Kd", 0.3f, 0.3f, 0.3f);
            prog.setUniform("Material.Ks", 0.5f, 0.5f, 0.5f);
            prog.setUniform("Material.Ka", 0.2f, 0.2f, 0.2f);
            prog.setUniform("Material.Shininess", 1.0f);
            model = mat4(1.0f);
            model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
            model = glm::rotate(model, glm::radians(45.0f), vec3(0.0f, 1.0f, 0.0f));
            model = glm::translate(model, vec3(0.0f, 0.9f, 0.0f));
            prog.setUniform("Tex1", 0);
            setMatrices(prog);
            bear->render();

        } if (modelNum == 1) {

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, foxTex);

            //---------Rendering the Fox----------//
            prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
            prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
            prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
            prog.setUniform("Material.Shininess", 30.0f);
            model = mat4(1.0f);
            model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
            model = glm::rotate(model, glm::radians(125.0f), vec3(0.0f, 1.0f, 0.0f));
            model = glm::translate(model, vec3(0.0f, 0.6f, -3.0f));

            prog.setUniform("Tex1", 0);
            setMatrices(prog);
            fox->render();
            //---------Rendering the Fox----------//

        } if (modelNum == 2) {


            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, racoonTex);

            //---------Rendering the racoon---------//
            prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
            prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
            prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
            prog.setUniform("Material.Shininess", 30.0f);
            model = mat4(1.0f);
            model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
            model = glm::rotate(model, glm::radians(-90.0f), vec3(0.0f, 1.0f, 0.0f));
            model = glm::translate(model, vec3(0.0f, 4.0f, -7.0f));

            prog.setUniform("Tex1", 0);
            setMatrices(prog);
            racoon->render();
            //---------Rendering the racoon---------//
        }

            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, ufoTex);

            //---Rendering a UFO---//
            prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
            prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
            prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
            prog.setUniform("Material.Shininess", 30.0f);
            model = mat4(1.0f);
            model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
            model = glm::rotate(model, glm::radians(-90.0f), vec3(0.0f, 1.0f, 0.0f));
            model = glm::translate(model, vec3(0.0f, 30.0f, 0.0f));

            prog.setUniform("Tex1", 1);
            setMatrices(prog);
            ufo->render();
            //---Rendering a UFO---//
         
            waterWaves(); //
    } 
    if (shaderNum == 1) {//-----Spotlight & Blinn-Phong-----//

        //Send Shader Index to Frag Shader
        prog.use();
        prog.setUniform("ShaderIndex", 1);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, ufoTex);


        //---Rendering a UFO---//
        prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
        prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
        prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
        prog.setUniform("Material.Shininess", 30.0f);
        model = mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
        model = glm::rotate(model, glm::radians(-90.0f), vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, vec3(0.0f, 30.0f, 0.0f));

        prog.setUniform("Tex1", 0);
        setMatrices(prog);
        ufo->render();
        //---Rendering a UFO---//

        if (modelNum == 0) {

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, bearTex);

            prog.setUniform("Material.Kd", 0.3f, 0.3f, 0.3f);
            prog.setUniform("Material.Ks", 0.5f, 0.5f, 0.5f);
            prog.setUniform("Material.Ka", 0.2f, 0.2f, 0.2f);
            prog.setUniform("Material.Shininess", 1.0f);
            model = mat4(1.0f);
            model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
            model = glm::rotate(model, glm::radians(45.0f), vec3(0.0f, 1.0f, 0.0f));
            model = glm::translate(model, vec3(0.0f, 0.9f, 0.0f));

            prog.setUniform("Tex1", 0);

            setMatrices(prog);
            bear->render();
            //-----------Renddering the bear-------------//

        } if (modelNum == 1) {

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, foxTex);

            //---------Rendering the Fox----------//
            prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
            prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
            prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
            prog.setUniform("Material.Shininess", 30.0f);
            model = mat4(1.0f);
            model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
            model = glm::rotate(model, glm::radians(125.0f), vec3(0.0f, 1.0f, 0.0f));
            model = glm::translate(model, vec3(0.0f, 0.6f, 0.0f));

            prog.setUniform("Tex1", 0);
            setMatrices(prog);
            fox->render();
            //---------Rendering the Fox----------//

        } if (modelNum == 2) {


            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, racoonTex);

            //---------Rendering the racoon---------//
            prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
            prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
            prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
            prog.setUniform("Material.Shininess", 30.0f);
            model = mat4(1.0f);
            model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
            model = glm::rotate(model, glm::radians(-90.0f), vec3(0.0f, 1.0f, 0.0f));
            model = glm::translate(model, vec3(0.0f, 4.0f, 0.0f));

            prog.setUniform("Tex1", 0);
            setMatrices(prog);
            racoon->render();
            //---------Rendering the racoon---------//
        }


        //glActiveTexture(GL_TEXTURE1);
        //glBindTexture(GL_TEXTURE_2D, ufoTex);

        ////---------Rendering the Plain--------//
        //prog.setUniform("Material.Kd", 0.3f, 0.3f, 0.3f);
        //prog.setUniform("Material.Ks", 0.5f, 0.5f, 0.5f);
        //prog.setUniform("Material.Ka", 0.2f, 0.2f, 0.2f);
        //prog.setUniform("Material.Shininess", 0.0f);
        //model = mat4(1.0f);
        //model = glm::translate(model, vec3(0.0f, 0.0f, 0.0f));
        //prog.setUniform("Tex1", 1);
        //setMatrices();
        //plane.render();
        ////---------Rendering the Plain--------//
    }
    if (shaderNum == 2) {//-----Edge Detection-----//

    }

    
}

void SceneBasic_Uniform::waterWaves() {
    vertexAnime.use();
    vertexAnime.setUniform("Time", waveTime);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, seaTex);
    
    vertexAnime.setUniform("light.L", vec3(1.0f));
    vertexAnime.setUniform("light.La", vec3(0.7f));
    vertexAnime.setUniform("light.Position", view * glm::vec4(0.0f, 1.2f, 0.0f + 1.0f, 1.0f));

    vertexAnime.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
    vertexAnime.setUniform("Material.Ks", 0.8f, 0.8f, 0.8f);
    vertexAnime.setUniform("Material.Ka", 0.2f, 0.5f, 0.9f);
    vertexAnime.setUniform("Material.Shininess", 10.0f);
    model = mat4(1.0f);
    model = glm::translate(model, vec3(0.0f, -1.0f, 0.0f));

    setMatrices(vertexAnime);
    plane.render();
}

void SceneBasic_Uniform::setMatrices(GLSLProgram& set)
{
    mat4 mv = view * model; //we create a model view matrix
    
    set.setUniform("ModelViewMatrix", mv); //set the uniform for the model view matrix
    
    set.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2]))); //we set the uniform for normal matrix
    
    set.setUniform("MVP", projection * mv); //we set the model view matrix by multiplying the mv with the projection matrix
}

void SceneBasic_Uniform::resize(int w, int h)
{
    glViewport(0, 0, w, h);
    width = w;
    height = h;
    projection = glm::perspective(glm::radians(60.0f), (float)w / h, 0.3f, 100.0f);
}



