#include "stdafx.h"
#include "Watermelon.h"

Watermelon* Watermelon::Create(string name)
{
    Watermelon* temp = new Watermelon();
    temp->name = name;
    temp->LoadFile("Watermelon.xml");

    return temp;
}

void Watermelon::Fire(Vector3 pos, Vector3 dir, float speed)
{
    Find("Full")->visible = true;
    Find("T")->visible = false;
    Find("B")->visible = false;

    SetWorldPos(pos);
    velocity = dir * speed;
    active = true;
    gravity = 0.0f;
}

void Watermelon::Boom(Vector3 mouse)
{
    if (boom) return;

    Find("Full")->visible = false;
    Find("T")->visible = true;
    Find("B")->visible = true;
    boom = true;

    rotation.z =  -atan2f(mouse.y, mouse.x);


}

void Watermelon::Update()
{
    if (not active) return;
    //수박이 날아가는 로직
    MoveWorldPos(velocity * DELTA);
    MoveWorldPos(Vector3(0,-1,0) *gravity * DELTA);
    gravity += 4.0f * DELTA;

    if (boom)
    {
        Find("T")->MoveLocalPos(Vector3(0,1,0)*2.0f*DELTA);
        Find("B")->MoveLocalPos(Vector3(0, -1, 0) * 2.0f * DELTA);
    }


    

    if (GetWorldPos().y < -10.0f)
    {
        boom = false;
        active = false;
        Find("T")->SetLocalPos(Vector3(0, 0, 0));
        Find("B")->SetLocalPos(Vector3(0, 0, 0));
    }
    Actor::Update();
}

void Watermelon::Render()
{
    if (not active) return;


    Actor::Render();
}
