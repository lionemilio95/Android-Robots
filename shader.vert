#version 330 core
// NOTE: Do NOT use any version older than 330! Bad things will happen!

// This is an example vertex shader. GLSL is very similar to C.
// You can define extra functions if needed, and the main() function is
// called when the vertex shader gets run.
// The vertex shader gets called once per vertex.

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texture;



// Uniform variables can be updated by fetching their location and passing values to that location
uniform mat4 projection;
uniform mat4 modelview;
uniform mat4 model;

// Outputs of the vertex shader are the inputs of the same name of the fragment shader.
// The default output, gl_Position, should be assigned something. You can define as many
// extra outputs as you need.
out vec3 Normal;
out vec3 Normaltrans;
out vec3 FragPos;
out float sampleExtraOutput;
out vec2 fragTexCoord;


void main()
{
    // OpenGL maintains the D matrix so you only need to multiply by P, V (aka C inverse), and M
    gl_Position = projection * modelview * vec4(position.x, position.y, position.z, 1.0);
    sampleExtraOutput = 1.0f;
    FragPos = vec3(model * vec4(position, 1.0f));
    
//    Normal = (normalize(normal) * 0.5 + 0.5);
//    Normaltrans = mat3(transpose(inverse(model))) * (normalize(normal) * 0.5 + 0.5);
//    Normaltrans = normalize(Normaltrans);
    fragTexCoord = texture;

    
    
}
