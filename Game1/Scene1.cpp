#include "stdafx.h"
#include "Human.h"
#include "Scene1.h"

void PrintMouseOver()
{
    cout << "PrintMouseOver" << endl;
}

Scene1::Scene1()
{

    //root = Actor::Create("Root");


    grid = Grid::Create();

    cam1 = Camera::Create();
    cam1->LoadFile("Cam.xml");

    Camera::main = cam1;
   
    //������ ������ Create �Լ��� ����
    /*for (int i = 0; i < TreeMax; i++)
    {
        for (int j= 0; j < TreeMax; j++)
        {
            trees[i][j] = Actor::Create();
            trees[i][j]->LoadFile("Tree.xml");
            trees[i][j]->SetWorldPosX(20 * i);
            trees[i][j]->SetWorldPosZ(20 * j);
        }

    }*/
  
    tree = Actor::Create();
    tree->LoadFile("Tree.xml");
    /*Matrix* trans = new Matrix[TreeMax * TreeMax];
    UINT transCount = TreeMax * TreeMax;
    for (int i = 0; i < TreeMax; i++)
    {
        for (int j = 0; j < TreeMax; j++)
        {
            Matrix pos = Matrix::CreateTranslation(20 * i, 0, 20 * j);
            trans[i* TreeMax +j] = pos.Transpose();
        }

    }
    tree->Find("Default")->mesh->CreateInstanceBuffer(trans, transCount);
    tree->Find("TreeMeshObject1")->mesh->CreateInstanceBuffer(trans, transCount);*/

    //��� �ε尡 �������� ���ҽ��Ŵ����� ����ī��Ʈ�� ���ҽ�Ű������ ����Ʈ����
    RESOURCE->ReleaseAll();
    
}
Scene1::~Scene1()
{
    //new delete�� �ƴ� create release�� ���� ����
    grid->Release();
    cam1->Release();
    tree->Release();
  

}

void Scene1::Init()
{

}

void Scene1::Release()
{
}

void Scene1::Update()
{
    // �����â�� ���
    LIGHT->RenderDetail();
 
    Camera::main->Update();
    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
    //���̾����Űâ�� ���
    ImGui::Begin("Hierarchy");
    grid->RenderHierarchy();
    cam1->RenderHierarchy();
    root->RenderHierarchy();
    /*for (int i = 0; i < TreeMax; i++)
    {
        for (int j = 0; j < TreeMax; j++)
        {
            trees[i][j]->RenderHierarchy();
        }

    }*/

    tree->RenderHierarchy();
    ImGui::End();
    //gui��³�


    //����ķ ��Ʈ��
    Camera::main->ControlMainCam();

    

    grid->Update();
    tree->Update();
    root->Update();
    /*for (int i = 0; i < TreeMax; i++)
    {
        for (int j = 0; j < TreeMax; j++)
        {
            trees[i][j]->Update();
        }

    }*/
}

void Scene1::LateUpdate()
{
    Ray CamForwardRay;

    CamForwardRay.position = Camera::main->GetWorldPos();
    CamForwardRay.direction = Camera::main->GetForward();

    Matrix Yaw;//��������
    Matrix Pitch; //��������
    
    //Yaw = Matrix::CreateRotationY(RANDOM->Float(-5.0f * ToRadian, 5.0f * ToRadian));
    //Pitch = Matrix::CreateRotationX(RANDOM->Float(-5.0f * ToRadian, 5.0f * ToRadian));
    //
    //CamForwardRay.direction = Vector3::TransformNormal(CamForwardRay.direction, 
    //    Yaw);
    //CamForwardRay.direction = Vector3::TransformNormal(CamForwardRay.direction,
    //    Pitch);




    //���콺�������� ���� �����
    //CamForwardRay = Utility::MouseToRay();

    //                 ����Ȯ���� ����, ������������
   /* Vector3 Hit;
    if (floor->Intersect(CamForwardRay, Hit))
    {
        sphere->SetWorldPos(Hit);
    }*/


}

void Scene1::PreRender()
{
   
} 

void Scene1::Render()
{
    //�׸������
    Camera::main->Set(); //ī�޶���
    LIGHT->Set();       //����Ʈ����

    grid->Render();
    tree->Render();
    root->Render();
   /* for (int i = 0; i < TreeMax; i++)
    {
        for (int j = 0; j < TreeMax; j++)
        {
            trees[i][j]->Render();
        }

    }*/
}

void Scene1::ResizeScreen()
{
    Camera::main->viewport.x = 0.0f;
    Camera::main->viewport.y = 0.0f;
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();
    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();
}  
