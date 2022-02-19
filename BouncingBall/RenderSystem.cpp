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

	//OpenGL �Ӽ� ����
	//core �������� ���
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//OpenGL ���� ���
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	//8-bits per RGBA ä�� Į�� ���� ��û
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	//���� ���۸� enable
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//�ϵ���� ���� ������ ���(�׷��� ī�� ���)
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	//������ ����
	mWindow = SDL_CreateWindow(mRealWorld.GetTitleC(), 100, 50,
		(int)(mScreenWidth), (int)(mScreenHeight), SDL_WINDOW_OPENGL);
	if (!mWindow) {
		SDL_Log("SDL create Window failed : %s", SDL_GetError());
		return false;
	}
	
	//OpenGL Context ����
	mContext = SDL_GL_CreateContext(mWindow);

	//GLEW �ʱ�ȭ
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		SDL_Log("Failed to initialize GLEW");
		return false;
	}

	//�Ϻ� �÷������� GLEW ���� �ڵ� ���� �� ����
	//�װ� Clear ����
	glGetError();

	//���̴� �ʱ�ȭ
	if (!LoadShaders()) {
		SDL_Log("Failed to load shaders");
		return false;
	}

	//��������Ʈ�� VertexArray ����
	CreateSpriteVA();

	return true;
}

void RenderSystem::CreateSpriteVA() {
	//�簢��!
	//������� : position(x, y, z), normal(x, y, z), texture(u, v)
	//��ġ ��ǥ / ���� ��ǥ / u, v�� �ؽ��� ��ǥ
	float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, //top left		0
		 0.5f, 0.5f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, //top right		1
		 0.5f,-0.5f, 0.f, 0.f, 0.f, 0.f, 1.f, 1.f, //bottom right	2
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, //bottom left	3
	};
	//�ε���
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	//VertexArray ����
	mSpriteVA = new VertexArray(vertices, 4, indices, 6);
}

bool RenderSystem::LoadShaders() {
	//Sprite ���̴� ����
	mSpriteShader = new Shader();
	if (!mSpriteShader->Load("./Shader/Sprite.vert", "./Shader/Sprite.frag"))
		return false;

	//Sprite�� view-projection ��� ���
	glm::mat4 sprite_view_projec = {
		{ 2.0f / mScreenWidth, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 2.0f / mScreenHeight, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f }
	};

	//���̴� ��� ���� �� view-projection ��� ����
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
	
	//��� ĥ�ϱ�
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//���� ���
	glEnable(GL_BLEND);
	//���İ� ����
	glBlendFunc(
		GL_SRC_ALPHA,				//srcFactor(���� �ִ� ����) = srcAlpha
		GL_ONE_MINUS_SRC_ALPHA);	//dstFactor(���� ����) = 1 - srcAlpha

	//���̴�, VertexArray Ȱ��ȭ
	mSpriteShader->Active();
	mSpriteVA->Active();

	//Sprite �׸���
	Texture* texture = mResourceSystem.GetTexture("../Assets/2DImages/Ship.png");
	if (texture) {

		//ũ�� ���(�ؽ��� ũ��)
		glm::mat4 texture_scale = {
			{ (float)(texture->GetWidth()), 0.0f, 0.0f, 0.0f },
			{ 0.0f, (float)(texture->GetHeight()), 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f }
		};

		//���� ���
		glm::mat4 world = {
			{ 1.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f }
		};
		//��� ���
		glm::mat4 result = texture_scale * world;

		//Uniform ����
		mSpriteShader->SetMat4("uWorldTransform", result);
		//�ؽ��� Ȱ��ȭ
		texture->Active();

		//�׸���!
		//�̳༮ ȣ�� ���� : VertexArray, Shader Ȱ��ȭ(���ε�) ���־����
		glDrawElements(
			GL_TRIANGLES,		//�׷��� �� ������/������Ƽ���� Ÿ��
			6,					//�ε��� ���ۿ� �ִ� �ε��� ��
			GL_UNSIGNED_INT,	//�� �ε����� Ÿ��
			nullptr);			//�� nullptr
	}

	//ȭ�� ����
	SDL_GL_SwapWindow(mWindow);
}