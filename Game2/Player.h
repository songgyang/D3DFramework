#pragma once

enum class PlayerState
{
	IDLE,
	WALK,
	DANCING,
	JUMPUP,
	JUMPDOWN,
	ATTACK,
	JUMPATTACK
};


class Player
{
private:
	PlayerState			state;
	SlashTrail*			slash;
	Actor*				actor;
	Vector3				lastPoint;
	Terrain*			plane = nullptr;
	float				gravity;
	bool				isFalling;

	bool				keyDown;

	//Vector3				srcPos;
	//Vector3				destPos;
	//float				lerpPos = 1.0f;
	//float				disPos;		//둘간의 거리차이를 저장

	//float				srcRot;
	//float				destRot;
	//float				lerpRot = 1.0f;
	//float				disRot;
	DamageText			damageText;
public:
	Player();
	~Player();
	virtual void Update() ;
	virtual void LateUpdate() ;
	virtual void Render() ;
	virtual void RenderShadow() ;
	virtual void RenderEnviroment() ;
	virtual void RenderWater();

	void SetMap(Terrain* target) { plane = target; }
	Vector3 GetWorldPos() { return actor->GetWorldPos(); }
	Actor* GetActor() { return actor; }
	PlayerState GetState() { return state; }
};

