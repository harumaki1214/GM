
#include "main.h"
#include "renderer.h"
#include "polygon2D.h"
#include "sprite.h"

void Polygon2D::Init()
{
	//ここにシェーダーファイルのロードを追加
	//CRenderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "unlitColorVS.cso");
	//CRenderer::CreatePixelShader(&m_PixelShader, "unlitColorPS.cso");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

	//Sprite* sprite = AddComponent<Sprite>();
	AddComponent<Sprite>()->Init(50.0f, 50.0f, 100.0f, 50.0f, "asset\\texture\\boss_position.PNG");
	//AddComponent<Sprite>()->Init(100.0f, 300.0f, 300.0f, 200.0f, "asset\\texture\\boss_position.PNG");
}


void Polygon2D::Uninit()
{
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

	GameObject::Uninit();
}


void Polygon2D::Update()
{
	GameObject::Update();
}


void Polygon2D::Draw()
{
	//ここにシェーダー関連の描画準備を追加
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//使用するシェーダを設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//基底クラスのメソッド呼び出し
	GameObject::Draw();
}