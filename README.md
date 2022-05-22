# COMP3015-c1Prototype: Low-Poly Forest Original
## COMP3015-c1Prototype: Alien abduction branch https://github.com/SteelBoshido99/COMP3015-c1Prototype/tree/AdvancedShaders
---
<p>This is an OpenGl project that showcases custom shader using GLSL. The redered scene shows 3 animals and 3 trees on a plain, the models are low-poly meshes with a different texture for each of them. The final aim for this project, is to have a space ship abducting one of the animals as well as utilize multiple shaders to provide some visual variety. THe current shader that this scene is using is Blinn-Phong, it also has one spot light (This will be replaced with an alien beam in the final showcase). </p>

## Inspiration
---
<p> The whole style of the scene is inspired by my personal use of low-poly assests in other projects that I've developed. The minimalistic aesthetic that low-poly themes provide is really appealing to me, and so I wanted to demonstrate that with this initial scene. The polished version of this project (Future link to repo here) will have a spaceship abducting one of the animals in the scene. Overall, I want to make this scene fun and quirky through a minimal lense as to not overwhlem the viewr with highly detailed textures and models.</p> 

## The Code base
---
<p> Thw code base for the whole project is relatively easy to navigate through. scenebasic_uniform.h contains the classes that are used in scenebasic_uniform.cpp, THe textures are alos loaded in the header file, as well as the model meshes. The fragment shader holds the code calculations of the Blinn-phong method, which takes into account spotlight lighting to produce the scene. The information for the spotlight and materials are held in the uniform structs in the fragment shader. The vertex shader gets the coordinates of the renderd models and their coresponding textures. The main chunk of coding is found in the scenebasic_uniform.cpp of the project, this is where the model meshes are retrieved and rendered. The textures are also assigned to a texture array which is then set to the respective model. This is where the spotlight is also constructed.</p>

## Extra Information
---
<p> Visual Studio 2019 version 16.7.6 was used to develop this scene </p> 
<p> Operating System is Windows 10 Pro, and the build is 19043.1586</p>

## YouTube link
---
https://youtu.be/L7J9wiXCbws
 
## External Asset Resources
---
1. https://www.freepik.com/free-vector/seamless-textured-grass-natural-grass-pattern_11930799.htm#query=grass%20texture&position=3&from_view=keyword - Floor texture
2. https://www.cgtrader.com/free-3d-models/plant/other/forest-assets-low-poly-including-bonus-animal - Tree and texture
3. https://www.cgtrader.com/items/3452204/download-page - Fox and bear model and texture
4. https://www.cgtrader.com/items/2632923/download-page - Racoon model


![Screenshot 2022-04-04 045420](https://user-images.githubusercontent.com/55700855/161471211-e68534da-ee49-477f-96ce-f4c778f18656.jpg)
![Screenshot 2022-04-04 045444](https://user-images.githubusercontent.com/55700855/161471219-b67b5614-2c8c-49b0-93fe-9008783f1baf.jpg)
![Screenshot 2022-04-04 045508](https://user-images.githubusercontent.com/55700855/161471224-7068cd4d-b790-4ffc-9fd6-16c109e73a94.jpg)
