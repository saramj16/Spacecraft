#include "HUD.h"
#include <stdlib.h>

HUD::HUD(int sw, int sh) {

	this->camera = new Camera();
	camera->setOrthographic(0, sw, 0, sh, 0.1, 2);
	camera->updateViewMatrix();

	//Level
	mesh1 = new Mesh();
	mesh1->vertices.resize(4);
	mesh1->uvs.resize(4);

	mesh1->vertices[0] = Vector3(0, sh - 45, 1);
	mesh1->vertices[1] = Vector3(30, sh - 45, 1);
	mesh1->vertices[2] = Vector3(30, sh, 1);
	mesh1->vertices[3] = Vector3(0, sh, 1);

	mesh1->uvs[0] = Vector2(0, 0);
	mesh1->uvs[1] = Vector2(1, 0);
	mesh1->uvs[2] = Vector2(1, 1);
	mesh1->uvs[3] = Vector2(0, 1);

	mesh1->indices.resize(6);
	mesh1->indices[0] = 0;
	mesh1->indices[1] = 1;
	mesh1->indices[2] = 2;
	mesh1->indices[3] = 0;
	mesh1->indices[4] = 2;
	mesh1->indices[5] = 3;

	mesh1->genBuffers();

	tex_shader1 = new Shader();
	tex_shader1->load("data/shaders/menu.vert", "data/shaders/menu.frag");

	//Two
	mesh2 = new Mesh();
	mesh2->vertices.resize(4);
	mesh2->uvs.resize(4);


	mesh2->vertices[0] = Vector3(370, sh - 45, 1);
	mesh2->vertices[1] = Vector3(400, sh - 45, 1);
	mesh2->vertices[2] = Vector3(400, sh, 1);
	mesh2->vertices[3] = Vector3(370, sh, 1);

	mesh2->uvs[0] = Vector2(0, 0);
	mesh2->uvs[1] = Vector2(1, 0);
	mesh2->uvs[2] = Vector2(1, 1);
	mesh2->uvs[3] = Vector2(0, 1);

	mesh2->indices.resize(6);
	mesh2->indices[0] = 0;
	mesh2->indices[1] = 1;
	mesh2->indices[2] = 2;
	mesh2->indices[3] = 0;
	mesh2->indices[4] = 2;
	mesh2->indices[5] = 3;

	mesh2->genBuffers();

	tex_shader2 = new Shader();
	tex_shader2->load("data/shaders/points.vert", "data/shaders/points.frag");

	texture1 = new Texture();
	texture2 = new Texture();

}

void HUD::points(int p) {

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int punts1, punts2;
	if (p < 10) {
		punts1 = 0;
		punts2 = p;
	}
	else {
		punts1 = p / 10;
		punts2 = p % 10;
	}
	

	texture1->load("data/assets/num" + punts1 + '.tga');
	tex_shader1->enable();
	tex_shader1->setTexture("u_texture_diffuse", texture1);
	tex_shader1->setMatrix44("u_mvp", camera->viewprojection_matrix);
	mesh1->render(GL_TRIANGLES, tex_shader1);
	tex_shader1->disable();

	texture2->load("data/assets/num" + punts2 + '.tga');
	tex_shader2->enable();
	tex_shader2->setTexture("u_texture_diffuse", texture2);
	tex_shader2->setMatrix44("u_mvp", camera->viewprojection_matrix);
	mesh2->render(GL_TRIANGLES, tex_shader2);
	tex_shader2->disable();

	glEnable(GL_BLEND);
}


