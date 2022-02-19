#pragma once
#include <unordered_map>

class ResourceSystem {
private:
	//참조
	class RealWorld& mRealWorld;

	//자원 map
	std::unordered_map<std::string, class Texture*> mTextures;
	std::unordered_map<std::string, class Mesh*> mMeshses;

public:
	//생성자
	ResourceSystem(class RealWorld& _real_world);
	~ResourceSystem();

	//제거
	void Destroy();

	//Get
	class Texture* GetTexture(const std::string& fileName);
	class Mesh* GetMesh(const std::string& fileName);
};