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
   
    //액터의 생성은 Create 함수로 생성
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

    //모든 로드가 끝났을땐 리소스매니저의 참조카운트를 감소시키기위해 리스트삭제
    RESOURCE->ReleaseAll();
    
}
Scene1::~Scene1()
{
    //new delete가 아닌 create release로 생성 해제
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
    // 디버그창에 출력
    LIGHT->RenderDetail();
 
    Camera::main->Update();
    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
    //하이어라이키창에 출력
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
    //gui출력끝


    //메인캠 컨트롤
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

    Matrix Yaw;//도리도리
    Matrix Pitch; //끄덕끄덕
    
    //Yaw = Matrix::CreateRotationY(RANDOM->Float(-5.0f * ToRadian, 5.0f * ToRadian));
    //Pitch = Matrix::CreateRotationX(RANDOM->Float(-5.0f * ToRadian, 5.0f * ToRadian));
    //
    //CamForwardRay.direction = Vector3::TransformNormal(CamForwardRay.direction, 
    //    Yaw);
    //CamForwardRay.direction = Vector3::TransformNormal(CamForwardRay.direction,
    //    Pitch);




    //마우스방향으로 광선 만들기
    //CamForwardRay = Utility::MouseToRay();

    //                 교차확인할 광선, 광선교차지점
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
    //그리기시작
    Camera::main->Set(); //카메라세팅
    LIGHT->Set();       //라이트세팅

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
