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
	//�Ӽ�
	State mState;					//����
	glm::mat4 mWorldTransform;		//WroldTransform ���
	glm::vec3 mPosition;			//��ġ Vector
	glm::quat mRotation;			//ȸ�� Quaternion
	float mScale;					//ũ��
	bool mRecomputeWorldTransform;	//WorldTransform ���� ����

	//Ŀ����
	std::vector<class Connecter*> mConnecters;
	//GM
	class GameMaster& mGM;

public:
	Puppet(class GameMaster& _gm);
	virtual ~Puppet();

	//����
	void Update(float _delta_time);
	void UpdateConnecters(float _delta_time);
	virtual void UpdatePuppet(float _delta_time);

	//Get/Set
	const glm::vec2& GetPosition() const { return mPosition; }
	//void SetPosition(const glm::vec2)

};