#include "VertexArray.h"
#include "SizeValues.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>

//����/�Ҹ���
VertexArray::VertexArray(const void* _vertices, unsigned int _num_vertices,
	const unsigned int* _indices, unsigned int _num_indices) :
	mNumVertices(_num_vertices),
	mNumIndices(_num_indices)
{
	//Vertex Array ����
	glGenVertexArrays(1, &mVertexArray);
	//���ε� �� ID �����ؼ� �Ű������� �Ѱ���
	//�� Vertex Array�� ID ����!
	glBindVertexArray(mVertexArray);

	//VertexSize ����
	GLuint vertex_size = 8 * size_f;

	//Vertex Buffer ����
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	//���� ������ �ֱ�
	//GL_STATIC_DRAW : �����͸� �ѹ��� �ε� -> ���� �׸� ��� ���
	glBufferData(
		GL_ARRAY_BUFFER,				//�����͸� �� ������ ���� Ÿ��
		_num_vertices * vertex_size,	//������ ����Ʈ ũ��
		_vertices,						//������ ������(������)
		GL_STATIC_DRAW);				//�� ������ �뵵

	//Index Buffer ����
	//Vertex Buffer ���� ���
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		_num_indices * size_ui,
		_indices,
		GL_STATIC_DRAW);

	//Vertex Shader �Ӽ��� ���� = Vertex Shader Layout ����
	//0 ��° Vertex �Ӽ� ���� = ��ġ ��ǥ
	glEnableVertexAttribArray(0);
	//�Ӽ� ���� ����
	glVertexAttribPointer(
		0,					//�Ӽ� �ε���
		3,					//����� ��(���⼱ x,y,z 3��)
		GL_FLOAT,			//����� Ÿ��
		GL_FALSE,			//(�������� ���)
		vertex_size,		//����(�� ���ؽ��� ũ��)
		0					//���ؽ��� ���ۿ��� �� �Ӽ������� ������
	);
	//1 ��° Vertex �Ӽ� ���� = ���� ��ǥ
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertex_size,
		reinterpret_cast<void*>(size_f * 3));
	//2 ��° Vertex �Ӽ� ���� = �ؽ��� ��ǥ
	glEnableVertexAttribArray(2);
	//�������� reinterpret_cast<void*>(sizeof(float) * 6)�� ����:
	//x, y, z��ǥ ����Ʈ ��ŭ �Ѿ�� u, v ��ǥ�� ���ͼ� �̸�ŭ �����µ�
	//reinterpret_cast<void*>�� ���� : ������ void*�� ��ȯ�ϱ� ����
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertex_size,
		reinterpret_cast<void*>(size_f * 6));
}
VertexArray::~VertexArray() {
	//��� ���� ����
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteBuffers(1, &mVertexArray);
}

//���ε�
void VertexArray::Active() {
	glBindVertexArray(mVertexArray);
}