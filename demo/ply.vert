#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform mat4 transform;
uniform mat4 model;
uniform mat4 camera;
uniform mat4 projection;

void main()
{
    gl_Position = projection * camera * model
            * transform 
            * vec4(aPos[0]/10, aPos[1]/10, aPos[2]/10, 1.0);

    ourColor = vec3(aColor[0]/255, aColor[1]/255, aColor[2]/255);
}