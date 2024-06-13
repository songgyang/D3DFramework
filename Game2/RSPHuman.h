#pragma once


class RSPHuman
{
    Actor*      actor;
    Actor*      RSP[3];
    int			src, dest;
    float		w;
    int    num;
    float       plus = 1.0f;
public:
    RSPHuman(bool player);
    void Update();
    void Render();
    void RenderHierarchy();
    void LerpHand(GameObject* node);
    void UpHand(int num);
    void DownHand();
};

