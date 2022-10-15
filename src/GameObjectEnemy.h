#pragma once

#include "GameObjectMesh.h"
#include "includes.h"
#include <ctime>

class GameObjectEnemy : public GameObjectMesh {
public:
	std::vector<Vector3> waypoints;
	Vector3 target;
	Vector3 to_target;
	float angle_rotation;
	Vector3 axis;
	Vector3 rotate_axis;

	boolean is_collider;

	void update(float dt, bool baixada);
	void rotateShips(float dt);
	void selectWaypoint();
};