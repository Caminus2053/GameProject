#pragma once
#include <string>

class Texture {
private:
	//�ؽ��� ID
	unsigned int mTextureID;
	//�ʺ�, ����
	int mWidth, mHeight;
	//�ε� ����
	bool mLoad = false;

public:
	//����/�Ҹ���
	Texture();
	~Texture();

	//�ε�
	bool Load(const std::string& fileName);
	void Destroy();

	//�ؽ��� ����
	void CreateFromSurface(struct SDL_Surface* surface);
	void CreateForRendering(int width, int height, unsigned int format);

	//Ȱ��ȭ(���ε�)
	void Active();

	//Get
	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }
	unsigned int GetTextureID() const { return mTextureID; }
	
};