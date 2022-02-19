#pragma once
#include <vector>
#include <string>

class RealWorld {
private:
	//����
	std::string mTitle;

	//�ʱ�ȭ ����
	bool mInit = false;

	//���ҽ� ���
	class ResourceSystem* mResourceSystem;
	//������ ���
	class RenderSystem* mRenderSystem;

	//std::vector<class SpriteConnecterR*> mSpriteConnecters;
	//std::vector<class MeshConnecterR*> mMeshConnecters;

public:
	//����/�Ҹ���
	RealWorld(std::string _title);
	~RealWorld();

	//�ʱ�ȭ/�ı�
	bool Initialize();
	void Destroy();

	//�׸���
	void Draw();

	//Get
	std::string GetTitle() const { return mTitle; }
	const char* GetTitleC() const { return mTitle.c_str(); }

	class ResourceSystem& GetResourceSystem() { return *mResourceSystem; }
	class RenderSystem& GetRenderSystem() { return *mRenderSystem; }

	/*void AddSpriteConnecter(class SpriteConnecterR* _sprite_conn);
	void RemoveSpriteConnecter(class SpriteConnecterR* _sprite_conn);

	void AddMeshConnecter(class MeshConnecterR* _mesh_conn);
	void RemoveMeshConnecter(class MeshConnecterR* _mesh_conn);*/
};