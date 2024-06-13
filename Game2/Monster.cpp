#include "stdafx.h"
#include "Monster.h"
#include "Player.h"

Monster::Monster()
{
	actor = Actor::Create();
	actor->LoadFile("Froggy4.xml");
	actor->anim->ChangeAnimation(AnimationState::LOOP, (int)MonsterState::IDLE, 0.01f);
	
}

Monster::~Monster()
{
}

void Monster::Update()
{
	actor->RenderHierarchy();
	//플레이어와의 거리
	Vector3 PlayerDis = pl->GetWorldPos() - actor->GetWorldPos();
	//스폰지점과의 거리
	Vector3 SpawnDis = pl->GetWorldPos() - spawnPoint;

	if (state == MonsterState::IDLE)
	{

		//idle-> walk
		if (SpawnDis.Length() < 150.0f)
		{
			state = MonsterState::WALK;
			actor->anim->ChangeAnimation(AnimationState::LOOP, (int)MonsterState::WALK, 0.01f);
		}
	}
	else if (state == MonsterState::WALK)
	{
		if (TIMER->GetTick(refreshTime, 0.2f))
		{
			int sourX, sourZ;
			if (not astar->GetNearNode(actor->GetWorldPos(), sourX, sourZ))
			{
				way.clear();
				way.push_back(spawnPoint);
				lerpPos = 0.0f;
			}
			else if (astar->PathFinding(actor->GetWorldPos(), pl->GetWorldPos(), way))
			{
				InitLerp(way.back());
				way.pop_back();
			}
		}


		//walk-> idle
		if (SpawnDis.Length() > 150.0f)
		{
			state = MonsterState::COMBACK;
			actor->anim->ChangeAnimation(AnimationState::LOOP, (int)MonsterState::WALK, 0.01f);
			if (astar->PathFinding(actor->GetWorldPos(), spawnPoint, way))
			{
				InitLerp(way.back());
				way.pop_back();
			}
		}
		//walk->attack
		else if (PlayerDis.Length() < 8.0f)
		{
			way.clear();
			lerpPos = 0.0f;
			state = MonsterState::ATTACK;
			actor->anim->ChangeAnimation(AnimationState::LOOP, (int)MonsterState::ATTACK, 0.01f);
		}
	}
	else if (state == MonsterState::ATTACK)
	{
		actor->Find("RootNode")->rotation.y = 
			Utility::NormalizeAngle(atan2f(PlayerDis.x, PlayerDis.z));




		if (PlayerDis.Length() > 10.0f)
		{
			state = MonsterState::WALK;
			actor->anim->ChangeAnimation(AnimationState::LOOP, (int)MonsterState::WALK, 0.01f);

		}
	}
	else if (state == MonsterState::COMBACK)
	{

		if (way.size() == 0)
		{
			state = MonsterState::IDLE;
			actor->anim->ChangeAnimation(AnimationState::LOOP, (int)MonsterState::IDLE, 0.01f);

		}
	}

	if (lerpPos < 1.0f)
	{
		lerpPos += DELTA * 10.0f / disPos;
		Vector3 mov = Utility::Lerp(srcPos, destPos, lerpPos);
		actor->SetWorldPos(mov);
		if (lerpPos >= 1.0f)
		{
			if (way.size() > 0)
			{
				InitLerp(way.back());
				way.pop_back();
			}
		}
	}
	
	if (lerpRot < 1.0f)
	{
		lerpRot += DELTA * PI / disRot;

		actor->Find("RootNode")->rotation.y
			= Utility::LerpAngle(srcRot, destRot, lerpRot);
	}

	if (damaging > 0.0f)
	{
		damaging -= DELTA;
		actor->Find("Alpha_Surface")->material->emissive.x = RANDOM->Float();
		if (damaging < 0.0f)
		{
			actor->Find("Alpha_Surface")->material->emissive.x = 0.0f;
		}
	}

	damageText.TextList.begin()->worldPos = actor->GetWorldPos() + Vector3(0.0f, 6.3f, 0);
	float dis = Utility::GetCamDistance(damageText.TextList.begin()->worldPos);

	damageText.TextList.begin()->size = Utility::Saturate(400.0f / dis, 1.0f, 400.0f);

	//damageText.TextList[0].size = 30.0f;

	actor->Update();
	damageText.Update();
}

void Monster::LateUpdate()
{
	

	

}

void Monster::Render()
{
	actor->Render();
	damageText.Render();
}
void Monster::RenderShadow()
{
	actor->RenderShadow();
}
void Monster::RenderEnviroment()
{
	actor->RenderEnviroment();
}
void Monster::RenderWater()
{
	actor->RenderWater();
}
void Monster::Hit(int damage)
{
	if (damaging > 0.0f) return;

	hp -= damage;
	if (hp < 0)hp = 0;
	actor->Find("HPFront")->scale.x = 3.7f * ((float)hp / 100.0f);
	damaging = 1.3f;
	damageText.Add(WorldText(to_wstring(damage), actor->GetWorldPos() +
		Vector3(0, 7, 0), 2, TextType_UP, 100));
	((Pop*)actor->Find("Damage"))->Play();
}
void Monster::InitLerp(Vector3 Dest)
{
	//출발지
	srcPos = actor->GetWorldPos();
	//도착지
	destPos = Dest;
	//높이값은 배제한후 사용
	//srcPos.y = 0.0f;
	//destPos.y = 0.0f;

	lerpPos = 0.0f;
	Vector3 dis = destPos - srcPos;
	disPos = dis.Length();


	srcRot = Utility::NormalizeAngle( actor->Find("RootNode")->rotation.y);
	destRot = Utility::NormalizeAngle(atan2f(dis.x, dis.z));
	lerpRot = 0.0f;
	disRot = abs(srcRot - destRot);
	if (disRot > PI)
	{
		disRot = PI * 2.0f - disRot;
	}


}

void Monster::Init(Terrain* target1, AStar* target2, Player* pl, Vector3 SpawnPoint)
{
	plane = target1;
	astar = target2;
	this->pl = pl;
	actor->SetWorldPos(SpawnPoint);
	spawnPoint = SpawnPoint;

	actor->Update();

	damageText.Add(WorldText(L"Froggy4", actor->GetWorldPos(), 
		FLT_MAX, 0 , 0 ,Color(1, 1, 1), 40.0f));
}
