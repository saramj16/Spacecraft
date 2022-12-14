/*  by Alun Evans 2016 LaSalle (alunthomasevasevans@gmail.com)
	based on framework by Javi Agenjo 2013 UPF  javi.agenjo@gmail.com
	This contains several functions that can be useful when programming your game.
*/
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>
#include <vector>

#include "framework.h"

//General functions **************
long getTime();

//generic purposes fuctions
void genGrid(float, float);
void drawGrid();
bool drawText(float x, float y, std::string text, Vector3 c, float scale = 1);

//check opengl errors
bool checkGLErrors();

std::string getPath();

Vector2 getDesktopSize( int display_index = 0 );


std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

#endif
