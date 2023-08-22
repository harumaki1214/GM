#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"

#include "title.h"
#include "titlelogo.h"
#include "game.h"
#include"polygon2D.h"
#include"fade.h"

void Title::Init()
{
	AddGameObject<TitleLogo>(2);
	m_Fade = AddGameObject<Fade>(2);
}

void Title::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger(VK_RETURN))
	{
		m_Fade->FadeOut();
		//Manager::SetScene<Game>();
	}

	if (m_Fade->GetFadeFinish())
	{
		Manager::SetScene<Game>();
	}
}
