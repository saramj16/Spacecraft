#pragma once

#ifndef SCENEPARSER_H
#define SCENEPARSER_H

#include "includes.h"
#include "utils.h"
#include <unordered_map>
#include "ParseObject.h"
#include "ParseObjectData.h"
#include "extra/textparser.h"
#include <string>
#include "GameObjectEnemy.h"
#include "GameObjectEnvironment.h"
#include "GameObjectMesh.h"
#include "game.h"
#include "Scene.h"

class SceneParser
{
public:
	int n_resources;
	std::vector<ParseObject> resources;
	int n_objects;
	std::vector<ParseObjectData> objects;

	Scene* escena;

	Scene* ParseData(const char* f);
	Scene* loadEscena();
};

#endif 