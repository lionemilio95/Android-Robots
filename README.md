# Android-Robots
This is a OpenGL project based on C++ from UCSD CSE course. It utilizes scaling, culling and setting texture for models. I created a Android robot using some simple geometric graphic such as sphere, circle, rectangle and pillar. To make the android robot looks better, I attached a texture on it according to the shapes on each part.
<br>
<br>
After one robot is created, I used a 2D matrix to form a robots amry, which has 100 robots in total. 
![Image of Robots Army](https://github.com/lionemilio95/jiayue/blob/master/projectimg/hw3.png)

To reduce the burden of my computer's CPU, I also create a Cull mode, which would only show pretty limited amount of robots while not rendering the rest. However, the rest of the robots would be rendered if the camera is focusing on them. This could effectively reduce the occupancy of the CPU.
![Image of Culling](https://github.com/lionemilio95/jiayue/blob/master/projectimg/hw3cull.png)

Additionally, in order to adjust the distance between two robots, I also created a bounding sphere for each rotbot. In such way, I could visualize the actual distance and thus adjust it. 

![Image of Bounding Sphere](https://github.com/lionemilio95/jiayue/blob/master/projectimg/hw3bs.png)



 
