#include "stdafx.h"
#include "LoadingScene.h"
#include "Scene1.h"

int initCount = 0;
string initObject = " ";


//�����忡�� ���۽�ų �Լ�
void LoadScene1()
{
	SCENE->AddScene("SC1", new Scene1);
	SCENE->GetScene("SC1")->Init();
}





LoadingScene::LoadingScene()
{
}

LoadingScene::~LoadingScene()
{
}

void LoadingScene::Init()
{
	cam = Camera::Create();
	cam->LoadFile("Cam1.xml");
	Camera::main = cam;

	ui = UI::Create();
	ui->LoadFile("UI.xml");

	cam->ResizeScreen();
	
	//���� ����
	t1 = new thread(LoadScene1);

}

void LoadingScene::Release()
{
}

void LoadingScene::Update()
{
	ImGui::Begin("Hierarchy");
	ui->RenderHierarchy();
	ImGui::End();

	ui->Update();
	cam->Update();

	ui->Find("Gauge")->scale.x = initCount / 10.0f;


	if (initCount == 10)
	{
		SCENE->ChangeScene("SC1");
		//�ش� �����带 ����
		t1->join();
		delete t1;
	}


}

void LoadingScene::LateUpdate()
{
}

void LoadingScene::PreRender()
{
}

void LoadingScene::Render()
{
	wstring str = Utility::ToWString(initObject);

	DWRITE->RenderText(str, RECT{ 0,0,800,800 }, 40,L"����ü",Color(1,0,0,1));
	Camera::main->Set();
	ui->Render();
}

void LoadingScene::ResizeScreen()
{
}
