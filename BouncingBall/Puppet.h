#pragma once
#include <GLM/mat4x4.hpp>
#include <GLM/vec3.hpp>
#include <GLM/ext/quaternion_float.hpp>
#include <vector>

class Puppet {
public:
	enum class State
	{
		Alive,
		Paused,
		Dead
	};

private:
	//속성
	State mState;					//상태
	glm::mat4 mWorldTransform;		//WroldTransform 행렬
	glm::vec3 mPosition;			//위치 Vector
	glm::quat mRotation;			//회전 Quaternion
	float mScale;					//크기
	bool mRecomputeWorldTransform;	//WorldTransform 재계산 여부

	//커넥터
	std::vector<class Connecter*> mConnecters;
	//GM
	class GameMaster& mGM;

public:
	Puppet(class GameMaster& _gm);
	virtual ~Puppet();

	//갱신
	void Update(float _delta_time);
	void UpdateConnecters(float _delta_time);
	virtual void UpdatePuppet(float _delta_time);

	//Get/Set
	const glm::vec2& GetPosition() const { return mPosition; }
	//void SetPosition(const glm::vec2)

};