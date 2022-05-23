# COMP3015-c1Prototype: Alien  Abduction
---
<p>This is an OpenGl project that showcases custom shader using GLSL. The rendered scene shows one animal being abducted by a UFO. Two executables are present and each show a different shadeer in action. The Blinn-Phong.exe shows a bear that is being abducted by a UFO, flying over a sea. The Edge.exe shows the same but with an edge detection shader applied. If you look into the sln file of the project you'll be able to change which shader and model is on display</p>

## Inspiration
---
<p> The whole style of the scene is inspired by my personal use of low-poly assests in other projects that I've developed. The minimalistic aesthetic that low-poly themes provide is really appealing to me, and so I wanted to demonstrate that with this initial scene (https://github.com/SteelBoshido99/COMP3015-c1Prototype). This version of the graphical project shows a bear being abducted by a UFO</p> 

## The Code base
---
<p> The code base for the whole project is relatively easy to navigate through. scenebasic_uniform.h contains the classes that are used in scenebasic_uniform.cpp, THe textures are alos loaded in the header file, as well as the model meshes. The fragment shader holds the code calculations of the Blinn-phong method, which takes into account spotlight lighting to produce the scene. In this version the spot-light shader is non-fuctional, which is due to a missed detail (will be amended in the futire) The information for the spotlight and materials are held in the uniform structs in the fragment shader. The vertex shader gets the coordinates of the renderd models and their coresponding textures. The main chunk of coding is found in the scenebasic_uniform.cpp of the project, this is where the model meshes are retrieved and rendered. There is now code to completely change the look of the scene, determining which shaders are in play and which one's are not(instuctions on how to change the scene will be below). This version of the project now uses a vertex-animation shader, in the form of a wave as well as an edge detection shader which also utilises the wave animation (Has to have its own edge wave shader)</p>

## Extra Information
---
<p> Visual Studio 2019 version 16.7.6 was used to develop this scene </p> 
<p> Operating System is Windows 10 Pro, and the build is 19043.1586</p>

## YouTube link
---

 
## External Asset Resources
---
1. https://www.dlf.pt/pngs/346549/ - Wave Texture
3. https://www.cgtrader.com/items/3452204/download-page - Fox and bear model and texture
4. https://www.cgtrader.com/items/2632923/download-page - Racoon model
5. https://www.cgtrader.com/free-3d-models/space/spaceship/free-flying-saucer - UFO model and Texture

## Edge Detection Shader
![image](https://user-images.githubusercontent.com/55700855/169723197-f009d24b-398e-42f5-8c61-2ac8c15bd7b3.png)
![image](https://user-images.githubusercontent.com/55700855/169723214-23865090-8f9e-4e67-8d19-23bd779d8208.png)

## Blinn-Phong Shader & Wave
![image](https://user-images.githubusercontent.com/55700855/169723248-bce47698-8a7c-4638-ba45-c75fb006cc2b.png)
![image](https://user-images.githubusercontent.com/55700855/169723266-5918aedd-75da-4c49-9747-19759539ccf7.png)

