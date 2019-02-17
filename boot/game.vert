#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

// 骨骼绑定 [骨骼索引 -1 无骨骼, 关联系数 1-100]
uniform ivec2 skBind;
uniform mat4 skeleton[10];

out vec3 ourColor;

uniform mat4 model;
uniform mat4 camera;
uniform mat4 projection;

uniform float colorCoefficient;
uniform float postitonCoefficient;

void main()
{
    vec4 pos = projection * camera * model
             * vec4(aPos[0]/postitonCoefficient, 
                    aPos[1]/postitonCoefficient,
                    aPos[2]/postitonCoefficient, 1.0);

    if (skBind[0] >= 0) {
      mat4 sk = skeleton[ skBind[0] ];
      pos = pos * (sk /* * (1/skBind[1])*/ );
    }

    gl_Position = pos;

    ourColor = vec3(aColor[0]/colorCoefficient, 
               aColor[1]/colorCoefficient, 
               aColor[2]/colorCoefficient);
}