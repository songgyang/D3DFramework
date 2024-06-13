#pragma once

enum TextType
{
	TextType_UP = 1,
	TextType_DOWN = 2,
	TextType_LEFT = 4,
	TextType_RIGHT = 8,
	TextType_UPSCALE = 16,
	TextType_DOWNSCALE = 32,
	TextType_ANI = 64
};

struct WorldText
{
	wstring text;
	wstring font;
	Vector3 worldPos;
	float   lifeTime;
	float   size;
	Color	color;
	int		type;
	float    delta;
	Vector2  offset;
	float	count;


	WorldText(wstring text, Vector3 pos, float life = FLT_MAX,
		int type = 0, float  delta = 0.0f,
		Color color = Color(1,1,1), 
		float size = 30.0f,wstring font = L"µ¸¿òÃ¼")
	{
		count = 0.0f;

		offset = Vector2();
		this->text = text;
		this->size = size;
		this->font = font;
		this->type = type;
		this->delta = delta;
		this->color = color;
		worldPos = pos;
		lifeTime = life;
	}
	bool Update();
	void Render();
};

class DamageText
{
public:
	list<WorldText> TextList;
	void Add(WorldText text);
	void Update();
	void Render();
};

