#pragma once
#include <vector>
#include <string>

class RealWorld {
private:
	//제목
	std::string mTitle;

	//초기화 여부
	bool mInit = false;

	//리소스 담당
	class ResourceSystem* mResourceSystem;
	//랜더링 담당
	class RenderSystem* mRenderSystem;

	//std::vector<class SpriteConnecterR*> mSpriteConnecters;
	//std::vector<class MeshConnecterR*> mMeshConnecters;

public:
	//생성/소멸자
	RealWorld(std::string _title);
	~RealWorld();

	//초기화/파괴
	bool Initialize();
	void Destroy();

	//그리기
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