#include "stdafx.h"
#include "Ddg.h"

Ddg::Ddg()
{
    actor = Actor::Create();
    actor->LoadFile("Box.xml");
    lifeTime = 0.0f;
    state = DDGState::IDLE;
    time = 0.0f;
}

void Ddg::Update()
{
    if (state == DDGState::IDLE)
    {

    }
    else if (state == DDGState::UP)
    {
        actor->MoveWorldPos(Vector3(0, 1, 0) * 10.0f * DELTA);
        time -= DELTA;
        if (time < 0.0f)
        {
            time = 1.0f;
            state = DDGState::STAND;
        }
    }
    else if (state == DDGState::STAND)
    {
        time -= DELTA;
        if (time < 0.0f)
        {
            time = 1.0f;
            state = DDGState::DOWN;
        }
    }
    else if (state == DDGState::DOWN)
    {
        actor->MoveWorldPos(Vector3(0, -1, 0) * 10.0f * DELTA);
        time -= DELTA;
        if (time < 0.0f)
        {
            time = 1.0f;
            state = DDGState::IDLE;
            actor->SetWorldPosY(0.0f);
        }
    }
    else if (state == DDGState::HIT)
    {
        actor->material->ambient.x = RANDOM->Float(0.5, 1.0f);
        actor->material->ambient.y = 0.0f;
        actor->material->ambient.z = 0.0f;
        time -= DELTA;
        if (time < 0.0f)
        {
            time = 1.0f;
            state = DDGState::DOWN;
            actor->material->ambient.x = 1.0f;
            actor->material->ambient.y = 1.0f;
            actor->material->ambient.z = 1.0f;
        }
    }



    actor->Update();
}

void Ddg::Render()
{
    actor->Render();
}

void Ddg::RenderHierarchy()
{
    actor->RenderHierarchy();
}

void Ddg::StandUp()
{
    time = 1.0f;
    state = DDGState::UP;

}

void Ddg::Hit()
{
    time = 1.0f;
    state = DDGState::HIT;


}
