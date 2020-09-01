//
//  Transform.hpp
//  HW3
//
//  Created by Jiayue Chen on 10/30/18.
//  Copyright © 2018 Jiayue Chen. All rights reserved.
//

#ifndef Transform_hpp
#define Transform_hpp
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
#include <list>

#endif /* Transform_hpp */



class Transform : public Node
{
private:
    
    
    
public:
    Transform();
    ~Transform();
    glm::mat4 MT;
    std::list<Node*> Nodelist;
    void addChild(Node* node);
    void removeChild(Node* node);
    void draw(GLint Shaderprogram ,glm::mat4 M);
    void update(float rotatedir);
    bool drawid = 0;
};
