#include "game.h"

float angle = 0;
Game* Game::instance = NULL;
RenderToTexture* rt = NULL;

Game::Game(SDL_Window* window)
{
	this->window = window;
	instance = this;

	SDL_GetWindowSize(window, &window_width, &window_height);

	keystate = NULL;
	mouse_locked = false;
	start = false;
}


void Game::init()
{

	SceneParser* sp = new SceneParser();
	scene = sp->ParseData("data/scenefile.txt");

	for (size_t i = 0; i < enemies.size(); i++) {
		enemies[i]->selectWaypoint();
	}

	SDL_ShowCursor(!mouse_locked); //hide or show the mouse
}

void Game::render(void)
{
	Menu* m;

	if (start != true) {
		
		if (inici == 0) {
			m = new Menu(window_width, window_height);
			m->carregarJuga();
			SDL_GL_SwapWindow(this->window);
			inici = 1;
		}

		if (keystate[SDL_SCANCODE_RETURN]) {
			SDL_GL_SwapWindow(this->window);
			Game::init();
			start = true;
			loser = 0;
			dificultat = 1;
			time0 = (float)clock();
		}

	}

	if (start == true) {

		time1 = (float)clock();
		if ((time1 - time0) / (float)CLOCKS_PER_SEC >= 1) { 
			seconds--;
			time0 = (float)clock();
			
			if (seconds == 0 || seconds < 0) {
				loser = 1;
			}
		}

		glClearColor(0.0, 0.0, 0.0, 1.0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (size_t i = 0; i < sky.size(); i++) {
			sky[i]->render();
		}

		for (size_t i = 0; i < enemies.size(); i++) {
			enemies[i]->render();
		}

		for (size_t i = 0; i < meshes.size(); i++) {
			meshes[i]->render();
		}

		player[0]->render();

		if (loser == 1) {
			std::cout << "Punts: " << p << std::endl;
			start = false;
			fi = true;
		}

		SDL_GL_SwapWindow(this->window);
	}
	if (fi == true) {
		SDL_GL_SwapWindow(this->window);
		if (keystate[SDL_SCANCODE_RETURN]) {
			exit(0);
		}
		
	}
	
}

void Game::update(double seconds_elapsed)
{

	time1 = (float)clock();

	if ((time1 - time0) / (float)CLOCKS_PER_SEC >= 1) {

		time0 = (float)clock();
		if (seconds%10 == 0) {
			!down;
		}
	}
	double speed = seconds_elapsed * 200; 

	if (mouse_locked)
	{
		int center_x = (int)floor(window_width*0.5f);
		int center_y = (int)floor(window_height*0.5f);
		SDL_WarpMouseInWindow(this->window, center_x, center_y);

		this->mouse_position.x = (float)center_x;
		this->mouse_position.y = (float)center_y;
	}

	for (size_t i = 0; i < enemies.size(); i++) {
		enemies[i]->update(seconds_elapsed, down);
	}

	if (keystate[SDL_SCANCODE_UP]) player[0]->up();
	if (keystate[SDL_SCANCODE_DOWN]) player[0]->down();
	if (keystate[SDL_SCANCODE_LEFT]) player[0]->left();
	if (keystate[SDL_SCANCODE_RIGHT]) player[0]->right();

	Vector3 dest = Vector3(player[0]->getPosition().x, player[0]->getPosition().y + 40, player[0]->getPosition().z + 90);
	Vector3 playerPosition = player[0]->getPosition();
	Vector3 front = player[0]->model.frontVector().normalize();
	Vector3 upVector = player[0]->model.topVector().normalize();

	Vector3 look = playerPosition + (front * 90) + (upVector * 20);

	look = scene->camera->eye.lerp(look, 0.5);

	scene->camera->lookAt(
		look,
		playerPosition,
		upVector);
	scene->camera->setPerspective(80.0f, (float)window_width / (float)window_height, 0.5f, 10000.0f); //set the projection, we want to be perspective

	player[0]->update(seconds_elapsed);

	angle += (float)seconds_elapsed * 25;


	GameObjectPlayer* A;
	GameObjectEnemy* B;

	for (int i = 0; i < enemies.size(); i++) {
		A = player[0];
		B = enemies[i];

			A->collision_model->setTransform(A->model.m);
			B->collision_model->setTransform(B->model.m);

			bool collision = A->collision_model->collision(B->collision_model);

			if (collision) {
				p++;

			}
		
	}

}

void Game::setWindowSize(int width, int height)
{


	glViewport(0, 0, width, height);
	window_width = width;
	window_height = height;
}

void Game::onKeyPressed(SDL_KeyboardEvent event)
{
	switch (event.keysym.sym)
	{
	case SDLK_ESCAPE: exit(0);
	}
}


void Game::onMouseButton(SDL_MouseButtonEvent event)
{
	if (event.button == SDL_BUTTON_MIDDLE)
	{
		mouse_locked = !mouse_locked;
		SDL_ShowCursor(!mouse_locked);
	}
}