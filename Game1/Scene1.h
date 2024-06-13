#pragma once

#define TreeMax 50

class Scene1 : public Scene
{
private:
    Camera* cam1;
    Grid*   grid;
   
    //�⺻������ ������Ʈ�� ���ͷ� ����
    Actor*  trees[TreeMax][TreeMax];
    Actor* tree;
    Actor* root;
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

