#ifndef OBJOBJECT_H
#define OBJOBJECT_H


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

class OBJObject
{
private:
std::vector<glm::vec3> vertices;
std::vector<glm::vec3> normals;
std::vector<glm::vec2> uvs;
std::vector<unsigned int> vertex_indices;
std::vector<unsigned int> normal_indices;
std::vector<unsigned int> uvs_indices;
std::vector<unsigned int> indices_;
std::vector<glm::vec3> vertices_;
std::vector<glm::vec3> normals_;
std::vector<glm::vec2> uvs_;
std::vector<glm::vec3> normalscolor;


public:

    ~OBJObject();
    
    glm::mat4 toWorld;

    OBJObject(const char* filepath); 

    
    
	void parse(const char* filepath);
	void draw(GLuint);
    void spin(float deg);
    void update(GLuint shaderProgram);
    void SettoWorld(float modmat);
    void SetroratetoWorld(float angle, float x, float y, float z);
    void SetMovetoWorld(float x, float y, float z);
    void SetScaletoWorld(float x, float y, float z);
    unsigned char* loadPPM(const char* filename, int& width, int& height);
    void loadTexture();
    glm::mat4 modelview;
    

    GLuint VBO, VAO, EBO, VBO2,VBO3,TEXTUREID;
    GLuint uProjection, uModelview, uModel, uTexture;



};

#endif
