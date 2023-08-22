#pragma once
#include"gameObject.h"
#include"model.h"

class Bullet : public GameObject
{
private:
	static Model* m_BulletModel;

	D3DXVECTOR3  m_Velocity{};
	class Audio* m_ExplosionSE{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

public:
	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	//void SetVelocity(D3DXVECTOR3);
};