#include "stdafx.h"
#include "RSPHuman.h"
#include "Watermelon.h"
#include "Ddg.h"
//#include "Scene1.h"
#include "LoadingScene.h"
#include "Main.h"


Main::Main()
{
	

	//투명 이미지출력
}

Main::~Main()
{
	
}
void Main::Init()
{
	SCENE->AddScene("LOADING", new LoadingScene);
	SCENE->ChangeScene("LOADING")->Init();
}

void Main::Release()
{
	SCENE->Release();
}

void Main::Update()

{
	SCENE->Update();
}


void Main::LateUpdate()
{
	SCENE->LateUpdate();
}
//메인렌더 그리기 전
void Main::PreRender()
{
	SCENE->PreRender();
}

void Main::Render()
{
	SCENE->Render();
}

void Main::ResizeScreen()
{
	SCENE->ResizeScreen();
}



int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	App.SetAppName(L"Game2");
	App.SetInstance(instance);
	WIN->Create();
	D3D->Create();
	Main* main = new Main();
	main->Init();

	int wParam = (int)WIN->Run(main);


	main->Release();
	SafeDelete(main);
	D3D->DeleteSingleton();
	WIN->DeleteSingleton();

	return wParam;
}