#pragma once
#include <GL/glew.h>

class VertexArray {
private:
	/*
	Vertex : ��
	indices : index�� ������ = ���ε�
	mNumVerts : Vertex Buffer�� ���� vertex ��
	mNumIndices : Index Buffer�� ���� index ��
	mVertexBuffer : Vertex Buffer�� OpenGL ID
	mIndexBuffer : Index Buffer�� OpenGL ID
	mVertexArray : Vertex Array ��ü�� OpenGL ID
	*/
	GLuint mNumVertices, mNumIndices;
	GLuint mVertexBuffer, mIndexBuffer;
	GLuint mVertexArray;

public:
	//����/�Ҹ���
	VertexArray(const void* _vertices, unsigned int _num_vertices,
		const unsigned int* _indices, unsigned int _num_indices);
	~VertexArray();

	//Ȱ��ȭ(���ε�)
	void Active();

	//Get
	unsigned int GetNumIndices() const { return mNumIndices; }
	unsigned int GetNumVertices() const { return mNumVertices; }
};