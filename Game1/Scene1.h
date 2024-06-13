#pragma once

#define TreeMax 50

class Scene1 : public Scene
{
private:
    Camera* cam1;
    Grid*   grid;
   
    //기본적으로 오브젝트는 액터로 설정
    Actor*  trees[TreeMax][TreeMax];
    Actor* tree;
    Actor* root;
public:
    Scene1();
    ~Scene1();

    // Scene을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void ResizeScreen() override;
};

