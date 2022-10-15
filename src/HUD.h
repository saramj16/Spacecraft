#pragma once

#include "includes.h"
#include "camera.h"
#include "shader.h"
#include "texture.h"
#include "mesh.h"

class HUD {
public:

	HUD(int sw, int sh);
	~HUD();

	Camera* camera;
	Shader* tex_shader1;
	Shader* tex_shader2;

	//Timer
	Mesh* mesh1;
	Texture* texture1;
	Mesh* mesh2;
	Texture* texture2;


	void render();
	void update(float);

	void points(int p);

};
