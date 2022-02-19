//GLSL 3.3 사용
#version 330

//glVertexAttribPointer로 설정
//0번째 속성 == 위치
//1번째 속성 == 법선 좌표
//2번째 속성 == 텍스쳐 coordiante
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTextureCoord;

//Uniform -> 계속 바뀌는 값
uniform mat4 uWorldTransform;
uniform mat4 uViewProjection;

// Add texture coordinate as output
out vec2 fragTextureCoord;

void main()
{
	//동차 행렬 생성
	vec4 position = vec4(inPosition, 1.0);
	//위치 계산 및 적용
	gl_Position = position * uWorldTransform * uViewProjection;
	//gl_Position = position * uViewProjection;
	//gl_Position = position * uWorldTransform;

	//fragment shader에 텍스쳐 coordiante 보내주기
	fragTextureCoord = inTextureCoord;
}
