#pragma once
class Water : public Actor
{
    friend class GameObject;
private:
    struct WaterBuffer
    {
        Vector2 velocity;
        float time;
        float padding;
    }waterBufferDesc;
    float uvScale = 20.0f;
    ID3D11Buffer* waterBuffer;
    ID3D11Buffer* clipPlaneBuffer;

    //�ݻ�� �� �׷��� ����Ÿ��
    CubeRenderTarget* reflection;
    CubeRenderTarget* refraction;


public:
    static Water* Create(string name = "Water");
    Water();

    void Update();
    virtual void Render();
    void RenderDetail();

    //�ݻ� ĸó
    void SetReflectionTarget();
    //���� ĸó
    void SetRefractionTarget();
    void UpdateUv();

};

