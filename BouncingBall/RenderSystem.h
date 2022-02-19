#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

struct DirectionalLight {
	glm::vec3 mDirection;		//방향
	glm::vec3 mDiffuseColor;	//Diffuse = 난반사 = 표면에 나오는 빛 색
	glm::vec3 mSpecColor;		//Specular = 정반사 = 광택 색
};

class RenderSystem {
private:
	//관리자
	class RealWorld& mRealWorld;

	//리소스 관리
	//여기서 텍스쳐, 메쉬, 사운드 등 로드 및 캐싱
	class ResourceSystem& mResourceSystem;
	
	//쉐이더
	class Shader* mSpriteShader;
	//class Shader* mMeshShader;

	//VertexArray
	class VertexArray* mSpriteVA;

	//View, Projection 행렬
	glm::mat4 mView;
	glm::mat4 mProjection;

	//화면 크기
	float mScreenWidth, mScreenHeight;

	//전역 빛
	glm::vec3 mAmbientLight;
	DirectionalLight mDirLight;

	//창, GLContext
	SDL_Window* mWindow;
	SDL_GLContext mContext;

	//class GBuffer* mGBuffer;
	//class Shader* mGBasicShader;

	//초기화용
	void CreateSpriteVA();
	bool LoadShaders();

	/*void Draw3DScene(unsigned int _framebuffer, const glm::mat4x4 _view,
		const glm::mat4x4 _proj, float _view_port_scale = 1.0f, bool _lit = true);
	void DrawGBuffer();*/

	

	//void SetLightUniforms(class Shader& shader, const glm::mat4x4& view);

public:
	RenderSystem(class RealWorld& _real_world);

	bool Initialize(float _screen_width, float _screen_height);
	void Destroy();

	void Draw();

	void SetViewMatrix(const glm::mat4x4& _view) { 
		mView = _view; 
	}
	void SetAbientLight(const glm::vec3& _ambient) {
		mAmbientLight = _ambient;
	}

	/*glm::vec3 Unproject(const glm::vec3& _screen_point) const;
	void GetScreenDirection(glm::vec3& _out_start, glm::vec3& _out_dir) const;*/

	float GetScreenWidth() const { return mScreenWidth; }
	float GetScreenHeight() const { return mScreenHeight; }

	//class GBuffer* GetGBuffer() { return mGBuffer; }
};