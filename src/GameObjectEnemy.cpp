#include "GameObjectEnemy.h"

void GameObjectEnemy::update(float dt,  bool baixada) {

	Vector3 object_pos(
		this->model.m[12],
		this->model.m[13],
		this->model.m[14]);

	if ((abs(object_pos.x - target.x) >= 5 || abs(object_pos.y - target.y) >= 5 || abs(object_pos.z - target.z) >= 5)) {
		this->model.traslate(-f.x *dt * 50, -f.y *dt * 50, -f.z *dt * 50);
		rotateShips(dt);
	}
	else {
		selectWaypoint();
	}

}



void GameObjectEnemy::rotateShips(float dt) {
	
	Vector3 object_pos(
		this->model.m[12],
		this->model.m[13],
		this->model.m[14]);

	to_target = (target - object_pos).normalize();
	Vector3 real_front = this->model.frontVector().normalize();

	angle_rotation = 3.14159265359 - acos(to_target.dot(real_front));
	axis = to_target.cross(real_front);

	Matrix44 inv = this->model;
	inv.inverse();
	rotate_axis = inv.rotateVector(axis);

	if (angle_rotation > 0.1)
		this->model.rotateLocal(-0.06, rotate_axis);
}

void GameObjectEnemy::selectWaypoint() {

	srand(time(NULL));
	rand() % waypoints.size();
	target = waypoints[rand() % waypoints.size()];

}
