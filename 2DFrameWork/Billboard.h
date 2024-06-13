#pragma once
class Billboard : public Actor
{
private:


public:
	static Billboard* Create(string name = "Billboard");
	virtual void	Release();
	virtual void	Update() override;
	virtual void	Render() override;
	virtual void	RenderDetail();
};

