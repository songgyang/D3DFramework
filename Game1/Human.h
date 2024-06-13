#pragma once

enum class HumanState
{
    IDLE,
    WALK,
    THROW
};


class Human
{
private:
    Actor* actor;
    HumanState state;
    bool plus = true;

    Actor* spear;
    float  gravity;

public:
    Human();
    void Update();
    void Render();
    void RenderHierarchy();

};

