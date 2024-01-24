#version 330 core

out vec4 FragColor;

in vec3 outNormal;
in vec2 TexCoord;

uniform sampler2D outTexture;

void main()
{
	FragColor = texture(outTexture,TexCoord);

	// ���� �����ϴ� ���
	// FragColor = vec4(result,1.0f);
	// FragColor = texture(outTexture,TexCoord) * FragColor;
}

