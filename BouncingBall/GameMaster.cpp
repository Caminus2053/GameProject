#include "GameMaster.h"
#include "RealWorld.h"
#include <string>
#include <SDL2/SDL.h>

GameMaster::GameMaster()
{
	mRealWorld = new RealWorld("BouncingBall");
}
bool GameMaster::Initialize() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
		SDL_Log("SDL Initialize failed : %s", SDL_GetError());
		return false;
	}

	if (!mRealWorld->Initialize())
		return false;

	mGameTime = SDL_GetTicks();

	return true;
}
void GameMaster::GameLoop() {
	while (mState != State::Quit) {
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				mState = State::Quit;
				break;
			}
		}

		const Uint8* state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_ESCAPE])
			mState = State::Quit;

		//RealWorld.Update();	-> 입력 처리
		//GameWorld.Update();	-> 퍼펫, 오디오(?), UI 순으로 처리
		mRealWorld->Draw();
	}
}
void GameMaster::Quit() {
	mRealWorld->Destroy();
}

void GameMaster::UpdateGame() {

}
void GameMaster::LoadData() {

}
void GameMaster::UnloadData() {

}