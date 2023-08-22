#pragma once

#pragma once
#include"gameObject.h"

class Explosion : public GameObject
{
private:
	D3DXMATRIX  mtxWorld;

	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	int m_Count{};
	int m_FrameCount{};

	class Audio* m_ExplosionSE {};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};
