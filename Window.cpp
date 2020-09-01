#include "Window.h"
#include "OBJObject.h"
#include "Geometry.hpp"
#include "Transform.hpp"


const char* window_title = "GLFW Starter Project";
Cube * cube;
OBJObject * Body;
Geometry * Torso;
Geometry * Head;
Geometry * LArm;
Geometry * RArm;
Geometry * Lleg;
Geometry * Rleg;
Geometry * Leye;
Geometry * Reye;
Geometry * Sphere;
Transform * Robothead;
Transform * Robotbody;
Transform * Robotbodyhead;
Transform * RobotLarm;
Transform * RobotRarm;
Transform * Robotarms;
Transform * RobotLleg;
Transform * RobotRleg;
Transform * Robotlegs;
Transform * RobotLeye;
Transform * RobotReye;
Transform * Roboteyes;
Transform * Robot;
Transform * Army;
Transform * ArmySphere;
Transform * Spheretrans;
Transform * Quad1;
Transform * Quad2;
Transform * Quad3;
Transform * Quad4;
Transform * RobotEC;
Transform * ArmyEC;
Transform * SphereEC;

int count;
int num;
int numdis;
int clickid = 0;
int clicked = 0;
int spherebool = 0;
int Debug = 1;
float NormalR = 3.5f;
float ECR = 30.62f;
int ECCull = 0;
int numEC;
double curxpos, curypos;
glm::vec3 lastvec, curvec,direction;
float rotangle;
GLint shaderProgram;
glm::mat4 torsomatrix  = glm::mat4(1.0f);
glm::mat4 bodyheadmatrix  = glm::mat4(1.0f);
glm::mat4 larmmatrix = glm::mat4(1.0f);
glm::mat4 rarmmatrix = glm::mat4(1.0f);
glm::mat4 llegmatrix = glm::mat4(1.0f);
glm::mat4 rlegmatrix = glm::mat4(1.0f);
glm::mat4 leyematrix = glm::mat4(1.0f);
glm::mat4 reyematrix = glm::mat4(1.0f);
glm::mat4 spherematrix = glm::mat4(1.0f);
glm::mat4 sphereECmatrix = glm::mat4(1.0f);









// On some systems you need to change this to the absolute path
#define VERTEX_SHADER_PATH "shader.vert"
#define FRAGMENT_SHADER_PATH "shader.frag"

// Default camera parameters
glm::vec3 cam_pos(25.0f, 10.0f, 70.0f);		// e  | Position of camera
glm::vec3 cam_look_at(0.0f, 0.0f, 0.0f);	// d  | This is where the camera looks at
glm::vec3 cam_up(0.0f, 1.0f, 0.0f);			// up | What orientation "up" is

glm::vec3 cam_pos_ec(25.0f, 10.0f, 70.0f);        // e  | Position of camera
glm::vec3 cam_look_at_ec(0.0f, 0.0f, 0.0f);    // d  | This is where the camera looks at
glm::vec3 cam_up_ec(0.0f, 1.0f, 0.0f);            // up | What orientation "up" is


int Window::width;
int Window::height;

int windowwidth;
int windowheight;

glm::mat4 Window::P;
glm::mat4 Window::V;

void Window::initialize_objects()
{

    
	cube = new Cube();
    Body = new OBJObject("body_s.obj");
    Torso = new Geometry("body_s.obj");
    Head = new Geometry("head_s.obj");
    LArm = new Geometry("limb_s.obj");
    RArm = new Geometry("limb_s.obj");
    Lleg = new Geometry("limb_s.obj");
    Rleg = new Geometry("limb_s.obj");
    Leye = new Geometry("eyeball_s.obj");
    Reye = new Geometry("eyeball_s.obj");
    Sphere = new Geometry("eyeball_s.obj");
    Robothead = new Transform();
    Robotbody = new Transform();
    Robotbodyhead = new Transform();
    RobotLarm = new Transform();
    RobotRarm = new Transform();
    Robotarms = new Transform();
    RobotLleg = new Transform();
    RobotRleg = new Transform();
    Robotlegs = new Transform();
    RobotLeye = new Transform();
    RobotReye = new Transform();
    Roboteyes = new Transform();
    Robot = new Transform();
    Army = new Transform();
    Quad1 = new Transform();
    Quad2 = new Transform();
    Quad3 = new Transform();
    Quad4 = new Transform();
    ArmyEC = new Transform();
    RobotEC = new Transform();
    SphereEC = new Transform();


    Spheretrans = new Transform();
    ArmySphere = new Transform;


    Robotbody->addChild(Torso);
    Robothead->addChild(Head);
    Robotbodyhead->addChild(Robotbody);
    Robotbodyhead->addChild(Robothead);
    RobotLarm->addChild(LArm);
    RobotRarm->addChild(RArm);
    Robotarms->addChild(RobotRarm);
    Robotarms->addChild(RobotLarm);
    RobotLleg->addChild(Lleg);
    RobotRleg->addChild(Rleg);
    Robotlegs->addChild(RobotRleg);
    Robotlegs->addChild(RobotLleg);
    RobotLeye->addChild(Leye);
    RobotReye->addChild(Reye);
    Roboteyes->addChild(RobotLeye);
    Roboteyes->addChild(RobotReye);

	// Load the shader program. Make sure you have the correct filepath up top
	shaderProgram = LoadShaders(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
    
    
    
    
    torsomatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.25f, 0.0f));
    bodyheadmatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, 0.0f));
    larmmatrix = larmmatrix * glm::scale(glm::mat4(1.0f), glm::vec3(1.25f, 1.0f,1.0f));
    larmmatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-1.25f, -0.5f,0.0f))* larmmatrix;
    rarmmatrix = rarmmatrix * glm::scale(glm::mat4(1.0f), glm::vec3(1.25f, 1.0f,1.0f));
    rarmmatrix = glm::translate(glm::mat4(1.0f), glm::vec3(1.25f, -0.5f,0.0f)) * rarmmatrix;
    llegmatrix = llegmatrix * glm::scale(glm::mat4(1.0f), glm::vec3(1.25f, 1.0f,1.0f));
    llegmatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, -2.55f,0.0f)) * llegmatrix;
    rlegmatrix = rlegmatrix * glm::scale(glm::mat4(1.0f), glm::vec3(1.25f, 1.0f,1.0f));
    rlegmatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, -2.55f,0.0f)) * rlegmatrix;
    leyematrix = leyematrix * glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f,2.0f));
    leyematrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.35f, 1.0f,0.7f)) * leyematrix;
    reyematrix = reyematrix * glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f,2.0f));
    reyematrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.35f, 1.0f,0.7f)) * reyematrix;
    spherematrix = spherematrix * glm::scale(glm::mat4(1.0f), glm::vec3(40.0f, 40.0f,40.0f));
    sphereECmatrix = sphereECmatrix * glm::scale(glm::mat4(1.f),glm::vec3(350.f, 350.f, 350.f));
    
    Robotbody->MT = torsomatrix;
    Robotbodyhead->MT = bodyheadmatrix;
    RobotLarm->MT = larmmatrix;
    RobotRarm->MT = rarmmatrix;
    RobotLleg->MT = llegmatrix;
    RobotRleg->MT = rlegmatrix;
    RobotLeye->MT = leyematrix;
    RobotReye->MT = reyematrix;
    

    Robot->addChild(Robotbodyhead);
    Robot->addChild(Robotlegs);
    Robot->addChild(Roboteyes);
    Robot->addChild(Robotarms);
    
    Spheretrans->MT = spherematrix;
    Spheretrans->addChild(Sphere);
    SphereEC->MT = sphereECmatrix;
    SphereEC->addChild(Sphere);
    
    for(int i = -5;i<5;++i){
        for (int j = -50;j<50;++j){
            Transform * Robots = new Transform();
            Transform * Robotsphere = new Transform();
            Transform * Spheretran = Spheretrans;
            Robots->addChild(Robotbodyhead);
            Robots->addChild(Robotlegs);
            Robots->addChild(Roboteyes);
            Robots->addChild(Robotarms);
            
            Robotsphere->addChild(Robotbodyhead);
            Robotsphere->addChild(Robotlegs);
            Robotsphere->addChild(Roboteyes);
            Robotsphere->addChild(Robotarms);
            Robotsphere->addChild(Spheretran);
    
    
            Robots->MT = glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f + 8*j, 0.0,-5.0f + 8*i)) * Robots->MT;
            
            Robotsphere->MT = glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f + 8*j, 0.0,-5.0f + 8*i)) * Robotsphere->MT;


            Army->addChild(Robots);
            ArmySphere->addChild(Robotsphere);
            num++;
        }
    }
    

    //Quad1
    for(int i = -2;i<3;++i){
        for (int j = -2;j<3;++j){
            Transform * Robotsphere = new Transform();
            Transform * Spheretran = Spheretrans;

            
            Robotsphere->addChild(Robotbodyhead);
            Robotsphere->addChild(Robotlegs);
            Robotsphere->addChild(Roboteyes);
            Robotsphere->addChild(Robotarms);
            Robotsphere->addChild(Spheretran);
            
            
            
            Robotsphere->MT = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f + 8*j, 0.0,0.0f + 8*i)) * Robotsphere->MT;
            
            
            Quad1->addChild(Robotsphere);
            Quad1->addChild(SphereEC);
            numEC++;
        }
    }
    
    
    
    ////////////////Quad2////////////
    for(int i = -2;i<3;++i){
        for (int j = -2;j<3;++j){
            Transform * Robotsphere = new Transform();
            Transform * Spheretran = Spheretrans;
            
            
            Robotsphere->addChild(Robotbodyhead);
            Robotsphere->addChild(Robotlegs);
            Robotsphere->addChild(Roboteyes);
            Robotsphere->addChild(Robotarms);
            Robotsphere->addChild(Spheretran);
            
            
            
            Robotsphere->MT = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f + 8*j, 0.0,0.0f + 8*i)) * Robotsphere->MT;
            
            
            Quad2->addChild(Robotsphere);
            Quad2->addChild(SphereEC);
            numEC++;
        }
    }
    Quad2->MT = glm::translate(glm::mat4(1.f), glm::vec3(40.f, 0.0f,0.0f));
    
    
    ////////////////Quad3////////////
    for(int i = -2;i<3;++i){
        for (int j = -2;j<3;++j){
            Transform * Robotsphere = new Transform();
            Transform * Spheretran = Spheretrans;
            
            
            Robotsphere->addChild(Robotbodyhead);
            Robotsphere->addChild(Robotlegs);
            Robotsphere->addChild(Roboteyes);
            Robotsphere->addChild(Robotarms);
            Robotsphere->addChild(Spheretran);
            
            
            
            Robotsphere->MT = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f + 8*j, 0.0,0.0f + 8*i)) * Robotsphere->MT;
            
            
            Quad3->addChild(Robotsphere);
            Quad3->addChild(SphereEC);
            numEC++;
        }
    }
    Quad3->MT = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.0f,-40.0f));
    
    
    
    ////////////////Quad4////////////
    for(int i = -2;i<3;++i){
        for (int j = -2;j<3;++j){
            Transform * Robotsphere = new Transform();
            Transform * Spheretran = Spheretrans;
            
            
            Robotsphere->addChild(Robotbodyhead);
            Robotsphere->addChild(Robotlegs);
            Robotsphere->addChild(Roboteyes);
            Robotsphere->addChild(Robotarms);
            Robotsphere->addChild(Spheretran);
            
            
            
            Robotsphere->MT = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f + 8*j, 0.0,0.0f + 8*i)) * Robotsphere->MT;
            
            
            Quad4->addChild(Robotsphere);
            Quad4->addChild(SphereEC);
            numEC++;
        }
    }
    Quad4->MT = glm::translate(glm::mat4(1.f), glm::vec3(40.f, 0.0f,-40.0f));
    
    ArmyEC->addChild(Quad1);
    ArmyEC->addChild(Quad2);
    ArmyEC->addChild(Quad3);
    ArmyEC->addChild(Quad4);
    
    //Robot->addChild();
//    Robot->MT =  glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 3.5f,0.0f)) * Robot->MT;
//    std::cout<<"x: "<< Robot->MT[3][0] << " y: " << Robot->MT[3][1] << " z: "<< Robot->MT[3][2];
    
    //std::cout<< "X: " << Army->MT[3][0]<< " Y: " << Army->MT[3][1] << " Z: " << Army->MT[3][2] <<std::endl;



}

// Treat this as a destructor function. Delete dynamically allocated memory here.
void Window::clean_up()
{

	glDeleteProgram(shaderProgram);
}

GLFWwindow* Window::create_window(int width, int height)
{

	// Initialize GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__ // Because Apple hates comforming to standards
	// Ensure that minimum OpenGL version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Enable forward compatibility and allow a modern OpenGL context
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create the GLFW window
	GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);

	// Check if the window could not be created
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		fprintf(stderr, "Either GLFW is not installed or your graphics card does not support modern OpenGL.\n");
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window
	glfwMakeContextCurrent(window);

	// Set swap interval to 1
	glfwSwapInterval(1);

	// Get the width and height of the framebuffer to properly resize the window

    windowwidth = width;
    windowheight = height;
    glfwGetFramebufferSize(window, &width, &height);

	// Call the resize callback to make sure things get drawn immediately
	Window::resize_callback(window, width, height);

	return window;
}

void Window::resize_callback(GLFWwindow* window, int width, int height)
{
#ifdef __APPLE__
	glfwGetFramebufferSize(window, &width, &height); // In case your Mac has a retina display
#endif
	Window::width = width;
	Window::height = height;
	// Set the viewport size. This is the only matrix that OpenGL maintains for us in modern OpenGL!
	glViewport(0, 0, width, height);

	if (height > 0)
	{
        P = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 1000.0f);
		V = glm::lookAt(cam_pos, cam_look_at, cam_up);
	}
}

void Window::idle_callback()
{
	// Call the update function the cube

}

void Window::display_callback(GLFWwindow* window)
{

    numdis = num;
    int numdissphere = num;
    int numECdis = numEC * 2;
    
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use the shader of programID
	glUseProgram(shaderProgram);
	
	// Render the sphere

    
    
 ///////////////////////Draw here ////////////////////////
    if(count<60){
        RobotRarm->update(-0.01f);
        RobotLleg->update(-0.01f);
        RobotLarm->update(0.01f);
        RobotRleg->update(0.01f);


//        RobotRarm->MT = glm::rotate(glm::mat4(1.0f), 0.01f, glm::vec3(-0.01,0.0,0.0)) * RobotRarm->MT;
//        RobotLleg->MT = glm::rotate(glm::mat4(1.0f), 0.01f, glm::vec3(-0.01,0.0,0.0)) * RobotLleg->MT;
//        RobotLarm->MT = glm::rotate(glm::mat4(1.0f), 0.01f, glm::vec3(0.01,0.0,0.0)) * RobotLarm->MT;
//        RobotRleg->MT = glm::rotate(glm::mat4(1.0f), 0.01f, glm::vec3(0.01,0.0,0.0)) * RobotRleg->MT;
        count++;
    }
    if((59<count)&&(count<180)){
        RobotRarm->update(0.01f);
        RobotLleg->update(0.01f);
        RobotLarm->update(-0.01f);
        RobotRleg->update(-0.01f);
//        RobotRarm->MT = glm::rotate(glm::mat4(1.0f), 0.01f, glm::vec3(0.01,0.0,0.0)) * RobotRarm->MT;
//        RobotLleg->MT = glm::rotate(glm::mat4(1.0f), 0.01f, glm::vec3(0.01,0.0,0.0)) * RobotLleg->MT;
//        RobotLarm->MT = glm::rotate(glm::mat4(1.0f), 0.01f, glm::vec3(-0.01,0.0,0.0)) * RobotLarm->MT;
//        RobotRleg->MT = glm::rotate(glm::mat4(1.0f), 0.01f, glm::vec3(-0.01,0.0,0.0)) * RobotRleg->MT;
        count++;
    }
    if(count>=180){
        count = -60;
    }
   
    
    
    if(ECCull == 0){
        Army->drawid = 1;
        ArmySphere->drawid = 1;
        

            for(Node * child : Army->Nodelist){
                float x = ((Transform* )child)->MT[3][0];
                float y = ((Transform* )child)->MT[3][1];
                float z = ((Transform* )child)->MT[3][2];
                child->drawid = InsideBool(x, y, z, NormalR);
                if(child->drawid == false){
                    numdis--;
                }
            }

        
            for(Node * child : ArmySphere->Nodelist){
                float x = ((Transform* )child)->MT[3][0];
                float y = ((Transform* )child)->MT[3][1];
                float z = ((Transform* )child)->MT[3][2];
                child->drawid = InsideBool(x, y, z,NormalR);
                if(child->drawid == false){
                    numdissphere--;
                }
            }
        
        
        if(spherebool == 0){
            Army->draw(shaderProgram, glm::mat4(1.0f));
            std::cout << numdis << std::endl;

        }
        if(spherebool == 1){
            ArmySphere->draw(shaderProgram, glm::mat4(1.0f));
            std::cout << numdissphere << std::endl;

        }
    }
    
    if(ECCull == 1){
        ArmyEC->drawid = 1;
        
        
        for(Node * child : ArmyEC->Nodelist){
            float x = ((Transform* )child)->MT[3][0];
            float y = ((Transform* )child)->MT[3][1];
            float z = ((Transform* )child)->MT[3][2];
            child->drawid = InsideBool(x, y, z, ECR);
        }
        
        for(Node * child : Quad1->Nodelist){
            float x = ((Transform* )child)->MT[3][0];
            float y = ((Transform* )child)->MT[3][1];
            float z = ((Transform* )child)->MT[3][2];
            child->drawid = InsideBool(x, y, z, ECR);
            if(child->drawid == false){
                numECdis--;
            }
            
        }
        for(Node * child : Quad2->Nodelist){
            float x = ((Transform* )child)->MT[3][0];
            float y = ((Transform* )child)->MT[3][1];
            float z = ((Transform* )child)->MT[3][2];
            child->drawid = InsideBool(x, y, z, ECR);
            if(child->drawid == false){
                numECdis--;
            }
        }
        for(Node * child : Quad3->Nodelist){
            float x = ((Transform* )child)->MT[3][0];
            float y = ((Transform* )child)->MT[3][1];
            float z = ((Transform* )child)->MT[3][2];
            child->drawid = InsideBool(x, y, z, ECR);
            if(child->drawid == false){
                numECdis--;
            }
        }
        for(Node * child : Quad4->Nodelist){
            float x = ((Transform* )child)->MT[3][0];
            float y = ((Transform* )child)->MT[3][1];
            float z = ((Transform* )child)->MT[3][2];
            child->drawid = InsideBool(x, y, z, ECR);
            if(child->drawid == false){
                numECdis--;
            }
        }
        std::cout << numECdis/2 << std::endl;
        ArmyEC->draw(shaderProgram,glm::mat4(1.f));
    }
    
    
    
//    Robotlegs->draw(shaderProgram, Window::V);
//    Robotarms->draw(shaderProgram,Window::V);
//    Robotbodyhead->draw(shaderProgram, Window::V);
//    RobotLeye->draw(shaderProgram, Window::V);
//    RobotReye->draw(shaderProgram, Window::V);



    
	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();
	// Swap buffers
	glfwSwapBuffers(window);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check for a key press
	if (action == GLFW_PRESS)
	{
		// Check if escape was pressed
		if (key == GLFW_KEY_ESCAPE)
		{
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);
        }
        if(key == GLFW_KEY_C){
            if(mods == GLFW_MOD_SHIFT){
                clickid = 1;
            }
            else{
                clickid = 0;
            }
        }
        if(key == GLFW_KEY_S){
            if(mods == GLFW_MOD_SHIFT){
                spherebool = 1;
            }
            else{
                spherebool = 0;
            }
        }
        if(key == GLFW_KEY_D){
            if(mods == GLFW_MOD_SHIFT){
                Debug = 1;
            }
            else{
                Debug = 0;
            }
        }
        if(key == GLFW_KEY_E){
            if(mods == GLFW_MOD_SHIFT){
                ECCull = 1;
            }
            else{
                ECCull = 0;
            }
        }
	}
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if(yoffset < 0){
        //glm::mat4 zoommatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.1f,1.1f,1.1f));
        glm::vec3 cam_dir = - cam_pos + cam_look_at;
        cam_pos = cam_pos + glm::vec3(0.05f, 0.05f, 0.05f) * cam_dir;
        V = glm::lookAt(cam_pos, cam_look_at, cam_up);
    }
    if(yoffset > 0){
        //glm::mat4 zoommatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1/1.1f,1/1.1f,1/1.1f));
        glm::vec3 cam_dir = - cam_pos + cam_look_at;
        cam_pos = cam_pos - glm::vec3(0.05f, 0.05f, 0.05f) * cam_dir;
        V = glm::lookAt(cam_pos, cam_look_at, cam_up);
    }
}


void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        clicked = 1;
    }
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        clicked = 0;
    }
}



void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    glm::mat4 tempcammatrix = glm::mat4(1.0f);

    if ((curxpos == 0) && (curypos == 0)) {
        curxpos = xpos;
        curypos = ypos;
    }
    
    if(clicked){
        lastvec = trackBallMapping(curxpos, curypos);
        curvec = trackBallMapping(xpos, ypos);
        direction = curvec - lastvec;
        float velocity = glm::length(direction);
        if(velocity > 0.01){
            glm::vec3 rotaxis;
            rotaxis = cross(lastvec,curvec);
            float value = (dot(lastvec,curvec))/((glm::length(lastvec))*(glm::length(curvec)));
            rotangle = acos(value);
            if(clickid == 0){
                tempcammatrix = tempcammatrix * glm::rotate(glm::mat4(1.0f),rotangle,rotaxis);
                glm::vec3 cam_dir = -cam_pos + cam_look_at;
                //cam_pos = glm::vec3(tempcammatrix * glm::vec4(cam_pos,1));
                //cam_up = glm::vec3( tempcammatrix * glm::vec4(cam_up,1));
                cam_dir = glm::vec3(tempcammatrix * glm::vec4(cam_dir,1));
                cam_look_at = cam_pos + cam_dir;
                V = glm::lookAt(cam_pos, cam_look_at, cam_up);
            }
            if(clickid == 1 ){
                Army->MT = glm::rotate(glm::mat4(1.0f), rotangle, rotaxis) * Army->MT;
                Robot->MT = glm::rotate(glm::mat4(1.0f), rotangle, rotaxis) * Robot->MT;
                ArmySphere->MT = glm::rotate(glm::mat4(1.0f), rotangle, rotaxis) * ArmySphere->MT;
            }
        }
        curxpos = xpos;
        curypos = ypos;
    }
    else{
        curxpos = curypos = 0;
    }
        
}




glm::vec3 Window::trackBallMapping(double xpos, double ypos){
    glm::vec3 v;
    float d;

    v.x = (2.0*xpos - (windowwidth)) / (windowwidth);
    v.y = ((windowheight) - 2.0*ypos) / (windowheight);
    v.z = 0.0;
    d = glm::length(v);
    d = (d<1.0) ? d : 1.0;
    v.z = sqrtf(1.001 - d*d);
    glm::normalize(v);
    return v;
}






bool Window::InsideBool(float x, float y, float z,float r){
    glm::vec3 fc;
    glm::vec3 ftl;
    glm::vec3 ftr;
    glm::vec3 fbl;
    glm::vec3 fbr;
    glm::vec3 nc;
    glm::vec3 ntl;
    glm::vec3 ntr;
    glm::vec3 nbl;
    glm::vec3 nbr;
    

    glm::vec3 up_normal;
    glm::vec3 left_normal;
    glm::vec3 right_normal;
    glm::vec3 down_normal;
    glm::vec3 forward_normal;
    glm::vec3 back_normal;
    float dist;
    int count = 0;
    float Hfarhalf;
    float Hnear;
    
    if(Debug == 1){
        Hfarhalf = tan(glm::radians(22.5f)) * 1000.0f;
    }
    else{
        Hfarhalf = tan(glm::radians(15.5f)) * 1000.0f;
    }
    float Wfarhalf = Hfarhalf * ((float)width / (float)height);

    float Hfar = 2 * Hfarhalf;
    float Wfar = 2 * Wfarhalf;
    
    glm::vec3 p = cam_pos;
    glm::vec3 d = normalize(cam_look_at - cam_pos);
    glm::vec3 up = normalize(cam_up);
    glm::vec3 right = -normalize(cross(cam_up,cam_look_at - cam_pos));
    
    
    fc = p + d * 1000.0f;
    

    
    ftl = fc + (up * Hfar/2.0f) - (right * Wfar/2.0f);
    ftr = fc + (up * Hfar/2.0f) + (right * Wfar/2.0f);
    fbl = fc - (up * Hfar/2.0f) - (right * Wfar/2.0f);
    fbr = fc - (up * Hfar/2.0f) + (right * Wfar/2.0f);

    
    

    
    nc = p + d * 0.1f;
    if(Debug == 0){
        Hnear = tan(glm::radians(22.5f)) * 0.1f * 2;
    }
    else{
        Hnear = tan(glm::radians(15.5f)) * 0.1f * 2;
    }
    float Wnear = 2 * Hnear * width / height;
    
    
    ntl = nc + (up * Hnear/2.0f) - (right * Wnear/2.0f);

    //std::cout<< Wnear <<std::endl;
    
    ntr = nc + (up * Hnear/2.0f) + (right * Wnear/2.0f);
    nbl = nc - (up * Hnear/2.0f) - (right * Wnear/2.0f);
    nbr = nc - (up * Hnear/2.0f) + (right * Wnear/2.0f);
    
    up_normal = normalize(cross((ntl-ftl),(ftr-ftl)));
    //std::cout<<"x: "<< right[0] << " y: " << right[1] << " z: "<< right[2]<< std::endl;
    down_normal = normalize(cross((fbr-fbl),(nbl-fbl)));
    left_normal = normalize(cross((nbl-fbl),(ftl-fbl)));
    right_normal = normalize(cross((ftr-fbr),(nbr-fbr)));
    forward_normal = normalize(cross((nbl-ntl),(ntr-ntl)));
    back_normal = normalize(cross((ftr-ftl),(fbl-ftl)));
    
    glm::vec3 position = glm::vec3(x,y,z);
    
    
    //upward face check
    dist  = dot((position-ftl),up_normal);
    if(dist<r){
        count++;
    }
    
    //downward face check
    dist = dot((position-fbl), down_normal);
    if(dist<r){
        count++;
    }
    
    //right face check
    dist = dot((position-fbr), right_normal);
    if(dist<r){
        count++;
    }
    
    //left face check
    dist = dot((position-fbl), left_normal);
    if(dist<r){
        count++;
    }
    
    //forward face check
    dist = dot((position-nbl), forward_normal);
    if(dist<r){
        count++;
    }
    
    //backward face check
    dist = dot((position-fbl), back_normal);
    if(dist<r){
        count++;
    }
    

    if(count == 6){
        return true;
    }
    
    return false;

}

    
    
    

