#pragma once
class Mesh
{
    friend class GameObject;
    friend class Rain;
    friend class Pop;
private:
    ID3D11Buffer*           vertexBuffer;               //정점 버퍼
    ID3D11Buffer*           indexBuffer;                //인덱스 버퍼
    ID3D11Buffer*           instanceBuffer = nullptr;   //트랜스폼을 저장할 버퍼

public:
    void*                   vertices;                   //정점버퍼에 갱신될 메모리
    UINT*                   indices;                    //인덱스버퍼에 갱신될 메모리
    Matrix*                 instance;                   //스킵

    UINT                    vertexCount;                //정점 갯수
    UINT                    indexCount;                 //인덱스 갯수
    UINT                    instanceCount = 0;          //스킵

    D3D_PRIMITIVE_TOPOLOGY  primitiveTopology;          //도형정의
    VertexType              vertexType;                 //쉐이더에 들어갈 버텍스 타입
    UINT                    byteWidth;                  //정점하나당 얼만큼 크기인지
    string                  file;                       //파일명
    string                  instanceFile;
public:
    static shared_ptr<Mesh> CreateMesh();

    Mesh();
    Mesh(void* vertices, UINT vertexCount, UINT* indices,
        UINT indexCount, VertexType type);
    void CreateInstanceBuffer(Matrix* instance, UINT instanceCount);
    ~Mesh();
    void Set();
    bool LoadFile(string file);
    void SaveFile(string file);
    void                RenderDetail(GameObject* root);
    const Vector3& GetVertexPosition(UINT idx);
    void UpdateBuffer();
    void DrawCall();
    bool LoadInstanceFile(string file);
    void SaveInstanceFile(string file);
    void InstanceEdit(GameObject* root);
    /*void Reset();
    
    */
};
