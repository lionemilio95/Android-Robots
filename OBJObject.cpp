#include "OBJObject.h"
#include "Window.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>   // include math functions, such as sin, cos, M_PI

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



OBJObject::OBJObject(const char *filepath) 
{

    
	toWorld = glm::mat4(1.0f);
	parse(filepath);
    int twidth = 512;
    int theight = 512;
    int nrChannels = 1;
    
    
    // for buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VBO2);
    glGenBuffers(1, &VBO3);
    glGenTextures(1, &TEXTUREID);
    glGenBuffers(1, &EBO);
    
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size()*sizeof(glm::vec3), &vertices_[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(GLfloat),(GLvoid*)0);
   
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    
    glBufferData(GL_ARRAY_BUFFER, normals_.size()*sizeof(glm::vec3), &normals_[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,3 * sizeof(GLfloat),(GLvoid*)0);
    
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glBufferData(GL_ARRAY_BUFFER, uvs_.size()*sizeof(glm::vec2), &uvs_[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,2 * sizeof(GLfloat),(GLvoid*)0);
    
    /////////////////TEXTURE///////////////////////
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TEXTUREID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    //unsigned char * image = loadPPM("jade01.ppm",twidth,theight);
    unsigned char * image = stbi_load("snow.jpeg", &twidth, &theight, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size()*sizeof(int), &indices_[0], GL_STATIC_DRAW);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    
    
    
}


OBJObject::~OBJObject()
{
    // Delete previously generated buffers. Note that forgetting to do this can waste GPU memory in a
    // large project! This could crash the graphics driver due to memory leaks, or slow down application performance!
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &VBO2);
    glDeleteBuffers(1, &VBO3);
    glDeleteBuffers(1, &EBO);
}



void OBJObject::parse(const char *filepath) 
{
	// Populate the face indices, vertices, and normals vectors with the OBJ Object data
    FILE* fp;     // file pointer
    float x,y,z;  // vertex coordinates
    char tempc;
    float r,g,b;  // vertex color
    float minx, miny,minz;
    float maxx, maxy, maxz;
    float centx, centy, centz;
    float scale1;
    int c1,c2;    // characters read from file
    unsigned int vertexind = 0;
    unsigned int normalind = 0;
    unsigned int uvsind = 0;
    unsigned int v1,v2,v3,vn1,vn2,vn3,vt1,vt2,vt3;
    
    
    
    
    fp = fopen(filepath,"rb");  // make the file name configurable so you can load other files
    
    // just in case the file can't be found or is corrupt
    if (fp==NULL) { std::cerr << "error loading file" << std::endl; exit(-1); }
    

    c1 = fgetc(fp);
    c2 = fgetc(fp);
    
    while (!feof(fp)) {
        

        
        if((c1=='v')&&(c2==' '))
            {
                fscanf(fp, "%f %f %f \n", &x, &y, &z);
                vertices.push_back(glm::vec3(x,y,z));
            }
    
        if((c1=='v')&&(c2=='n'))
        {
            fscanf(fp, "%f %f %f \n", &x, &y, &z);
            normals.push_back(glm::vec3(x,y,z));

        }
        
        if((c1=='v')&&(c2=='t'))
        {
            fscanf(fp, "%f %f \n", &x, &y);
            uvs.push_back(glm::vec2(x,y));
        }
        
        if((c1=='f')&&(c2==' '))
        {
            fscanf(fp, "%d %c %d %c %d %d %c %d %c %d %d %c %d %c %d \n",
                   &v1,&tempc,&vt1, &tempc,&vn1, &v2,&tempc,&vt2,&tempc,&vn2, &v3, &tempc,&vt3, &tempc, &vn3);
            vertex_indices.push_back(v1-1);
            vertex_indices.push_back(v2-1);
            vertex_indices.push_back(v3-1);

            normal_indices.push_back(vn1-1);
            normal_indices.push_back(vn2-1);
            normal_indices.push_back(vn3-1);
            
            uvs_indices.push_back(vt1-1);
            uvs_indices.push_back(vt2-1);
            uvs_indices.push_back(vt3-1);
            
            
        }
        
        else{
            fscanf(fp, "\n");
        }
        
        c1 = fgetc(fp);
        c2 = fgetc(fp);
        
    }
    
    
    for(unsigned int i = 0; i < normals.size();++i){
        normalscolor.push_back(glm::normalize(normals[i]));
        normalscolor[i].x = normalscolor[i].x * 0.5 + 0.5;
        normalscolor[i].y = normalscolor[i].y * 0.5 + 0.5;
        normalscolor[i].z = normalscolor[i].z * 0.5 + 0.5;
    }
    
    
    
    fclose(fp);   // make sure you don't forget to close the file when done
    
//    maxx = minx = vertices[0].x;
//    maxy = miny = vertices[0].y;
//    maxz = minz = vertices[0].z;
//
//    for(unsigned int i = 0; i < vertices.size()-1;++i){
//        maxx = std::max(maxx, vertices[i+1].x);
//        minx = std::min(minx, vertices[i+1].x);
//        maxy = std::max(maxy, vertices[i+1].y);
//        miny = std::min(miny, vertices[i+1].y);
//        maxz = std::max(maxz, vertices[i+1].z);
//        minz = std::min(minz, vertices[i+1].z);
//    }
//    centx = (maxx+minx)/2;
//    centy = (maxy+miny)/2;
//    centz = (maxz+minz)/2;
//    // x_scale = x *2 / (max_x - min_x)
//
//    scale1 = std::max((maxx-minx),(maxy-miny));
//    scale1 = std::max(scale1, (maxz-minz));
//
//
//    for(unsigned int i = 0; i < vertices.size();++i){
//        vertices[i].x = vertices[i].x -centx;
//        vertices[i].y = vertices[i].y -centy;
//        vertices[i].z = vertices[i].z -centz;
//        vertices[i].x = vertices[i].x * 2/scale1;
//        vertices[i].y = vertices[i].y * 2/scale1;
//        vertices[i].z = vertices[i].z * 2/scale1;
//    }
    
    
    
    
    //HW3 starts here
    for (unsigned i = 0; i < vertex_indices.size(); i++) {
        vertices_.push_back(vertices[vertex_indices[i]]);
        //std::cout<< vertices_[i].x << std::endl;
        normals_.push_back(normals[normal_indices[i]]);
        uvs_.push_back(uvs[uvs_indices[i]]);
        indices_.push_back(i);
    }
}





void OBJObject::draw(GLuint shaderProgram) 
{
    
    modelview = Window::V * toWorld;
    uProjection = glGetUniformLocation(shaderProgram, "projection");
    uModelview = glGetUniformLocation(shaderProgram, "modelview");
    uModel = glGetUniformLocation(shaderProgram, "model");
    uTexture = glGetUniformLocation(shaderProgram, "tex");
    
    glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
    glUniformMatrix4fv(uModelview, 1, GL_FALSE, &modelview[0][0]);
    glUniformMatrix4fv(uModel, 1, GL_FALSE, &toWorld[0][0]);
    glUniform1i(uTexture, 0);
   
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TEXTUREID);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (unsigned int)indices_.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}




void OBJObject::update(GLuint shaderProgram)
{

    
}

void OBJObject::spin(float deg)
{

}






void OBJObject::SettoWorld(float modmat){
    toWorld = glm::scale(glm::mat4(1.0f),glm::vec3(modmat,modmat,modmat)) * toWorld;
}


void OBJObject::SetroratetoWorld(float angle, float x, float y, float z){
    //std::cout<< angle << std::endl;
    toWorld = glm::rotate(glm::mat4(1.0f),angle,glm::vec3(x,y,z)) * toWorld;
}

void OBJObject::SetMovetoWorld(float x, float y, float z){
    toWorld = glm::translate(glm::mat4(1.0f), glm::vec3(x,y,z)) * toWorld;
}

void OBJObject::SetScaletoWorld(float x, float y, float z){
    toWorld = toWorld * glm::scale(glm::mat4(1.0f), glm::vec3(x,y,z));
}











unsigned char* OBJObject::loadPPM(const char* filename, int& width, int& height)
{
    const int BUFSIZE = 128;
    FILE* fp;
    unsigned int read;
    unsigned char* rawData;
    char buf[3][BUFSIZE];
    char* retval_fgets;
    size_t retval_sscanf;
    
    if ( (fp=fopen(filename, "rb")) == NULL)
    {
        std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
        width = 0;
        height = 0;
        return NULL;
    }
    
    // Read magic number:
    retval_fgets = fgets(buf[0], BUFSIZE, fp);
    
    // Read width and height:
    do
    {
        retval_fgets=fgets(buf[0], BUFSIZE, fp);
    } while (buf[0][0] == '#');
    retval_sscanf=sscanf(buf[0], "%s %s", buf[1], buf[2]);
    width  = atoi(buf[1]);
    height = atoi(buf[2]);
    
    // Read maxval:
    do
    {
        retval_fgets=fgets(buf[0], BUFSIZE, fp);
    } while (buf[0][0] == '#');
    
    // Read image data:
    rawData = new unsigned char[width * height * 3];
    read = fread(rawData, width * height * 3, 1, fp);
    fclose(fp);
    if (read != 1)
    {
        std::cerr << "error parsing ppm file, incomplete data" << std::endl;
        delete[] rawData;
        width = 0;
        height = 0;
        return NULL;
    }
    
    return rawData;
}

// load image file into texture object
void OBJObject::loadTexture()
{
    GLuint texture[1];     // storage for one texture
    int twidth, theight;   // texture width/height [pixels]
    unsigned char* tdata;  // texture pixel data
    
    // Load image file
    tdata = loadPPM("image.ppm", twidth, theight);
    if (tdata==NULL) return;
    
    // Create ID for texture
    glGenTextures(1, &texture[0]);
    
    // Set this texture to be the one we are working with
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    
    // Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);
    
    // Set bi-linear filtering for both minification and magnification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


