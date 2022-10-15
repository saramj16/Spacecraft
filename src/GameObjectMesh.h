#pragma once

#ifndef GAMEOBJECTMESH_H
#define GAMEOBJECTMESH_H

#include "GameObject.h"
#include "ResourceM.h"
#include "camera.h"


class GameObjectMesh : public GameObject {
public:
	//Attributes of this class
	Mesh* mesh;
	Texture* texture;
	Shader* shader;
	Vector3 color;
	float angle = 0;
	Vector3 f;

	boolean is_collider;
	CollisionModel3D* collision_model;

	//overwritten virtual functions
	void render();
	void update(float dt);
	void setCollisionModel();
};

#endif