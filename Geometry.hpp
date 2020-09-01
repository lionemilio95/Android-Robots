//
//  Geometry.hpp
//  HW3
//
//  Created by Jiayue Chen on 10/30/18.
//  Copyright © 2018 Jiayue Chen. All rights reserved.
//

#ifndef Geometry_hpp
#define Geometry_hpp

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
#include "Node.hpp"
#include "OBJObject.h"
#include <list>

#endif /* Geometry_hpp */


class Geometry : public Node
{
private:
    
    
    
public:
    Geometry(const char *filepath);
    ~Geometry();
    glm::vec4 MT;
    void draw(GLint Shaderprogram, glm::mat4 M);
    OBJObject * myobj;
    void update(float rotatedir);
    bool drawid = 1;
    
    
};


