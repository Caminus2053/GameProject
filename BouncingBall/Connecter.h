#pragma once

class Connecter {
protected:
	//�� Connecter �����
	class Puppet& mUser;
	//���� �켱����
	int mUpdatePriority;

public:
	//����/�Ҹ���
	Connecter(class Puppet& _puppet, int _update_priority = 100);
	virtual ~Connecter();

	//����
	virtual void Update(float _delta_time);
	virtual void OnUpdateWorldTransform() { };

	//Get
	class Puppet& GetUser(){ return mUser; }
	int GetUpdatePriority() { return mUpdatePriority; }
};