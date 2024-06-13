#pragma once
class Mesh
{
    friend class GameObject;
    friend class Rain;
    friend class Pop;
private:
    ID3D11Buffer*           vertexBuffer;               //���� ����
    ID3D11Buffer*           indexBuffer;                //�ε��� ����
    ID3D11Buffer*           instanceBuffer = nullptr;   //Ʈ�������� ������ ����

public:
    void*                   vertices;                   //�������ۿ� ���ŵ� �޸�
    UINT*                   indices;                    //�ε������ۿ� ���ŵ� �޸�
    Matrix*                 instance;                   //��ŵ

    UINT                    vertexCount;                //���� ����
    UINT                    indexCount;                 //�ε��� ����
    UINT                    instanceCount = 0;          //��ŵ

    D3D_PRIMITIVE_TOPOLOGY  primitiveTopology;          //��������
    VertexType              vertexType;                 //���̴��� �� ���ؽ� Ÿ��
    UINT                    byteWidth;                  //�����ϳ��� ��ŭ ũ������
    string                  file;                       //���ϸ�
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
