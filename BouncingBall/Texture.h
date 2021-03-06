#pragma once
#include <string>

class Texture {
private:
	//텍스쳐 ID
	unsigned int mTextureID;
	//너비, 높이
	int mWidth, mHeight;
	//로드 여부
	bool mLoad = false;

public:
	//생성/소멸자
	Texture();
	~Texture();

	//로드
	bool Load(const std::string& fileName);
	void Destroy();

	//텍스쳐 생성
	void CreateFromSurface(struct SDL_Surface* surface);
	void CreateForRendering(int width, int height, unsigned int format);

	//활성화(바인딩)
	void Active();

	//Get
	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }
	unsigned int GetTextureID() const { return mTextureID; }
	
};