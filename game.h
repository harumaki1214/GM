#pragma once
#include "main.h"
#include "renderer.h"
#include "manager.h"

#include"scene.h"

class Game : public Scene
{

private:
	class Fade* m_Fade{};

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
};