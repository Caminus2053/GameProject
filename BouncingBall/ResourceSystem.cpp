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
	//�ؽ��� ������
	Texture* texture = nullptr;
	//���� �ؽ��� �ֳ� Ȯ��
	auto iter = mTextures.find(fileName);
	//������ �ִ°� �ֱ�
	if (iter != mTextures.end())
		texture = iter->second;
	//������ �ε�
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
	//�ؽ��� ����
	for (auto texture : mTextures)
		delete texture.second;
	mTextures.clear();
}