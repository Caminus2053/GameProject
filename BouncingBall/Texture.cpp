#include "Texture.h"
#include <SOIL2/SOIL2.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>

Texture::Texture() :
	mTextureID(0),
	mWidth(0), mHeight(0)
{

}
Texture::~Texture() {
	Destroy();
}

//텍스쳐 로드
bool Texture::Load(const std::string& fileName) {

	int channels = 0;
	//텍스쳐 이미지 데이터 로드
	unsigned char* image = SOIL_load_image(
		fileName.c_str(),
		&mWidth, &mHeight,
		&channels, SOIL_LOAD_AUTO
	);

	//로드 실패시
	if (image == nullptr) {
		SDL_Log("SOIL 이미지 로드 실패 %s : %s", fileName.c_str(), SOIL_last_result());
		return false;
	}

	//채널 수 == RGBA
	int format = GL_RGB;
	if (channels == 4)
		format = GL_RGBA;

	//텍스쳐 오브젝트 생성
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);

	//텍스쳐 오브젝트에 텍스쳐 이미지 데이터 복사
	glTexImage2D(
		GL_TEXTURE_2D,		//텍스쳐 타깃
		0,					//LOD
		format,				//OpenGL이 사용해야 되는 색상 포맷(채널)
		mWidth,				//너비
		mHeight,			//높이
		0,					//보더(0이어야됨?)
		format,				//입력 데이터 색상 포맷(채널)
		GL_UNSIGNED_BYTE,	//입력 데이터 비트 깊이
		image);				//이미지 데이터의 포인터

	//이미지 데이터 해제
	SOIL_free_image_data(image);

	//mipmaps 생성
	glGenerateMipmap(GL_TEXTURE_2D);
	//축소 필터 : 밉맵 선형보간(3중 선형보간) 사용
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//확대 필터 : 기존 선형 보간(2중 선형보간) 사용
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//anisotrpic 필터(이방성 필터링) 사용 가능 체크
	if (GLEW_EXT_texture_filter_anisotropic) {
		//이방성 최댓값 구하기
		GLfloat largest;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest);
		//이방성 필터링 활성화
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest);
	}

	mLoad = true;
	return true;
}

//텍스쳐 삭제
void Texture::Destroy() {
	if(mLoad) glDeleteTextures(1, &mTextureID);
}

//Surface에서 텍스쳐 생성
void Texture::CreateFromSurface(SDL_Surface* surface) {
	mWidth = surface->w;
	mHeight = surface->h;

	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		mWidth,
		mHeight,
		0,
		GL_BGRA,
		GL_UNSIGNED_BYTE,
		surface->pixels
	);

	//bilinear 필터링(이중선형 필터링) 활성화
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

//랜더링용 텍스쳐(비어있는 텍스쳐) 생성
void Texture::CreateForRendering(int width, int height, unsigned int format) {
	mWidth = width;
	mHeight = height;

	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,				//마지막 요소가 nullptr이면
		format,			//2,3번째 요소가 무시됨
		mWidth,
		mHeight,
		0,
		GL_RGB,
		GL_FLOAT,
		nullptr			//비어있으므로 nullptr
	);

	//선형보간필터링 사용X -> 정확한 샘플링 픽셀 데이터가 필요함으로
	//그래서 일단 최근접 이웃 필터링으로 설정
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

//바인딩
void Texture::Active() {
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}
