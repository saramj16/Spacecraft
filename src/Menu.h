#pragma once
#include "includes.h"
#include "utils.h"
#include "camera.h"
#include "rendertotexture.h"
#include "SceneParser.h"
#include "shader.h"
#include "mesh.h"




class Menu {
public:
	Menu(int sw, int sh);
	~Menu();

	Mesh* mesh;
	Camera* c;

	boolean inici = false;

	std::vector<Texture*> entries;
	int current_entry;
	Shader* shader;

	Texture* texture;

	void carregarJuga();




};