#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <SDL2/SDL_types.h>

class GameMaster {
public:
	//게임 상태
	enum class State
	{
		Play = 0,
		Paused = 1,
		Quit = 2
	};

private:
	void UpdateGame();
	void LoadData();
	void UnloadData();

	//게임 시간
	Uint32 mGameTime;
	//게임 상태
	State mState;

	//리소스, 랜더링, 사운드 등 담당
	class RealWorld* mRealWorld;

public:
	GameMaster();

	//
	bool Initialize();
	void GameLoop();
	void Quit();

	State GetState() const { return mState; }
	void SetState(State _state) { mState = _state; }
};