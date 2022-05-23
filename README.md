# COMP3015-c1Prototype: Alien  Abduction
---
<p>This is an OpenGl project that showcases custom shader using GLSL. The rendered scene shows one animal being abducted by a UFO. Two executables are present and each show a different shadeer in action. The Blinn-Phong.exe shows a bear that is being abducted by a UFO, flying over a sea. The Edge.exe shows the same but with an edge detection shader applied. If you look into the sln file of the project you'll be able to change which shader and model is on display</p>

## Inspiration
---
<p> The whole style of the scene is inspired by my personal use of low-poly assests in other projects that I've developed. The minimalistic aesthetic that low-poly themes provide is really appealing to me, and so I wanted to demonstrate that with this initial scene (https://github.com/SteelBoshido99/COMP3015-c1Prototype). This version of the graphical project shows a bear being abducted by a UFO</p> 

# The Code base
## Edge Detection
---
<p> This shader shows the boundries of an object. Using the edgyDect, frag and vert shader in the scenebasic_uniform.cpp it uses a two-pass execution which it first passes the image to a taxture, then applies the edge detection filter by reading from the rendered texture. The result is then sent to the view. The edgyWave frag and vert shader do this also. However, the difference is that it takes in a time value which is updated every frame, showing the wave moving with an edge detection filter. These shaders are done through custom methods which are enabled in the scenebasic_uniform.h file</p>

## Vertex-Animation: Wave
<p>Contained in it's own method, this converts vertecies from a surface, in this case a plane, to create a sine wave surface animation. using the tesselated quad a set of triagles is the used to create a flat surface on the x-z plane. The vertexAnime.vert then transforms the y coordinate by calculating each vertex against a time-baed sine function as well as generate a normal vector from the transformed vertex.</p>

## Extra Information
---
<p> Visual Studio 2019 version 16.7.6 was used to develop this scene </p> 
<p> Operating System is Windows 10 Pro, and the build is 19043.1586</p>

## YouTube link
---
https://youtu.be/ie4LUxzKt_g
 
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

