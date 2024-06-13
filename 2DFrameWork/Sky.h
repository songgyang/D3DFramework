#pragma once
class Sky : public Actor
{
public:
	shared_ptr<Texture> texCube = nullptr;
	static Sky* Create(string name = "Sky");
	virtual void	Render() override;
	virtual void	RenderEnviroment() override;
	void	        RenderDetail();

	void			RotateSky();
};
