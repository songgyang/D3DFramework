#pragma once
class Watermelon : public Actor
{
private:

    Vector3 velocity;
    bool    active = false;
    bool    boom = false;

    float   gravity;

public:
    static Watermelon* Create(string name = "Watermelon");

    void Fire(Vector3 pos, Vector3 dir, float speed);
    void Boom(Vector3 mouse);

    void Update();
    void Render();

    bool GetActive() { return active; }

};

