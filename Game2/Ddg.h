#pragma once

enum class DDGState
{
    IDLE,           //대기
    UP,             //올라가는중
    STAND,          //서있음
    DOWN,            //내려가는중
    HIT
};

class Ddg
{
private:
    float   lifeTime;

public:
    Actor*  actor;
    DDGState state;
    float       time;
public:
    Ddg();
    void Update();
    void Render();
    void RenderHierarchy();

    void StandUp();
    void Hit();

};

