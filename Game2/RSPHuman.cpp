#include "stdafx.h"
#include "RSPHuman.h"

RSPHuman::RSPHuman(bool player)
{
    actor = Actor::Create();
	if(player)
		actor->LoadFile("RSPHuman.xml");
	else
		actor->LoadFile("RSPHuman2.xml");

	RSP[0] = Actor::Create();
	RSP[0]->LoadFile("Rock.xml");
	RSP[0]->Update();

	RSP[1] = Actor::Create();
	RSP[1]->LoadFile("Scissors.xml");
	RSP[1]->Update();

	RSP[2] = Actor::Create();
	RSP[2]->LoadFile("Paper.xml");
	RSP[2]->Update();

	src = dest = 0;
	w = 1.0f;
}

void RSPHuman::Update()
{
    actor->Update();

	if (w < 1.0f)
	{
		w += DELTA;

		actor->Find("RSholder")->rotation.x += 45.0f*plus *ToRadian* DELTA;
		LerpHand(actor->Find("handRoot"));

		if (w >= 1.0f)
		{
			//출발지가 목적지로 갱신
			src = dest;
		}
	}
}

void RSPHuman::LerpHand(GameObject* node)
{
	GameObject* srcOb = RSP[src]->Find(node->name);
	GameObject* destOb = RSP[dest]->Find(node->name);

	//위치값
	Vector3 pos = Utility::Lerp(srcOb->GetLocalPos(),
		destOb->GetLocalPos(), w);
	node->SetLocalPos(pos);

	//회전값
	node->rotation = Utility::Lerp(srcOb->rotation, destOb->rotation, w);

	//내가 가진 자식 만큼
	for (auto it = node->children.begin(); it != node->children.end(); it++)
	{
		LerpHand(it->second);
	}


}

void RSPHuman::UpHand(int num)
{
	dest = num;
	w = 0.0f;
	plus = -1.0f;
}

void RSPHuman::DownHand()
{
	dest = 2;
	w = 0.0f;
	plus = 1.0f;
}

void RSPHuman::Render()
{
    actor->Render();
}

void RSPHuman::RenderHierarchy()
{
    actor->RenderHierarchy();
}
