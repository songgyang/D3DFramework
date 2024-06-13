#include "stdafx.h"
#include "Scene1.h"
#include "Player.h"
#include "Monster.h"
#include "stdafx.h"

Scene1::Scene1()
{
    

}
Scene1::~Scene1()
{
  
}

void Scene1::Init()
{
	/*Actor* Root = Actor::Create("Root");
	Root->AddChild(GameObject::Create("Child0"));
	Root->AddChild(GameObject::Create("Child1"));
	Root->DeleteObject("Child1");*/









	initCount = 0;

	sky = Sky::Create();
	sky->LoadFile("Sky.xml");

	initObject = "grid";
	grid = Grid::Create();
	initCount++;

	initObject = "cam1";
	cam1 = Camera::Create();
	cam1->LoadFile("Cam1.xml");
	initCount++;


	initObject = "Floor";
	plane = Terrain::Create();
	plane->LoadFile("Floor.xml");
	initCount++;

	initObject = "Astar";
	astar = new AStar();
	//길찾기 할 맵 대상 plane, 맵을 몇개로 나눌지
	astar->CreateNode(plane, 257);
	initCount++;

	initObject = "light";
	pointLight = Light::Create("light", 0);
	pointLight->light->color = Color(0, 0, 0);
	initCount++;

	//pointLight->light->radius = 200.0f;


	initObject = "Player";
	pl = new Player();
	pl->SetMap(plane);
	initCount++;

	initObject = "Monster";
	Vector3 spawn[3];
	spawn[0] = Vector3(-184.878f, 0.0f, 0.0f);
	spawn[1] = Vector3(-184.878f, 5.80f, 52.20f);
	spawn[2] = Vector3(-184.878f, 18.0f, 42.80f);
	for (int i = 0; i < 3; i++)
	{
		mon[i] = new Monster();
		mon[i]->Init(plane, astar, pl, spawn[i]);
	}

	initCount++;

	//LIGHT->dirLight.color = Color(0, 0, 0);
	initObject = "shadow";
	shadowTarget = new CubeRenderTarget();
	shadowTarget->ResizeScreen(2000);
	shadowTarget->shadowBias = 0.002f;

	environmentTarget = new CubeRenderTarget();
	environmentTarget->ResizeScreen(2000);


	initCount++;
	
	initObject = "Rain";
	rain = Rain::Create();
	rain->LoadFile("Rain.xml");
	rain->Play();
	
	//lock
	initCount++;
	//unlock


	sphere = Actor::Create();
	sphere->LoadFile("Sphere.xml");

	initObject = "postEffect";
	postEffect = new PostEffect();



	water = Water::Create();
	water->LoadFile("water.xml");

	initCount++;
	//postEffect->psp.filter = 1;
}

void Scene1::Release()
{
	//delete 

}

void Scene1::Update()
{
	postEffect->RenderDetail();
	//ImGui::SliderFloat("distance", &distance, 0, 500);
	//shadowTarget->RenderDetail();
	//Camera::main->ControlMainCam();
	ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());


	LIGHT->RenderDetail();

	ImGui::Begin("Hierarchy");
	grid->RenderHierarchy();
	cam1->RenderHierarchy();
	plane->RenderHierarchy();
	pointLight->RenderHierarchy();
	rain->RenderHierarchy();
	sky->RenderHierarchy();
	sphere->RenderHierarchy();
	water->RenderHierarchy();

	ImGui::End();



	cam1->Update();
	grid->Update();
	plane->Update();
	pointLight->Update();
	rain->Update();
	sky->Update();
	sphere->Update();
	for (int i = 0; i < 3; i++)
	{
		mon[i]->Update();
	}
	pl->Update();
	postEffect->Update();
	water->Update();



}

void Scene1::LateUpdate()
{
	for (int i = 0; i < 3; i++)
	{
		if (mon[i]->GetActor()->Intersect(pl->GetActor()->Find("Sword")))
		{
			if (pl->GetState() == PlayerState::ATTACK)
				mon[i]->Hit(RANDOM->Int(1, 20));
		}
	}





	for (int i = 0; i < 3; i++)
	{
		mon[i]->LateUpdate();
	}

	pl->LateUpdate();

}

void Scene1::PreRender()
{
	LIGHT->Set();
	//1 Pass
	//환경매핑
	{
		environmentTarget->SetTarget();
		environmentTarget->position = sphere->GetWorldPos();
		sky->RenderEnviroment();
		plane->RenderEnviroment();

		/*pl->RenderEnviroment();
		for (int i = 0; i < 3; i++)
		{
			mon[i]->RenderEnviroment();
		}*/
	}
	
	//물반사 그리기
	{
		water->SetReflectionTarget();

		plane->RenderWater();
		pl->RenderWater();
		for (int i = 0; i < 3; i++)
		{
			mon[i]->RenderWater();
		}
	}
	//물굴절 그리기
	{
		water->SetRefractionTarget();

		plane->RenderWater();
		pl->RenderWater();
		for (int i = 0; i < 3; i++)
		{
			mon[i]->RenderWater();
		}
	}
	
	//2Pass
	//그림자 그리기
	{
		//그려줄 타겟 설정( 타겟설정이 그림자 그리기 시작)
		shadowTarget->SetTarget();
		//그림자를 그려줄 위치
		shadowTarget->position = pl->GetWorldPos() - LIGHT->dirLight.direction * distance;
		//plane->RenderShadow();

		pl->RenderShadow();
		for (int i = 0; i < 3; i++)
		{
			mon[i]->RenderShadow();
		}
	}




	//3Pass
	//메인 게임 그리기 (postEffect에)
	{
		postEffect->SetTarget();
		Camera::main->Set();
		//false -> 알파테스트
		//true -> 알파블렌딩
		sky->Render();
		//grid->Render();
		rain->Render();

		//맵이 그려지기 전에 해당 텍스처를 바인딩
		shadowTarget->SetRGBTexture(5);
		plane->Render();

		//반사매핑이 그려지기 전에 해당 텍스처를 바인딩
		environmentTarget->SetRGBTexture(4);
		sphere->Render();

		water->Render();

		pl->Render();
		for (int i = 0; i < 3; i++)
		{
			mon[i]->Render();
		}

		

		BLEND->Set(true);
	}


	//그림자 그리기 끝
}

void Scene1::Render()
{
	//포스트 이펙트에 있는걸 그리기
	postEffect->Render();
}

void Scene1::ResizeScreen()
{
	cam1->viewport.x = 0.0f;
	cam1->viewport.y = 0.0f;
	cam1->viewport.width = App.GetWidth();
	cam1->viewport.height = App.GetHeight();
	cam1->width = App.GetWidth();
	cam1->height = App.GetHeight();
}
