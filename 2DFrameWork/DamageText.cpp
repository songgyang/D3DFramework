#include "framework.h"
#include "DamageText.h"

bool WorldText::Update()
{
	if (lifeTime > 0.0f and lifeTime != FLT_MAX)
	{
		lifeTime -= DELTA;
		if (type & TextType_ANI)
		{
			count += delta * DELTA;
		}
		if (type & TextType_UP)
		{
			offset.y -= delta * DELTA;
		}
		else if (type & TextType_DOWN)
		{
			offset.y += delta * DELTA;
		}
		if (type & TextType_RIGHT)
		{
			offset.x += delta * DELTA;
		}
		else if (type & TextType_LEFT)
		{
			offset.x -= delta * DELTA;
		}
		if (type & TextType_UPSCALE)
		{
			size += delta * DELTA;
		}
		else if (type & TextType_DOWNSCALE)
		{
			size -= delta * DELTA;
		}

	}

	if (lifeTime <= 0.0f)
	{
		return false;
	}
	return true;
}

void WorldText::Render()
{
	if (lifeTime > 0.0f)
	{
		Vector3 screenPos = Utility::WorldToScreen(worldPos);
		screenPos.x += offset.x - size/2.0f * 0.5f * text.size();
		screenPos.y += offset.y - size * 0.5f / 1.0f;

		if (screenPos.x >= 0 and screenPos.y >= 0 and screenPos.z >= 0)
		{
			if (type & TextType_ANI)
			{
				wstring copy;
				int countsize = min((int)count, text.size());
				copy.assign(text.c_str(), countsize);
				DWRITE->RenderText(copy, RECT{ (LONG)screenPos.x ,(LONG)screenPos.y,
			(LONG)screenPos.x + (LONG)App.GetWidth(),
				(LONG)screenPos.y + (LONG)App.GetHeight() }, size, font, color);
			}
			else
			DWRITE->RenderText(text, RECT{ (LONG)screenPos.x ,(LONG)screenPos.y,
			(LONG)screenPos.x + (LONG)App.GetWidth(),
				(LONG)screenPos.y + (LONG)App.GetHeight() }, size,font,color);
		}
	}
}

void DamageText::Add(WorldText text)
{
	TextList.push_back(text);
}
void DamageText::Update()
{
	for(auto it = TextList.begin(); it != TextList.end();)
	{
		if (not it->Update())
		{
			it = TextList.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void DamageText::Render()
{
	for (auto it = TextList.begin(); it != TextList.end(); it++)
	{
		it->Render();
	}
}
