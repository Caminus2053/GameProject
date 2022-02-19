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

//�ؽ��� �ε�
bool Texture::Load(const std::string& fileName) {

	int channels = 0;
	//�ؽ��� �̹��� ������ �ε�
	unsigned char* image = SOIL_load_image(
		fileName.c_str(),
		&mWidth, &mHeight,
		&channels, SOIL_LOAD_AUTO
	);

	//�ε� ���н�
	if (image == nullptr) {
		SDL_Log("SOIL �̹��� �ε� ���� %s : %s", fileName.c_str(), SOIL_last_result());
		return false;
	}

	//ä�� �� == RGBA
	int format = GL_RGB;
	if (channels == 4)
		format = GL_RGBA;

	//�ؽ��� ������Ʈ ����
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);

	//�ؽ��� ������Ʈ�� �ؽ��� �̹��� ������ ����
	glTexImage2D(
		GL_TEXTURE_2D,		//�ؽ��� Ÿ��
		0,					//LOD
		format,				//OpenGL�� ����ؾ� �Ǵ� ���� ����(ä��)
		mWidth,				//�ʺ�
		mHeight,			//����
		0,					//����(0�̾�ߵ�?)
		format,				//�Է� ������ ���� ����(ä��)
		GL_UNSIGNED_BYTE,	//�Է� ������ ��Ʈ ����
		image);				//�̹��� �������� ������

	//�̹��� ������ ����
	SOIL_free_image_data(image);

	//mipmaps ����
	glGenerateMipmap(GL_TEXTURE_2D);
	//��� ���� : �Ӹ� ��������(3�� ��������) ���
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//Ȯ�� ���� : ���� ���� ����(2�� ��������) ���
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//anisotrpic ����(�̹漺 ���͸�) ��� ���� üũ
	if (GLEW_EXT_texture_filter_anisotropic) {
		//�̹漺 �ִ� ���ϱ�
		GLfloat largest;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest);
		//�̹漺 ���͸� Ȱ��ȭ
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest);
	}

	mLoad = true;
	return true;
}

//�ؽ��� ����
void Texture::Destroy() {
	if(mLoad) glDeleteTextures(1, &mTextureID);
}

//Surface���� �ؽ��� ����
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

	//bilinear ���͸�(���߼��� ���͸�) Ȱ��ȭ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

//�������� �ؽ���(����ִ� �ؽ���) ����
void Texture::CreateForRendering(int width, int height, unsigned int format) {
	mWidth = width;
	mHeight = height;

	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,				//������ ��Ұ� nullptr�̸�
		format,			//2,3��° ��Ұ� ���õ�
		mWidth,
		mHeight,
		0,
		GL_RGB,
		GL_FLOAT,
		nullptr			//��������Ƿ� nullptr
	);

	//�����������͸� ���X -> ��Ȯ�� ���ø� �ȼ� �����Ͱ� �ʿ�������
	//�׷��� �ϴ� �ֱ��� �̿� ���͸����� ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

//���ε�
void Texture::Active() {
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}
