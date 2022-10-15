#pragma once

#ifndef GAMEOBJECTENVIRONMENT_H
#define GAMEOBJECTENVIRONMENT_H


#include "GameObject.h"
#include "ResourceM.h"
#include "camera.h"


class GameObjectEnvironment : public GameObject
{
public:

	//Attributes of this class
	Mesh* mesh;
	Texture* texture;
	Shader* shader;
	Vector3 color;
	float angle = 0;
	boolean is_collider;

	//overwritten virtual functions
	void render();
	void update(float dt);
};

#endif