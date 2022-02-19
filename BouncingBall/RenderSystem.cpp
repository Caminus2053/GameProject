#include "RenderSystem.h"
#include "RealWorld.h"
#include "ResourceSystem.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"
#include <GLM/gtx/string_cast.hpp>

RenderSystem::RenderSystem(RealWorld& _real_world) :
	mRealWorld(_real_world),
	mResourceSystem(_real_world.GetResourceSystem()),
	mSpriteShader(nullptr), //mMeshShader(nullptr),
	mSpriteVA(nullptr),
	mView(), mProjection(),
	mScreenWidth(0.0f), mScreenHeight(0.0f),
	mAmbientLight(), mDirLight(),
	mWindow(nullptr), mContext()
{

}

bool RenderSystem::Initialize(float _screen_width, float _screen_height) {
	mScreenWidth = _screen_width;
	mScreenHeight = _screen_height;

	//OpenGL 속성 설정
	//core 프로파일 사용
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//OpenGL 버전 명시
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	//8-bits per RGBA 채널 칼라 버퍼 요청
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	//더블 버퍼링 enable
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//하드웨어 가속 강제로 사용(그래픽 카드 사용)
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	//윈도우 생성
	mWindow = SDL_CreateWindow(mRealWorld.GetTitleC(), 100, 50,
		(int)(mScreenWidth), (int)(mScreenHeight), SDL_WINDOW_OPENGL);
	if (!mWindow) {
		SDL_Log("SDL create Window failed : %s", SDL_GetError());
		return false;
	}
	
	//OpenGL Context 생성
	mContext = SDL_GL_CreateContext(mWindow);

	//GLEW 초기화
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		SDL_Log("Failed to initialize GLEW");
		return false;
	}

	//일부 플랫폼에서 GLEW 에러 코드 생길 수 잇음
	//그걸 Clear 해줌
	glGetError();

	//쉐이더 초기화
	if (!LoadShaders()) {
		SDL_Log("Failed to load shaders");
		return false;
	}

	//스프라이트용 VertexArray 생성
	CreateSpriteVA();

	return true;
}

void RenderSystem::CreateSpriteVA() {
	//사각형!
	//순서대로 : position(x, y, z), normal(x, y, z), texture(u, v)
	//위치 좌표 / 법선 좌표 / u, v는 텍스쳐 좌표
	float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, //top left		0
		 0.5f, 0.5f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, //top right		1
		 0.5f,-0.5f, 0.f, 0.f, 0.f, 0.f, 1.f, 1.f, //bottom right	2
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, //bottom left	3
	};
	//인덱스
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	//VertexArray 생성
	mSpriteVA = new VertexArray(vertices, 4, indices, 6);
}

bool RenderSystem::LoadShaders() {
	//Sprite 쉐이더 생성
	mSpriteShader = new Shader();
	if (!mSpriteShader->Load("./Shader/Sprite.vert", "./Shader/Sprite.frag"))
		return false;

	//Sprite용 view-projection 행렬 계산
	glm::mat4 sprite_view_projec = {
		{ 2.0f / mScreenWidth, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 2.0f / mScreenHeight, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f }
	};

	//쉐이더 사용 설정 및 view-projection 행렬 설정
	mSpriteShader->Active();
	mSpriteShader->SetMat4("uViewProjection", sprite_view_projec);

	return true;
}

void RenderSystem::Destroy() {
	delete mSpriteVA;
	delete mSpriteShader;
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void RenderSystem::Draw() {
	
	//배경 칠하기
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//블랜드 허용
	glEnable(GL_BLEND);
	//알파값 지정
	glBlendFunc(
		GL_SRC_ALPHA,				//srcFactor(새로 넣는 색상꺼) = srcAlpha
		GL_ONE_MINUS_SRC_ALPHA);	//dstFactor(원래 색상꺼) = 1 - srcAlpha

	//쉐이더, VertexArray 활성화
	mSpriteShader->Active();
	mSpriteVA->Active();

	//Sprite 그리기
	Texture* texture = mResourceSystem.GetTexture("../Assets/2DImages/Ship.png");
	if (texture) {

		//크기 행렬(텍스쳐 크기)
		glm::mat4 texture_scale = {
			{ (float)(texture->GetWidth()), 0.0f, 0.0f, 0.0f },
			{ 0.0f, (float)(texture->GetHeight()), 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f }
		};

		//월드 행렬
		glm::mat4 world = {
			{ 1.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f }
		};
		//결과 행렬
		glm::mat4 result = texture_scale * world;

		//Uniform 설정
		mSpriteShader->SetMat4("uWorldTransform", result);
		//텍스쳐 활성화
		texture->Active();

		//그리기!
		//이녀석 호출 조건 : VertexArray, Shader 활성화(바인딩) 되있어야함
		glDrawElements(
			GL_TRIANGLES,		//그려야 할 폴리곤/프리미티브의 타입
			6,					//인덱스 버퍼에 있는 인덱스 수
			GL_UNSIGNED_INT,	//각 인덱스의 타입
			nullptr);			//걍 nullptr
	}

	//화면 갱신
	SDL_GL_SwapWindow(mWindow);
}