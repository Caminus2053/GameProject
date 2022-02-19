//GLSL 3.3 ���
#version 330

//glVertexAttribPointer�� ����
//0��° �Ӽ� == ��ġ
//1��° �Ӽ� == ���� ��ǥ
//2��° �Ӽ� == �ؽ��� coordiante
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTextureCoord;

//Uniform -> ��� �ٲ�� ��
uniform mat4 uWorldTransform;
uniform mat4 uViewProjection;

// Add texture coordinate as output
out vec2 fragTextureCoord;

void main()
{
	//���� ��� ����
	vec4 position = vec4(inPosition, 1.0);
	//��ġ ��� �� ����
	gl_Position = position * uWorldTransform * uViewProjection;
	//gl_Position = position * uViewProjection;
	//gl_Position = position * uWorldTransform;

	//fragment shader�� �ؽ��� coordiante �����ֱ�
	fragTextureCoord = inTextureCoord;
}
