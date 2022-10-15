#pragma once

#ifndef PARSEOBJECTDATA_H
#define PARSEOBJECTDATA_H


#include "includes.h"
#include <cmath>

class ParseObjectData
{
public:
	char* object;
	char* name;
	char* mesh;
	char* shader;
	char* texture;
	std::vector<Vector3> waypoints;
	Vector3 position;
	Vector3 scale;
	Vector3 rotation;

};

#endif