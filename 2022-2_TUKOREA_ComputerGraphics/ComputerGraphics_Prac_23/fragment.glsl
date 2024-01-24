#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec3 Color;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main()
{
	float ambientLight = 0.3; // 주변 조명 계수
	vec3 ambient = ambientLight *vec3(0.5f,0.5f,0.5f); // 주변 조명 값

	vec3 normalVector = normalize(Normal); // 노말 정규화
	vec3 lightDir = normalize(lightPos - FragPos); // 표면과 조명의 위치로 조명 방향 결정
	float diffuseLight = max(dot(normalVector,lightDir),0.0); // N과 L의 내적 값으로 강도 조절 (음의 값 X)
	vec3 diffuse = diffuseLight * lightColor; // 산란반사 조명 값 = 산란반사값 * 조명색상값

	int shininess = 128; // 광택 계수 
	vec3 viewDir = normalize(viewPos - FragPos); // 관찰자 방향
	vec3 reflectDir = reflect(-lightDir,normalVector); // 반사 방향: reflect 함수 - 입사 벡터의 반사 방향 계산
	float specularLight = max(dot(viewDir,reflectDir),0.0); // V와 R의 내적값으로 강도 조절: 음수 방지 
	specularLight = pow(specularLight,shininess); // shininess 승을 해주어 하이라이트 만들어 줌
	vec3 specular = specularLight * lightColor; // 거울 반사 조명값: 거울반사값 * 조명색상값 

	vec3 result = (ambient + diffuse + specular) * Color; // 최종 조명 설정된 픽셀 색상: (주변+산란반사+거울반사조명) * 객체색상 

	FragColor = vec4(result,1.0); // 픽셀 색 출력 
}