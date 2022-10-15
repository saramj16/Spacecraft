#include "Scene.h"


Scene::Scene() {
	this->root = new GameObject();
	light_position = new Vector3(100, 100, 100);

}
Scene::~Scene() {
	this->root->clear();
	delete this->root;
}
void Scene::render() {
	this->root->render();
}
void Scene::update(float dt) {
	this->root->update(dt);
}

void Scene::getColliders(std::vector<GameObject*>& colliders, GameObject* current) {
	colliders.push_back(current);

}