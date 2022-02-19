//GLSL 3.3 ���
#version 330

// vertex shader ���� �Ѿ�� ������
in vec2 fragTextureCoord;

// Color Buffer�� �Ѱ��� ����
out vec4 outColor;

// �ؽ��� ���ø���
// ���� ���� �ȳ־��ָ� ���� �ֱ�Į�� ������ �ʱ�ȭ��
uniform sampler2D uTexture;

void main()
{
	// �ؽ��Ŀ��� Color �� ��������
	outColor = texture(uTexture, fragTextureCoord);
}
