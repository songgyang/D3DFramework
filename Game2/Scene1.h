#pragma once
class Scene1 : public Scene
{
private:

    CubeRenderTarget* shadowTarget;
    CubeRenderTarget* environmentTarget;

    Actor*          sphere;


    Camera* cam1;
    Grid* grid;
    Sky*    sky;
    Water* water;

    class Player* pl;
    class Monster* mon[3];

    Terrain* plane;
    AStar* astar;
    Light* pointLight;
    float               distance = 30;
    Rain* rain;

    PostEffect* postEffect;


public:
    Scene1();
    ~Scene1();

    // Scene��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void ResizeScreen() override;
};
