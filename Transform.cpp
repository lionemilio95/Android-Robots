//
//  Transform.cpp
//  HW3
//
//  Created by Jiayue Chen on 10/30/18.
//  Copyright © 2018 Jiayue Chen. All rights reserved.
//

#include "Transform.hpp"
#include <iostream>


Transform::Transform(){
    MT = glm::mat4(1.0f);
}

void Transform::addChild(Node* node){
    Nodelist.push_back(node);
}

void Transform::removeChild(Node* node){
    for(auto it = Nodelist.begin();it != Nodelist.end();++it){
        if (*it == node){
            Nodelist.erase(it);
        }
    }
}

void Transform::draw(GLint Shaderprogram, glm::mat4 M){
    glm::mat4 M_new = M * MT;
//    for(int i = 0; i < 4;i++){
//        for(int j = 0; j < 4;j++){
//            std::cout<< M_new[i][j] << std::endl;
//        }
//    }
    for(Node* child : Nodelist){
        if(child->drawid ==1){
            child->draw(Shaderprogram,M_new);
        }
    }
}


Transform::~Transform(){
}




void Transform::update(float rotatedir){
    MT = glm::rotate(glm::mat4(1.0f), 0.01f, glm::vec3(rotatedir,0.0f,0.0f)) * MT;
    //std::cout<< MT[3][0] << "   " << MT[3][2] << " " <<std::endl;

}
