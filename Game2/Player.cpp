#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	actor = Actor::Create();
	actor->LoadFile("Froggy5.xml");
	Camera::main = (Camera*)actor->Find("Cam");
	Camera::main->ResizeWindow();

	//ó�� ��ġ���� ���� ���� �Ŀ� �ʱ�ȭ
	actor->Update();
	lastPoint = actor->GetWorldPos();
	gravity = 0.0f;
	actor->anim->ChangeAnimation(AnimationState::LOOP,
		(UINT)PlayerState::IDLE, 0.05f);


	slash = new SlashTrail();
	slash->Bottom = actor->Find("SwordStart");
	slash->Top = actor->Find("SwordEnd");
	slash->interval = 0.03f;
	slash->material->LoadFile("Slash.mtl");
}

Player::~Player()
{
}

void Player::Update()
{
	slash->RenderDetail();
	actor->RenderHierarchy();
	
	if (INPUT->KeyDown('L'))
	{
		((Rain*)actor->Find("LevelUp"))->Play();
	}



	//{
	//	//��Ŭ��������
	//	if (INPUT->KeyPress(VK_RBUTTON))
	//	{
	//		Ray CamRay = Utility::MouseToRay();
	//		Vector3 Hit;
	//		//if (Utility::RayIntersectTri(CamRay, plane, Hit))
	//		//�׷���ī�带���� ���Ŀ������Ͽ� �������� ����
	//		if (plane->ComPutePicking(CamRay, Hit))
	//		{
	//			//actor->SetWorldPos(Hit);
	//			//actor->Update();

	//			//�����
	//			srcPos = actor->GetWorldPos();
	//			//������
	//			destPos = Hit;
	//			//���̰��� �������� ���
	//			srcPos.y = 0.0f;
	//			destPos.y = 0.0f;

	//			lerpPos = 0.0f;
	//			Vector3 dis = destPos - srcPos;
	//			disPos = dis.Length();

	//			/*srcRot = Utility::NormalizeAngle( actor->Find("frogman")->rotation.y);
	//			destRot = Utility::NormalizeAngle(PI + atan2f(dis.x, dis.z));
	//			lerpRot = 0.0f;
	//			disRot = abs(srcRot - destRot);
	//			if (disRot > PI)
	//			{
	//				disRot = PI * 2.0f - disRot;
	//			}*/
	//		}
	//	}

	//	if (lerpPos < 1.0f)
	//	{
	//		lerpPos += DELTA * 10.0f / disPos;
	//		Vector3 mov = Utility::Lerp(srcPos, destPos, lerpPos);
	//		actor->SetWorldPosX(mov.x);
	//		actor->SetWorldPosZ(mov.z);

	//	}
	//	/*if (lerpRot < 1.0f)
	//	{
	//		lerpRot += DELTA * PI / disRot;

	//		actor->Find("frogman")->rotation.y
	//			= Utility::LerpAngle(srcRot, destRot, lerpRot);
	//	}*/
	//}

	//actor->Update();

	keyDown = false;
	//4���� ������,ȸ��
	if (INPUT->KeyPress('W'))
	{
		actor->MoveWorldPos(actor->Find("OffsetCam")->GetForward() * 10.0f * DELTA);

		actor->Find("RootNode")->rotation.y =
			Utility::LerpAngle(actor->Find("RootNode")->rotation.y,
				actor->Find("OffsetCam")->rotation.y, 0.03f);
		keyDown = true;
	}
	else if (INPUT->KeyPress('S'))
	{
		actor->MoveWorldPos(-actor->Find("OffsetCam")->GetForward() * 10.0f * DELTA);
		actor->Find("RootNode")->rotation.y =
			Utility::LerpAngle(actor->Find("RootNode")->rotation.y,
				actor->Find("OffsetCam")->rotation.y - PI, 0.03f);
		keyDown = true;
	}
	if (INPUT->KeyPress('A'))
	{
		actor->MoveWorldPos(-actor->Find("OffsetCam")->GetRight() * 10.0f * DELTA);

		actor->Find("RootNode")->rotation.y =
			Utility::LerpAngle(actor->Find("RootNode")->rotation.y,
				actor->Find("OffsetCam")->rotation.y - PI * 0.5f, 0.03f);
		keyDown = true;
	}
	else if (INPUT->KeyPress('D'))
	{
		actor->MoveWorldPos(actor->Find("OffsetCam")->GetRight() * 10.0f * DELTA);

		actor->Find("RootNode")->rotation.y =
			Utility::LerpAngle(actor->Find("RootNode")->rotation.y,
				actor->Find("OffsetCam")->rotation.y + PI * 0.5f, 0.03f);
		keyDown = true;
	}
	if (INPUT->GetHideMouse())
	{
		Vector3 Rot;
		Rot.x = INPUT->movePosition.y * 0.001f;
		Rot.y = INPUT->movePosition.x * 0.001f;
		actor->Find("OffsetCam")->rotation.y += Rot.y;
		actor->Find("OffsetCam")->rotation.x += Rot.x;
	}
	if (INPUT->KeyPress(VK_RBUTTON) and INPUT->GetHideMouse() == false)
	{
		Vector3 Rot;
		Rot.x = INPUT->movePosition.y * 0.001f;
		Rot.y = INPUT->movePosition.x * 0.001f;
		actor->Find("OffsetCam")->rotation.y += Rot.y;
		actor->Find("OffsetCam")->rotation.x += Rot.x;
	}
	if (INPUT->KeyDown(VK_SPACE)and
		(state < PlayerState::JUMPUP))
	{
		isFalling = true;
		gravity = -24.0f;
	}
	
	if (isFalling)
	{
		actor->MoveWorldPos(Vector3(0, -1, 0) * gravity * DELTA);
		gravity += 30.0f * DELTA;
		//cout << "�߷�������" << gravity << endl;
	}

	actor->Update();
	slash->Update();

	if (state == PlayerState::IDLE)
	{
		if (INPUT->KeyPress('1'))
		{
			state = PlayerState::JUMPATTACK;
			actor->anim->ChangeAnimation(AnimationState::ONCE_LAST,
				(UINT)PlayerState::JUMPATTACK, 0.1f);
			actor->Find("mixamorig:Hips")->rootMotion = true;
		}

		if (INPUT->KeyPress(VK_LBUTTON))
		{
			state = PlayerState::ATTACK;
			actor->anim->ChangeAnimation(AnimationState::ONCE_LAST,
				(UINT)PlayerState::ATTACK, 0.1f);

			damageText.Add(WorldText(L"ATTACK!", actor->GetWorldPos() +
				Vector3(0, 7, 0), 5.0f, TextType_ANI | TextType_UP, 3.0f,Color(1,1,0)));
		}
		if (INPUT->KeyPress(VK_SPACE))
		{
			state = PlayerState::JUMPUP;
			actor->anim->ChangeAnimation(AnimationState::ONCE_LAST,
				(UINT)PlayerState::JUMPUP, 0.1f);
		}
		if (keyDown == true)
		{
			state = PlayerState::WALK;
			actor->anim->ChangeAnimation(AnimationState::LOOP,
				(UINT)PlayerState::WALK, 0.1f);
		}
	}
	else if (state == PlayerState::JUMPATTACK)
	{
		actor->MoveWorldPos(actor->Find("OffsetCam")->GetForward() * 10.0f * DELTA);

		if (actor->anim->GetPlayTime() > 0.95f)
		{
			state = PlayerState::IDLE;
			actor->anim->ChangeAnimation(AnimationState::LOOP,
				(UINT)PlayerState::IDLE, 0.0f);
			actor->Find("mixamorig:Hips")->rootMotion = false;
		}

	}
	else if (state == PlayerState::WALK)
	{
		if (INPUT->KeyPress(VK_LBUTTON))
		{
			state = PlayerState::ATTACK;
			actor->anim->ChangeAnimation(AnimationState::ONCE_LAST,
				(UINT)PlayerState::ATTACK, 0.1f);
		}
		if (INPUT->KeyPress(VK_SPACE))
		{
			state = PlayerState::JUMPUP;
			actor->anim->ChangeAnimation(AnimationState::ONCE_LAST,
				(UINT)PlayerState::JUMPUP, 0.1f);
		}
		if (keyDown == false)
		{
			state = PlayerState::IDLE;
			actor->anim->ChangeAnimation(AnimationState::LOOP,
				(UINT)PlayerState::IDLE, 0.1f);
		}
	}
	else if (state == PlayerState::JUMPUP)
	{
		actor->anim->aniScale = 2.0f;
		if (not isFalling)
		{
			state = PlayerState::JUMPDOWN;
			actor->anim->ChangeAnimation(AnimationState::ONCE_LAST,
				(UINT)PlayerState::JUMPDOWN, 0.1f);
		}
	}
	else if (state == PlayerState::JUMPDOWN)
	{
		actor->anim->aniScale = 2.5f;
		if (actor->anim->GetPlayTime() > 0.5f)
		{
			state = PlayerState::IDLE;
			actor->anim->ChangeAnimation(AnimationState::LOOP,
				(UINT)PlayerState::IDLE, 0.1f);
			actor->anim->aniScale = 1.0f;
		}
	}
	else if (state == PlayerState::ATTACK)
	{
		if (actor->anim->GetPlayTime() > 0.37f)
		{
			if(not slash->isPlaying)
			slash->Play();
		}

		if (actor->anim->GetPlayTime() > 0.7f)
		{
			if (slash->isPlaying)
				slash->Stop();
		}

		if (actor->anim->GetPlayTime() > 0.9f)
		{

			state = PlayerState::IDLE;
			actor->anim->ChangeAnimation(AnimationState::ONCE_LAST,
				(UINT)PlayerState::IDLE, 0.1f);
		}
	}
	damageText.Update();
}

void Player::LateUpdate()
{
	//ĳ���Ͱ� �ʰ� �ε����� ����
	Ray SphereRay;
	SphereRay.position = actor->GetWorldPos() + Vector3(0, 100, 0);
	SphereRay.direction = Vector3(0, -1, 0);
	Vector3 Hit;
	if (Utility::RayIntersectMap(SphereRay, plane, Hit))
	{
		//���� ���� ������
		if (Hit.y < actor->GetWorldPos().y)
		{
			isFalling = true;
			//cout << "����������" << endl;
		}
		//���� ���� ������
		else
		{
			isFalling = false;
			gravity = 0.0f;
			actor->SetWorldPosY(Hit.y);
			//cout << "�پ��ִ���" << endl;
		}


		actor->Update();
	}





	//�������̰� ���̳��� ���ư���
	/*if (gravity >= 0.0f)
	{
		float currentY = actor->GetWorldPos().y;
		float lastY = lastPoint.y;
		if (currentY - lastY > (10.0f * DELTA))
		{
			actor->SetWorldPos(lastPoint);
			actor->Update();
		}
	}*/
	







}

void Player::Render()
{
	//BLEND->Set(true);
	actor->Render();
	//BLEND->Set(false);
	slash->Render();
	lastPoint = actor->GetWorldPos();
	damageText.Render();
}

void Player::RenderShadow()
{
	actor->RenderShadow();
}

void Player::RenderEnviroment()
{
	actor->RenderEnviroment();
}

void Player::RenderWater()
{
	actor->RenderWater();
}
