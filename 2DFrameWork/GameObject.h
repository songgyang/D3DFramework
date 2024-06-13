#pragma once

enum class ObType
{
	GameObject,
	Actor,
	Camera,
	Terrain,
	UI,
	Sky,
	Light,
	Billboard,
	Rain,
	Pop,
	Water
};

//��ġ�� ���� �׷����� ������Ʈ
class GameObject : public Transform
{
	friend class Actor;
	//static -> non static
	//member -> method
	//private -> protected -> pulic

	//static
private:
	static GameObject* axis;
	static Material* defalutMaterial;
public:
	static GameObject* Create(string name = "GameObject");
	static void CreateStaticMember();
	static void DeleteStaticMember();
	static void RenderAxis();


	//non static
protected:
	ObType						type;

public:
	shared_ptr<Mesh>			mesh;
	shared_ptr<Shader>			shader;
	shared_ptr<Shader>			shadowShader = nullptr;
	shared_ptr<Shader>			enviromentShader = nullptr;
	shared_ptr<Shader>			waterShader = nullptr;

	class Material*				material;
	class Collider*				collider;



	string						name;
	bool						visible;
	bool						rootMotion = false;

	class Actor*				skelRoot;	//���̷��� ���� ���

	class Actor*				root;		//�ֻ���
	map<string, GameObject*>	children;	//�ڽ�
	int                         boneIndex = -1;


protected:
	GameObject();
	//���� ��常 �������
	GameObject(GameObject& src);
	virtual ~GameObject();
	void	SaveObject(Xml::XMLElement* This, Xml::XMLDocument* doc);
	void	LoadObject(Xml::XMLElement* This);
	virtual void        CopyChild(GameObject* src);
public:
	virtual void	Release();
	void			AddChild(GameObject* child);
	void			AddBone(GameObject* child);
	virtual bool	RenderHierarchy();
	virtual void	RenderDetail();

	virtual void	Update();
	virtual void	Render();
	virtual void	RenderShadow();
	virtual void	RenderEnviroment();
	virtual void	RenderWater();


	bool            Intersect(GameObject* target);
	bool            Intersect(Ray Ray, Vector3& Hit);
};

class Actor : public GameObject
{
	friend class GameObject;
public:
	static Actor* Create(string name = "Actor");
	static Actor* Create(Actor* src);
protected:
	Actor();
	//��Ʈ��常 ����
	Actor(Actor& src);
	virtual ~Actor();
public:
	string			file;
	Skeleton*		skeleton;
	Animations*		anim;
	int             boneIndexCount = 1;
	//�ؽ����̺�
	unordered_map<string, GameObject*>	obList;
public:
	void			ReleaseMember();
	GameObject*		Find(string name);
	bool            DeleteObject(string Name);
	bool            DeleteAllObject(string Name);
	//                 
	bool			ReleaseLinkObject(string ActorName);

	virtual void	RenderDetail();
	void			SaveFile(string file);
	void			LoadFile(string file);
	virtual void	Update();
	virtual void    Render();
	virtual void	RenderShadow();
	virtual void	RenderEnviroment();
	virtual void	RenderWater();
};