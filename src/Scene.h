#pragma once

#ifndef SCENE_H
#define SCENE_H


#include "GameObject.h"
#include "camera.h"

class Scene
{
public:
	Scene();
	~Scene();
	//scene graph starts from here
	GameObject* root;
	//optional - you can choose whether to put the camera in Scene
	//or leave it in game
	Camera* camera;
	std::vector<GameObject*> colliders;
	//a list of all lights - could be within graph or not
	Vector3* light_position;
	//standard render and update functions
	void render();
	void update(float);
	void getColliders(std::vector<GameObject*>& colliders, GameObject* current);

};

#endif