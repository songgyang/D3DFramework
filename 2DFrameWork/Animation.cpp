#include "framework.h"

Animation::Animation()
{
	frameMax = 0;
	boneMax = 0;
	tickPerSecond = 0;
	arrFrameBone = nullptr;
	file = "";
}

Animation::~Animation()
{
	for (UINT i = 0; i < frameMax; i++)
	{
		delete[] arrFrameBone[i];
	}
	delete[] arrFrameBone;
}


bool Animation::LoadFile(string file)
{
	this->file = file;
	
	wstring path = L"../Contents/Animation/" + Utility::ToWString(file);


	if (not PathFileExists(path.c_str()))
	{
		return false;
	}
	BinaryReader in;
	in.Open(path);

	frameMax = in.Int();
	boneMax = in.Int();
	tickPerSecond = in.Float();

	arrFrameBone = new Matrix * [frameMax];
	for (UINT i = 0; i < frameMax; i++)
	{
		arrFrameBone[i] = new Matrix[boneMax];
	}

	for (UINT i = 0; i < frameMax; i++)
	{
		for (UINT j = 0; j < boneMax; j++)
		{
			arrFrameBone[i][j] = in.matrix();
		}
	}
	in.Close();
	return true;
}

void Animation::SaveFile(string file)
{
	this->file = file;
	BinaryWriter out;
	wstring path = L"../Contents/Animation/" + Utility::ToWString(file);
	out.Open(path);

	out.Int(frameMax);
	out.Int(boneMax);
	out.Float(tickPerSecond);

	for (UINT i = 0; i < frameMax; i++)
	{
		for (UINT j = 0; j < boneMax; j++)
		{
			out.matrix(arrFrameBone[i][j]);
		}
	}
	out.Close();
}

void Animations::AnimatorUpdate(Animator& Animator)
{
	if (playList.empty()) return;

	if (Animator.animState == AnimationState::LOOP)
	{
		Animator.frameWeight += DELTA * playList[Animator.animIdx]->tickPerSecond * aniScale;
		if (Animator.frameWeight >= 1.0f)
		{
			Animator.frameWeight = 0.0f;
			Animator.currentFrame++;
			Animator.nextFrame++;
			if (Animator.nextFrame >= playList[Animator.animIdx]->frameMax)
			{
				Animator.currentFrame = 0;
				Animator.nextFrame = 1;
			}
		}
	}
	else if (Animator.animState >= AnimationState::ONCE_LAST)
	{
		Animator.frameWeight += DELTA * playList[Animator.animIdx]->tickPerSecond * aniScale;
		if (Animator.frameWeight >= 1.0f)
		{
			Animator.frameWeight = 0.0f;
			Animator.currentFrame++;
			Animator.nextFrame++;
			if (Animator.nextFrame >= playList[Animator.animIdx]->frameMax)
			{
				if (Animator.animState == AnimationState::ONCE_LAST)
				{
					Animator.currentFrame--;
					Animator.nextFrame--;
				}
				else
				{
					Animator.currentFrame = 0;
					Animator.nextFrame = 1;
				}
				
				Animator.animState = AnimationState::STOP;
			}
		}
	}
}

Animations::Animations()
{
	isChanging = false;
}

Animations::~Animations()
{
	for (int i = 0; i < playList.size(); i++)
	{
		SafeReset(playList[i]);
	}
}

void Animations::Update()
{
	if (playList.empty()) return;

	if (isChanging)
	{
		AnimatorUpdate(nextAnimator);
		Changedtime += DELTA;
		if (Changedtime >= blendtime)
		{
			Changedtime = 0.0f;
			//�����ִϸ��̼��� ����ִϸ��̼����� �ٲ۴�.
			currentAnimator = nextAnimator;
			isChanging = false;
		}
	}

	AnimatorUpdate(currentAnimator);
}

Matrix Animations::GetFrameBone(int boneIndex)
{
	if (playList.empty())  return Matrix();
	
	/*return playList[currentAnimator.animIdx]->arrFrameBone[currentAnimator.nextFrame][boneIndex]
		* currentAnimator.frameWeight +
		playList[currentAnimator.animIdx]->arrFrameBone[currentAnimator.currentFrame][boneIndex]
		* (1.0f - currentAnimator.frameWeight);*/

	if (isChanging)
	{
		return
			playList[currentAnimator.animIdx]->arrFrameBone[currentAnimator.nextFrame][boneIndex]
			* (1.0f - Changedtime / blendtime)
			+
			(playList[nextAnimator.animIdx]->arrFrameBone[nextAnimator.nextFrame][boneIndex]
				* nextAnimator.frameWeight +
				playList[nextAnimator.animIdx]->arrFrameBone[nextAnimator.currentFrame][boneIndex]
				* (1.0f - nextAnimator.frameWeight)) * (Changedtime / blendtime);
	}

	return playList[currentAnimator.animIdx]->arrFrameBone[currentAnimator.nextFrame][boneIndex]
		* currentAnimator.frameWeight +
		playList[currentAnimator.animIdx]->arrFrameBone[currentAnimator.currentFrame][boneIndex]
		* (1.0f - currentAnimator.frameWeight);
	/*return
		playList[currentAnimator.animIdx]->arrFrameBone[currentAnimator.currentFrame][boneIndex];*/
}

void Animations::ChangeAnimation(AnimationState state, UINT idx, float blendtime)
{
	if (blendtime == 0.0f)
	{
		currentAnimator.animState = state;
		this->blendtime = blendtime;
		currentAnimator.animIdx = idx;
		currentAnimator.currentFrame = 0;
		currentAnimator.nextFrame = 1;
		isChanging = false;
		return;
	}

	Changedtime = 0.0f;

	isChanging = true;

	//currentAnimator.animState = AnimationState::STOP;
	nextAnimator.animState = state;
	this->blendtime = blendtime;
	nextAnimator.animIdx = idx;
	nextAnimator.currentFrame = 0;
	nextAnimator.nextFrame = 1;
}

void Animations::RenderDetail()
{

	if (GUI->FileImGui("AnimationLoad", "AnimationLoad",
		".anim", "../Contents/Animation"))
	{
		string path = ImGuiFileDialog::Instance()->GetCurrentPath();
		Utility::Replace(&path, "\\", "/");
		if (path.find("/Animation/") != -1)
		{
			size_t tok = path.find("/Animation/") + 11;
			path = path.substr(tok, path.length())
				+ "/" + ImGuiFileDialog::Instance()->GetCurrentFileName();
		}
		else
		{
			path = ImGuiFileDialog::Instance()->GetCurrentFileName();
		}
		playList.push_back(RESOURCE->animations.Load(path));

		//SafeReset(emissiveMap);
		//emissiveMap = RESOURCE->textures.Load(path);
		//emissive.w = 1.0f;
	}


	ImGui::Text("PlayTime : %f", GetPlayTime());
	ImGui::SliderFloat("AniScale", &aniScale, 0.001f, 10.0f);
	for (int i = 0; i < playList.size(); i++)
	{
		string name = to_string(i) + playList[i]->file;
		ImGui::Text("%s", name.c_str());
		ImGui::PushID(i);
		
		if (ImGui::Button("STOP"))
		{
			ChangeAnimation(AnimationState::STOP, i);
		}
		ImGui::SameLine();
		if (ImGui::Button("OnceLast"))
		{
			ChangeAnimation(AnimationState::ONCE_LAST, i);
		}
		ImGui::SameLine();
		if (ImGui::Button("OnceFirst"))
		{
			ChangeAnimation(AnimationState::ONCE_FIRST, i);
		}
		ImGui::SameLine();
		if (ImGui::Button("Loop"))
		{
			ChangeAnimation(AnimationState::LOOP, i);
		}
		ImGui::SameLine();
		if (ImGui::Button("Delete"))
		{
			playList.erase(playList.begin() + i);
			ChangeAnimation(AnimationState::STOP, 0, 0.0f);
			i = playList.size();
			isChanging = false;
		}
		
		ImGui::PopID();
	}
}

float Animations::GetPlayTime()
{
	if (playList.empty()) return 0.0f;


	if (isChanging)
	{
		return (float)nextAnimator.nextFrame /
			(float)(playList[nextAnimator.animIdx]->frameMax - 1);
	}
	return (float)currentAnimator.nextFrame /
		(float)(playList[currentAnimator.animIdx]->frameMax - 1);
}
