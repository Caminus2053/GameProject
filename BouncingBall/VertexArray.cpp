#include "VertexArray.h"
#include "SizeValues.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>

//생성/소멸자
VertexArray::VertexArray(const void* _vertices, unsigned int _num_vertices,
	const unsigned int* _indices, unsigned int _num_indices) :
	mNumVertices(_num_vertices),
	mNumIndices(_num_indices)
{
	//Vertex Array 생성
	glGenVertexArrays(1, &mVertexArray);
	//바인딩 후 ID 생성해서 매개변수에 넘겨줌
	//즉 Vertex Array의 ID 생성!
	glBindVertexArray(mVertexArray);

	//VertexSize 설정
	GLuint vertex_size = 8 * size_f;

	//Vertex Buffer 생성
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	//버퍼 데이터 넣기
	//GL_STATIC_DRAW : 데이터를 한번만 로드 -> 자주 그릴 경우 사용
	glBufferData(
		GL_ARRAY_BUFFER,				//데이터를 쓸 버퍼의 버퍼 타입
		_num_vertices * vertex_size,	//복사할 바이트 크기
		_vertices,						//복사할 데이터(포인터)
		GL_STATIC_DRAW);				//이 데이터 용도

	//Index Buffer 생성
	//Vertex Buffer 같은 방식
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		_num_indices * size_ui,
		_indices,
		GL_STATIC_DRAW);

	//Vertex Shader 속성들 설정 = Vertex Shader Layout 설정
	//0 번째 Vertex 속성 설정 = 위치 좌표
	glEnableVertexAttribArray(0);
	//속성 포멧 설정
	glVertexAttribPointer(
		0,					//속성 인덱스
		3,					//요소의 수(여기선 x,y,z 3개)
		GL_FLOAT,			//요소의 타입
		GL_FALSE,			//(정수형만 사용)
		vertex_size,		//간격(각 버텍스의 크기)
		0					//버텍스의 시작에서 이 속성까지의 오프셋
	);
	//1 번째 Vertex 속성 설정 = 법선 좌표
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertex_size,
		reinterpret_cast<void*>(size_f * 3));
	//2 번째 Vertex 속성 설정 = 텍스쳐 좌표
	glEnableVertexAttribArray(2);
	//오프셋이 reinterpret_cast<void*>(sizeof(float) * 6)인 이유:
	//x, y, z좌표 바이트 만큼 넘어가야 u, v 좌표가 나와서 이만큼 오프셋둠
	//reinterpret_cast<void*>쓴 이유 : 강제로 void*로 변환하기 위해
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertex_size,
		reinterpret_cast<void*>(size_f * 6));
}
VertexArray::~VertexArray() {
	//모든 버퍼 제거
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteBuffers(1, &mVertexArray);
}

//바인딩
void VertexArray::Active() {
	glBindVertexArray(mVertexArray);
}