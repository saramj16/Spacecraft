#include "GameObjectMesh.h"
#include "game.h"



void GameObjectMesh::render() {

	Game* game = Game::instance;

	//*** Drawing code starts here ***
	//build a rotation matrix - angle is incremented in update()


	Matrix44 mvp = model * game->scene->camera->viewprojection_matrix;

	Matrix44 inverse_m = model;
	inverse_m.inverse();
	Matrix44 normal_m = inverse_m.transpose();

	Vector3 light_pos(100.0f, 100.0f, 100.0f);

	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);


	this->shader->enable();
	this->shader->setMatrix44("u_mvp", mvp);
	this->shader->setMatrix44("u_normal_matrix", normal_m);
	this->shader->setUniform3("u_light", light_pos);
	this->shader->setTexture("u_texture_diffuse", this->texture);
	f = this->model.frontVector().normalize();

	mesh->render(GL_TRIANGLES, shader);


	shader->disable();


	glDisable(GL_BLEND);


	for (int i = 0; i < this->children.size(); i++) {
		this->children[i]->render();
	}

}

void GameObjectMesh::update(float dt) {

}

void GameObjectMesh::setCollisionModel() {

	collision_model = newCollisionModel3D();

	collision_model->setTriangleNumber(mesh->indices.size() / 3);

	for (size_t i = 0; i < mesh->indices.size() / 3; i++) {

		Vector3 v1 = mesh->vertices[mesh->indices[i * 3]];
		Vector3 v2 = mesh->vertices[mesh->indices[i * 3 + 1]];
		Vector3 v3 = mesh->vertices[mesh->indices[i * 3 + 2]];

		collision_model->addTriangle(v1.x, v1.y, v1.z,
			v2.x, v2.y, v2.z,
			v3.x, v3.y, v3.z);
	}

	collision_model->finalize();

}