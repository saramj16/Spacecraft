#pragma once

#include "GameObjectMesh.h"
#include "includes.h"

class GameObjectPlayer : public GameObjectMesh {
public:

	Vector3 position;
	Vector3 object_position;


	boolean is_collider;

	void update(float dt);
	Vector3 getPosition();
	void up();
	void down();
	void left();
	void right();
};
