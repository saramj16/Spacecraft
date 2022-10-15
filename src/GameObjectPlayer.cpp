#include "GameObjectPlayer.h"

void GameObjectPlayer::update(float dt) {
	object_position = Vector3(
		this->model.m[12],
		this->model.m[13],
		this->model.m[14]);

	this->model.traslate(-f.x *dt * 100, -f.y *dt * 100, -f.z *dt * 100);
}

Vector3 GameObjectPlayer::getPosition() {
	return object_position;
}

void GameObjectPlayer::left() {
	this->model.rotateLocal(-0.03, Vector3(0, 0, 1));
}

void GameObjectPlayer::right() {
	this->model.rotateLocal(0.03, Vector3(0, 0, 1));
}

void GameObjectPlayer::up() {
	this->model.rotateLocal(-0.02, Vector3(1, 0, 0));
}

void GameObjectPlayer::down() {
	this->model.rotateLocal(0.02, Vector3(1, 0, 0));
}

