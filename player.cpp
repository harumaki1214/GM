
#include "main.h"
#include "renderer.h"
#include "manager.h"

#include "scene.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "cylinder.h"
#include "box.h"
#include "audio.h"
#include "shadow.h"


void Player::Init()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\player.obj");

	m_Position = D3DXVECTOR3(0.0f, 1.0f, -5.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\vertexLightingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\vertexLightingPS.cso");

	m_ShotSE = AddComponent<Audio>();
	m_ShotSE->Load("asset\\audio\\wan.wav");
	
	m_Shadow = AddComponent<Shadow>();
}


void Player::Uninit()
{
	GameObject::Uninit();

	m_Model->Unload();
	delete m_Model;

	//ここにシェーダーオブジェクトの解放を追加
	if (m_VertexLayout != NULL)
	{
		m_VertexLayout->Release();
		m_VertexLayout = NULL;
	}

	if (m_VertexShader != NULL)
	{
		m_VertexShader->Release();
		m_VertexShader = NULL;
	}

	if (m_PixelShader != NULL)
	{
		m_PixelShader->Release();
		m_PixelShader = NULL;
	}
}


void Player::Update()
{
	GameObject::Update();

	Scene* scene = Manager::GetScene();

	D3DXVECTOR3 oldPosition = m_Position;

	//トップビュー
	/*if (Input::GetKeyPress('A'))
		m_Position.x -= 0.1f;

	if (Input::GetKeyPress('D'))
		m_Position.x += 0.1f;

	if (Input::GetKeyPress('W'))
		m_Position.z += 0.1f;

	if (Input::GetKeyPress('S'))
		m_Position.z -= 0.1f;*/


		/*if (Input::GetKeyPress('R'))
			m_Rotation.x -= 0.1f;
		if (Input::GetKeyPress('F'))
			m_Rotation.x += 0.1f;*/
	
	//弾発射
	if (Input::GetKeyTrigger(VK_SPACE))
	{
		Bullet* bullet = scene->AddGameObject<Bullet>(1);
		//scene->AddGameObject<Bullet>(3)->SetPosition(m_Position);
		bullet->SetVelocity(GetForward());
		bullet->SetPosition(GetPosition());

		m_ShotSE->Play();
	}

	if (Input::GetKeyPress('A'))
		m_Position -= GetRight() * 0.1f;

	if (Input::GetKeyPress('D'))
		m_Position += GetRight() * 0.1f;

	if (Input::GetKeyPress('W'))
		m_Position += GetForward() * 0.1f;

	if (Input::GetKeyPress('S'))
		m_Position -= GetForward() * 0.1f;

	if (Input::GetKeyPress('Q'))
		m_Rotation.y -= 0.05f;

	if (Input::GetKeyPress('E'))
		m_Rotation.y += 0.05f;

	//ジャンプ
	if (Input::GetKeyTrigger('J'))
	{
		m_Velocity.y = 0.35f;
	}

	m_Velocity.y -= 0.010f;

	//移動
	m_Position += m_Velocity;

	//障害物との当たり判定
	float groundHeight = 0.0f;

	std::vector<Cylinder*> cylinders = scene->GetGameObjects<Cylinder>();   //std::vector<Enemy*>はautoでも可

	for (Cylinder* cylinder : cylinders)
	{
		D3DXVECTOR3 position = cylinder->GetPosition();
		D3DXVECTOR3 scale = cylinder->GetScale();

		D3DXVECTOR3 direction = m_Position - position;
		direction.y = 0.0f;
		float length = D3DXVec3Length(&direction);

		if (length < scale.x)
		{
			if (m_Position.y < position.y + scale.y - 0.5f)
			{
				m_Position.x = oldPosition.x;
				m_Position.z = oldPosition.z;
			}
			else
			{
				groundHeight = position.y + scale.y;
			}
			break;
		}
	}

	std::vector<Box*> boxes = scene->GetGameObjects<Box>();   //std::vector<Enemy*>はautoでも可

	for (Box* box : boxes)
	{
		D3DXVECTOR3 position = box->GetPosition();
		D3DXVECTOR3 scale = box->GetScale();
	
		if (position.x - scale.x - 0.5f < m_Position.x &&
			m_Position.x < position.x + scale.x + 0.5f &&
			position.z - scale.z - 0.5f < m_Position.z &&
			m_Position.z < position.z + scale.z + 0.5f)
		{
			if (m_Position.y < position.y + scale.y * 2.0f - 0.5f)
			{
				m_Position.x = oldPosition.x;
				m_Position.z = oldPosition.z;
			}
			else
			{
				groundHeight = position.y + scale.y * 2.0f;
			}
			break;
		}
	}

	//	
	D3DXVECTOR3 shadowPosition = m_Position;
	shadowPosition.y = groundHeight + 0.01f;
	m_Shadow->SetPosition(shadowPosition);

	//接地
	if (m_Position.y < groundHeight && m_Velocity.y < 0.0f)
	{
		m_Position.y = groundHeight;
		m_Velocity.y = 0.0f;
	}

}


void Player::Draw()
{
	GameObject::Draw();

	//ここにシェーダー関連の描画準備を追加 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//使用するシェーダを設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y + D3DX_PI, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}