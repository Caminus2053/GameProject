#include "ResourceSystem.h"
#include "RealWorld.h"
#include "Texture.h"

ResourceSystem::ResourceSystem(RealWorld& _real_world):
	mRealWorld(_real_world)
{

}
ResourceSystem::~ResourceSystem() {
	Destroy();
}

Texture* ResourceSystem::GetTexture(const std::string& fileName) {
	//텍스쳐 생성용
	Texture* texture = nullptr;
	//먼저 텍스쳐 있나 확인
	auto iter = mTextures.find(fileName);
	//있으면 있는거 주기
	if (iter != mTextures.end())
		texture = iter->second;
	//없으면 로드
	else {
		texture = new Texture();
		if (texture->Load(fileName))
			mTextures.emplace(fileName, texture);
		else {
			delete texture;
			texture = nullptr;
		}
	}

	return texture;
}
Mesh* ResourceSystem::GetMesh(const std::string& fileName) {
	return nullptr;
}

void ResourceSystem::Destroy() {
	//텍스쳐 제거
	for (auto texture : mTextures)
		delete texture.second;
	mTextures.clear();
}