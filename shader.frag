#version 330 core
// This is a sample fragment shader.

// Inputs to the fragment shader are the outputs of the same name from the vertex shader.
// Note that you do not have access to the vertex shader's default output, gl_Position.
in float sampleExtraOutput;
in vec3 FragPos;
in vec3 Normal;
in vec3 Normaltrans;
in vec2 fragTexCoord;
uniform sampler2D tex;



// You can output many things. The first vec4 type output determines the color of the fragment
out vec4 color;



void main()
{
    color = texture(tex,fragTexCoord);
    //color = vec4(Normal,1);
}
