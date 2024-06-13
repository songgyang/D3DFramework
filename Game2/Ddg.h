#pragma once

enum class DDGState
{
    IDLE,           //���
    UP,             //�ö󰡴���
    STAND,          //������
    DOWN,            //����������
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

