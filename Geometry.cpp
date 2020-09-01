//
//  Geometry.cpp
//  HW3
//
//  Created by Jiayue Chen on 10/30/18.
//  Copyright © 2018 Jiayue Chen. All rights reserved.
//

#include "Geometry.hpp"
#include <iostream>


Geometry::Geometry(const char *filepath){
     myobj = new OBJObject(filepath);
}

Geometry::~Geometry(){
    delete myobj;
}



void Geometry::draw(int Shaderprogram,glm::mat4 M){
    myobj -> toWorld = M;
//    for(int i = 0; i < 4;i++){
//        for(int j = 0; j < 4;j++){
//            std::cout<< myobj->modelview[i][j] << std::endl;
//        }
//    }
    
    myobj-> draw(Shaderprogram);
}



void Geometry::update(float rotatedir){
    
}
