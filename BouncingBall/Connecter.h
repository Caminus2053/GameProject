#pragma once

class Connecter {
protected:
	//이 Connecter 사용자
	class Puppet& mUser;
	//갱신 우선순위
	int mUpdatePriority;

public:
	//생성/소멸자
	Connecter(class Puppet& _puppet, int _update_priority = 100);
	virtual ~Connecter();

	//갱신
	virtual void Update(float _delta_time);
	virtual void OnUpdateWorldTransform() { };

	//Get
	class Puppet& GetUser(){ return mUser; }
	int GetUpdatePriority() { return mUpdatePriority; }
};