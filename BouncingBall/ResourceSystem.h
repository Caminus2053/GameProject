#pragma once
#include <unordered_map>

class ResourceSystem {
private:
	//����
	class RealWorld& mRealWorld;

	//�ڿ� map
	std::unordered_map<std::string, class Texture*> mTextures;
	std::unordered_map<std::string, class Mesh*> mMeshses;

public:
	//������
	ResourceSystem(class RealWorld& _real_world);
	~ResourceSystem();

	//����
	void Destroy();

	//Get
	class Texture* GetTexture(const std::string& fileName);
	class Mesh* GetMesh(const std::string& fileName);
};