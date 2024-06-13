#pragma once

enum class MonsterState
{
	IDLE,
	WALK,
	ATTACK,
	COMBACK
};

class Monster
{
private:
	Actor*				actor;
	vector<Vector3>		way;

	Vector3				srcPos;
	Vector3				destPos;
	float				lerpPos = 1.0f;
	float				disPos;

	float				srcRot;
	float				destRot;
	float				lerpRot = 1.0f;
	float				disRot;


	//참조대상
	Terrain*			plane;
	AStar*				astar;
	class Player*		pl;


	//길찾기 갱신용
	float				refreshTime = 0.0f;

	MonsterState		state = MonsterState::IDLE;
	Vector3				spawnPoint;

	int					hp = 100; //HPFront 3.7
	float				damaging = 0.0f;

	DamageText			damageText;

public:
	Monster();
	~Monster();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void RenderShadow();
	virtual void RenderEnviroment();
	virtual void RenderWater();

	void Hit(int damage);
	void InitLerp(Vector3 Dest);

	void Init(Terrain* target1, AStar* target2 , Player* pl, Vector3 SpawnPoint);

	Actor* GetActor() { return actor; }
};

