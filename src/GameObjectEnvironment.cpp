#include "GameObjectEnvironment.h"
#include "game.h"

void GameObjectEnvironment::render() {

	Game* g = Game::instance;

	//*** Drawing code starts here ***

	glDisable(GL_DEPTH_TEST);
	glCullFace(GL_FRONT);

	this->model.setTranslation(g->scene->camera->eye.x, g->scene->camera->eye.y, g->scene->camera->eye.z);

	//create our mvp
	Matrix44 mvp = model * g->scene->camera->viewprojection_matrix;
	//create normal matrix
	Matrix44 inverse_m = model;
	inverse_m.inverse();
	Matrix44 normal_m = inverse_m.transpose();
	//light position
	Vector3 light_pos(100.0f, 100.0f, 100.0f);

	//enable shader and set uniforms
	this->shader->enable();
	this->shader->setMatrix44("u_mvp", mvp);
	this->shader->setMatrix44("u_normal_matrix", normal_m);
	this->shader->setUniform3("u_light", light_pos);
	this->shader->setTexture("u_texture_diffuse", this->texture);



	mesh->render(GL_TRIANGLES, shader);



	//disable the shader
	shader->disable();

	//disable blending to draw text on top
	glDisable(GL_BLEND);


	for (int i = 0; i < this->children.size(); i++) {
		this->children[i]->render();
	}

	//*** Drawing code ends here ***
}

void GameObjectEnvironment::update(float dt) {

}