/*  by Alun Evans 2016 LaSalle (alunthomasevasevans@gmail.com)
	based on framework by Javi Agenjo 2013 UPF  javi.agenjo@gmail.com
	This class encapsulates the game, is in charge of creating the game, getting the user input, process the update and render.
*/

#ifndef GAME_H
#define GAME_H

#include "includes.h"
#include "camera.h"
#include "ResourceM.h"
#include "utils.h"
#include "rendertotexture.h"
#include <cmath>
#include "SceneParser.h"
#include "Scene.h"
#include "Menu.h"


#include "GameObjectPlayer.h"
#include "GameObjectMesh.h"
#include "GameObjectEnvironment.h"
#include "GameObjectEnemy.h"



class Game {
public:
	static Game* instance;

	std::vector<GameObjectMesh*> meshes;
	std::vector<GameObjectEnemy*> enemies;
	std::vector<GameObjectEnvironment*> sky;
	std::vector<GameObjectPlayer*> player;
	ResourceM* rm;
	Scene* scene;

	int seconds = 20;
	boolean start;


	int inici = 0;
	int opcio = 0;
	float time0, time1;

	int loser;
	int p = 0;

	


	//window
	SDL_Window* window;
	int window_width;
	int window_height;

	float time;

	//keyboard state
	const Uint8* keystate;

	//mouse state
	int mouse_state; //tells which buttons are pressed
	Vector2 mouse_position; //last mouse position
	Vector2 mouse_delta; //mouse movement in the last frame
	bool mouse_locked; //tells if the mouse is locked (not seen)

	Camera* camera; //our global camera

	bool down = false;
	bool fi = false;

	int dificultat = 0;

	// constructor
	Game(SDL_Window* window);
	// descructor
	~Game();
	void init();
	void render(void);
	void update(double dt);

	void onKeyPressed(SDL_KeyboardEvent event);
	void onMouseButton(SDL_MouseButtonEvent event);
	void onResize(SDL_Event e);

	void setWindowSize(int width, int height);
};


#endif
