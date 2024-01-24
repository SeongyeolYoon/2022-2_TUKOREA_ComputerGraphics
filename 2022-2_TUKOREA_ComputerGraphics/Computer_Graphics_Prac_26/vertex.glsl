#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;
layout (location = 3) in vec3 vColor;

out vec3 outNormal;
out vec2 TexCoord;
out vec3 Color;

uniform mat4 modelTransform; // �𵨸� ��ȯ��
uniform mat4 viewTransform; // ���� ��ȯ��
uniform mat4 projectionTransform; // ���� ��ȯ��

void main()
{
	gl_Position = projectionTransform * viewTransform * modelTransform * vec4(vPos,1.0);
	outNormal = vNormal;
	TexCoord = vTexCoord;
	Color = vColor;
}