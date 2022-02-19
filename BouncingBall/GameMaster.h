#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <SDL2/SDL_types.h>

class GameMaster {
public:
	//���� ����
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

	//���� �ð�
	Uint32 mGameTime;
	//���� ����
	State mState;

	//���ҽ�, ������, ���� �� ���
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