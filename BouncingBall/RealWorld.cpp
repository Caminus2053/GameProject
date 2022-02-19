#include "RealWorld.h"
#include "ResourceSystem.h"
#include "RenderSystem.h"
#include <string>

RealWorld::RealWorld(std::string _title) :
	mTitle(_title)
{
	mResourceSystem = new ResourceSystem(*this);
	mRenderSystem = new RenderSystem(*this);
}
RealWorld::~RealWorld() {
	Destroy();
}

bool RealWorld::Initialize() {
	//SDL 초기화
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		SDL_Log("SDL Initialize failed : %s", SDL_GetError());
		return false;
	}

	//화면 중앙으로
	//putenv("SDL_VIDEO_CENTERED=1");

	//RenderSystem 초기화
	if (!mRenderSystem->Initialize(1024.0f, 768.0f)) {
		SDL_Log("RenderSystem Initialize failed");
		return false;
	}

	mInit = true;
	return true;
}

void RealWorld::Destroy() {
	if (!mInit) return;
	delete mResourceSystem;
	delete mRenderSystem;
}

void RealWorld::Draw() {
	mRenderSystem->Draw();
}