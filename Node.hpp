//
//  Node.hpp
//  HW3
//
//  Created by Jiayue Chen on 10/30/18.
//  Copyright © 2018 Jiayue Chen. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h> // Remove this line in future projects
#else
#include <GL/glew.h>
#endif

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif


#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>



class Node
{
private:

    
    
public:

    virtual void draw (GLint Shaderprogram,glm::mat4 C) = 0;
    virtual void update(float rotatedir)=0;
    glm::mat4 MT;

    //glm::mat4 C = glm::mat4(1.0f);
    bool drawid = 1;
};
#endif /* Node_hpp */

