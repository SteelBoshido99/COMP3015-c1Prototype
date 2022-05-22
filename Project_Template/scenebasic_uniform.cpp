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



//---To render the bear use 0 || to render the fox use 1 || to render the racoon use 2---//
int modelNum = 0;

//---to use Blinn-Phong use 0 || to use edge use 2 || to use spotlight use 1(in progress)---//
int shaderNum = 2;


//Constructors for time and plane, also loads in the models
SceneBasic_Uniform::SceneBasic_Uniform() : time(0.0f), plane(10.0f, 10.0f, 100, 100){
    bear = ObjMesh::load("../Project_Template/media/Bear.obj", true);
    fox = ObjMesh::load("../Project_Template/media/Fox.obj", true);
    racoon = ObjMesh::load("../Project_Template/media/Racoon.obj", true);
    ufo = ObjMesh::load("../Project_Template/media/UFO.obj", true);
}

void SceneBasic_Uniform::initScene()
{
    compile();

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
   
    //initialise the model matrix
    model = mat4(1.0f);
    projection = mat4(1.0f);

    edgeSetUp();
    edgyDect.use();

}

void SceneBasic_Uniform::compile()
{
	try {
        
		prog.compileShader("shader/basic_uniform.vert");
		prog.compileShader("shader/basic_uniform.frag");
        prog.link();
        prog.use();

        vertexAnime.compileShader("shader/vertexAnime.frag");
        vertexAnime.compileShader("shader/vertexAnime.vert");
        vertexAnime.link();
        vertexAnime.use();

        edgyDect.compileShader("shader/edgyDect.frag");
        edgyDect.compileShader("shader/edgyDect.vert");
        edgyDect.link();
        edgyDect.use();
		

	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void SceneBasic_Uniform::update( float t )
{
    float deltaT = t - tPrev;
    if (tPrev == 0.0f)
        deltaT = 0.0f;
    tPrev = t;
    angle += rotSpeed * deltaT;
    if (angle > glm::two_pi<float>())
        angle -= glm::two_pi<float>();

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

    view = glm::lookAt(vec3(10.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    view = glm::rotate(view, glm::radians(10.0f * time), vec3(0.0f, 1.0f, 0.0f));

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

            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, ufoTex);

            //---Rendering a UFO---//
            prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
            prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
            prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
            prog.setUniform("Material.Shininess", 30.0f);
            model = mat4(1.0f);
            model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
            model = glm::rotate(model, glm::radians(-90.0f * time), vec3(0.0f, 1.0f, 0.0f));
            model = glm::translate(model, vec3(0.0f, 30.0f, 0.0f));

            prog.setUniform("Tex1", 1);
            setMatrices(prog);
            ufo->render();
            //---Rendering a UFO---//
         
            waterWaves(); //
    } 
    if (shaderNum == 1) {//-----Spotlight & Blinn-Phong-----//

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

        } 
        if (modelNum == 1) {

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

        } 
        if (modelNum == 2) {


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
    }
    if (shaderNum == 2) {//-----Edge Detection-----//
        
        edgyDect.use();
        
        pass1();
        glFlush();
        pass2();

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

//---------------------------------------------Edge Detection---------------------------------------------//
void SceneBasic_Uniform::edgeSetUp() {
     
    edgyDect.use();
    compile();
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    projection = mat4(1.0f);
    angle = glm::pi<float>() / 4.0f;

    setupFBO();
    // Array for full-screen quad
    GLfloat verts[] = {
    -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f
    };
    GLfloat tc[] = {
    0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
    };
    // Set up the buffers
    unsigned int handle[2];
    glGenBuffers(2, handle);

    glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
    glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(float), verts, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), tc, GL_STATIC_DRAW);

    // Set up the vertex array object
    glGenVertexArrays(1, &fsQuad);
    glBindVertexArray(fsQuad);

    glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0); // Vertex position

    glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
    glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2); // Texture coordinates

    glBindVertexArray(0);

    edgyDect.setUniform("edgeRange", 1.0f);
    edgyDect.setUniform("Light.L", vec3(1.0f));
    edgyDect.setUniform("Light.La", vec3(0.2f));
}

void SceneBasic_Uniform::setupFBO() //---populates buffers---//
{
    // Generate and bind the framebuffer
    glGenFramebuffers(1, &fboHandle);
    glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);

    // Create the texture object
    glGenTextures(1, &renderTex);
    glBindTexture(GL_TEXTURE_2D, renderTex);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

    // Bind the texture to the FBO
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
        renderTex, 0);

    // Create the depth buffer
    GLuint depthBuf;
    glGenRenderbuffers(1, &depthBuf);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuf);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);

    // Bind the depth buffer to the FBO
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
        GL_RENDERBUFFER, depthBuf);

    // Set the targets for the fragment output variables
    GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, drawBuffers);

    // Unbind the framebuffer, and revert to default framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SceneBasic_Uniform::pass1()
{
    edgyDect.setUniform("Pass", 1);
    glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    view = glm::lookAt(vec3(25.0f * cos(angle), 3.0f, 7.0f * sin(angle)), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    projection = glm::perspective(glm::radians(60.0f), (float)width / height, 0.3f, 100.0f);


    edgyDect.use();
    //---Rendering a UFO---//
    edgyDect.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
    edgyDect.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    edgyDect.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
    edgyDect.setUniform("Material.Shininess", 30.0f);
    model = mat4(1.0f);
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    model = glm::rotate(model, glm::radians(45.0f * time), vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, vec3(0.0f, 30.0f, 0.0f));

    edgyDect.setUniform("Tex1", 1);
    setMatrices(edgyDect);
    ufo->render();
    //---Rendering a UFO---//

    if (modelNum == 0) {

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, bearTex);
        edgyDect.use();
        edgyDect.setUniform("Material.Kd", 0.3f, 0.3f, 0.3f);
        edgyDect.setUniform("Material.Ks", 0.5f, 0.5f, 0.5f);
        edgyDect.setUniform("Material.Ka", 0.2f, 0.2f, 0.2f);
        edgyDect.setUniform("Material.Shininess", 1.0f);
        model = mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        model = glm::rotate(model, glm::radians(45.0f * time), vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, vec3(0.0f, 0.9f, 0.0f));

        edgyDect.setUniform("Tex1", 0);

        setMatrices(edgyDect);
        bear->render();
        //-----------Renddering the bear-------------//

    } 
    if (modelNum == 1) {

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, foxTex);
        edgyDect.use();
        //---------Rendering the Fox----------//
        edgyDect.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
        edgyDect.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
        edgyDect.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
        edgyDect.setUniform("Material.Shininess", 30.0f);
        model = mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        model = glm::rotate(model, glm::radians(125.0f * time), vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, vec3(0.0f, 0.6f, 0.0f));

        edgyDect.setUniform("Tex1", 0);
        setMatrices(edgyDect);
        fox->render();
        //---------Rendering the Fox----------//

    }
    if (modelNum == 2) {


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, racoonTex);
        edgyDect.use();
        //---------Rendering the racoon---------//
        edgyDect.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
        edgyDect.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
        edgyDect.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
        edgyDect.setUniform("Material.Shininess", 30.0f);
        model = mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
        model = glm::rotate(model, glm::radians(-90.0f * time), vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, vec3(0.0f, 4.0f, 0.0f));

        edgyDect.setUniform("Tex1", 0);
        setMatrices(edgyDect);
        racoon->render();
        //---------Rendering the racoon---------//
    }

    edgyDect.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
    edgyDect.setUniform("Material.Ks", 0.0f, 0.0f, 0.0f);
    edgyDect.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
    edgyDect.setUniform("Material.Shininess", 1.0f);
    model = mat4(1.0f);
    model = glm::translate(model, vec3(0.0f, -0.75f, 0.0f));
    setMatrices(edgyDect);
    plane.render();
}

void SceneBasic_Uniform::pass2()
{
    edgyDect.setUniform("Pass", 2);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, renderTex);

    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT);

    model = mat4(1.0f);
    view = mat4(1.0f);
    projection = mat4(1.0f);
    setMatrices(edgyDect);
    // Render the full-screen quad
    glBindVertexArray(fsQuad);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
//---------------------------------------------Edge Detection---------------------------------------------//







