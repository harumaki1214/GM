#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "player.h"
#include "scene.h"

#define	VALUE_MOVE_CAMERA	(20.0f)										// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)							// カメラの回転量

void Camera::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 5.0f, -10.0f);
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void Camera::Update()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();
	m_Target = player->GetPosition();

	//トップビュー
	/*m_Target = player->GetPosition();
	m_Position = m_Target + D3DXVECTOR3(0.0f, 6.0f, -10.0f);*/
	
	//サードパーソンビュー（フォトーナイト）
	m_Target = player->GetPosition() + player->GetRight() * 0.5f;
	m_Position = m_Target - player->GetForward() * 12.0f + D3DXVECTOR3(0.0f, 3.0f, 0.0f);

	//ファーストパーソンビュー(valo)
	/*m_Position = player->GetPosition() + D3DXVECTOR3(0.0f, 1.5f, 0.0f);
	m_Target = m_Position + player->GetForward();*/
}

void Camera::Draw()
{
	// ビューマトリックス設定
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_ViewMatrix, &m_Position, &m_Target, &up);

	Renderer::SetViewMatrix(&m_ViewMatrix);

	D3DXMATRIX projectionMatrix;

	// プロジェクションマトリックス設定
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}


