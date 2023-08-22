#include "main.h"
#include "renderer.h"
#include "manager.h"

#include"input.h"
#include "result.h"
#include "resultLogo.h"
#include "title.h"
#include "Polygon2D.h"
#include "fade.h"

void Result::Init()
{
	AddGameObject<ResultLogo>(2);
	m_Fade = AddGameObject<Fade>(2);
}

void Result::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger(VK_RETURN))
	{
		m_Fade->FadeOut();
		//Manager::SetScene<Game>();
	}

	if (m_Fade->GetFadeFinish())
	{
		Manager::SetScene<Title>();
	}
}
