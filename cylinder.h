#pragma once
#include"gameObject.h"
#include"model.h"

class Cylinder : public GameObject
{
private:
	static Model* m_CylinderModel;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

public:
	static void Load();
	static void Unlooad();
	void Init();
	void Uninit();
	void Update();
	void Draw();

	//void SetPosition();
};