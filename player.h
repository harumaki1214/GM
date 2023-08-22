#pragma once

#include"model.h"
#include"gameObject.h"


class Player : public GameObject
{
private:
	Model* m_Model{};
	class Audio* m_ShotSE{};
	class Shadow* m_Shadow{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	D3DXVECTOR3 m_Velocity{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};
