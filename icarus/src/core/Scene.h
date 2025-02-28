#pragma once
#include "archimedes/Actor.h"

static class Scene
{
public:
	bool SaveScene();
	bool ChangeScene(SceneData scene);

	SceneData GetOpenScene()
	{
		return s_OpenScene;
	}

private:
	static SceneData s_OpenScene;
};

struct SceneData
{
	sf::Color RefreshColor;
};