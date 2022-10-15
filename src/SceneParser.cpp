#include "SceneParser.h"

Scene* SceneParser::ParseData(const char* f) {

	TextParser t;
	ParseObject parse_object;
	ParseObjectData parse_object_data;


	if (t.create(f) == false) {
		std::cout << "ARCHIVO NO ABIERTO!" << std::endl;
		return 0;
	}
	else {

		t.seek("RESOURCES");
		this->n_resources = t.getint();

		for (int i = 0; i < this->n_resources; i++) {
			std::string type;
			std::string name;
			std::string path;

			t.seek("RESOURCE");
			type = t.getword();
			t.seek("NAME");
			name = t.getword();
			t.seek("PATH");

			char * type_convert = new char[type.size() + 1];
			std::copy(type.begin(), type.end(), type_convert);
			type_convert[type.size()] = '\0';

			if (strcmp(type_convert,"SHADER") == 0) {
				std::string temp = t.getword();
				temp = temp + "-";
				temp = temp + t.getword();
				temp = temp + "-";
				path = temp;
			}else{
				path = t.getword();
			}

			parse_object.type = type_convert;

			char * name_convert = new char[name.size() + 1];
			std::copy(name.begin(), name.end(), name_convert);
			name_convert[name.size()] = '\0';

			parse_object.name = name_convert;

			char * path_convert = new char[path.size() + 1];
			std::copy(path.begin(), path.end(), path_convert);
			path_convert[path.size()] = '\0';

			parse_object.path = path_convert;

			this->resources.push_back(parse_object);
		}

		t.seek("OBJECTS");
		this->n_objects = t.getint();

		for (int i = 0; i < this->n_objects; i++) {

			std::string object;
			std::string name;
			std::string mesh;
			std::string shader;
			std::string texture;

			t.seek("OBJECT");
			object = t.getword();

			t.seek("NAME");
			name = t.getword();

			t.seek("MESH");
			mesh = t.getword();

			t.seek("SHADER");
			shader = t.getword();

			t.seek("TEXTURE");
			texture = t.getword();

			t.seek("POSITION");
			float f1 = (float)t.getfloat();
			float f2 = (float)t.getfloat();
			float f3 = (float)t.getfloat();
			Vector3 pos = Vector3(f1, f2, f3);
			parse_object_data.position = pos;
		
			t.seek("ROTATION");
			f1 = (float)t.getfloat();
			f2 = (float)t.getfloat();
			f3 = (float)t.getfloat();
			Vector3 rot = Vector3(f1, f2, f3);
			parse_object_data.rotation = rot;

			t.seek("SCALE");
			f1 = t.getfloat();
			f2 = t.getfloat();
			f3 = t.getfloat();
			Vector3 scale = Vector3(f1, f2, f3);
			parse_object_data.scale = scale;

			char * object_convert = new char[object.size() + 1];
			std::copy(object.begin(), object.end(), object_convert);
			object_convert[object.size()] = '\0';

			parse_object_data.object = object_convert;

			char * name_convert1 = new char[name.size() + 1];
			std::copy(name.begin(), name.end(), name_convert1);
			name_convert1[name.size()] = '\0';

			parse_object_data.name = name_convert1;

			char * mesh_convert = new char[mesh.size() + 1];
			std::copy(mesh.begin(), mesh.end(), mesh_convert);
			mesh_convert[mesh.size()] = '\0';

			parse_object_data.mesh = mesh_convert;

			char * shader_convert = new char[shader.size() + 1];
			std::copy(shader.begin(), shader.end(), shader_convert);
			shader_convert[shader.size()] = '\0';

			parse_object_data.shader = shader_convert;

			char * texture_convert = new char[texture.size() + 1];
			std::copy(texture.begin(), texture.end(), texture_convert);
			texture_convert[texture.size()] = '\0';

			parse_object_data.texture = texture_convert;

			if (!strcmp(parse_object_data.object, "GAMEOBJECTENEMY")) {
				t.seek("WAYPOINTS");
				int num_waypoints = t.getint();
				for (int i = 0; i < num_waypoints; i++) {
					float x = t.getfloat();
					float y = t.getfloat();
					float z = t.getfloat();
					parse_object_data.waypoints.push_back(Vector3(x, y, z));
				}
			}

			this->objects.push_back(parse_object_data);
		}

		escena = loadEscena();
		return escena;

	}
}

Scene* SceneParser::loadEscena() {

	ResourceM* resources = new ResourceM();

	char * first_path;
	char * second_path;

	for (int i = 0; i < this->n_resources; i++) {

		int n = 0;

		if (strcmp(this->resources[i].type, "TEXTURE") == 0) {
			n = 1;
		}

		if (strcmp(this->resources[i].type, "MESH") == 0) {
			n = 2;
		}

		if (strcmp(this->resources[i].type, "SHADER") == 0) {
			n = 3;
			
			char * temp = strdup(this->resources[i].path);
			char * aux = std::strtok(temp, "-");
			first_path = aux;
			aux = std::strtok(NULL, "-");
			second_path = aux;
			
		}


		switch(n){
			case 1:
				resources->loadTexture(this->resources[i].name, this->resources[i].path);
				break;

			case 2:
				resources->loadMesh(this->resources[i].name, this->resources[i].path);
				break;

			case 3:
				resources->loadShader(this->resources[i].name, first_path, second_path);
				break;
			default:
				std::cout << "ERROR CARGANDO ASSETS (1)" << std::endl;
				break;

		}
	}

	GameObjectPlayer* nouJugador;
	GameObjectEnemy* nouEnemic;
	GameObjectMesh* novaMesh;
	GameObjectEnvironment* nouEnvironment;


	for (int i = 0; i < (int)this->objects.size(); i++) {

		int n = 0;

		if (strcmp(this->objects[i].object, "GAMEOBJECTPLAYER") == 0) {
			n = 1;
		}

		if (strcmp(this->objects[i].object, "GAMEOBJECTENEMY") == 0) {
			n = 2;
		}

		if (strcmp(this->objects[i].object, "GAMEOBJECTMESH") == 0) {
			n = 3;
		}

		if (strcmp(this->objects[i].object, "GAMEOBJECTENVIRONMENT") == 0) {
			n = 4;
		}


		switch (n) {
			case 1:
				nouJugador = new GameObjectPlayer();
				nouJugador->name = this->objects[i].name;
				nouJugador->mesh = resources->getMesh(this->objects[i].mesh);
				nouJugador->shader = resources->getShader(this->objects[i].shader);
				nouJugador->texture = resources->getTexture(this->objects[i].texture);
				nouJugador->model.traslate(this->objects[i].position.x, this->objects[i].position.y, this->objects[i].position.z);
				nouJugador->model.rotateVector(this->objects[i].rotation);
				nouJugador->model.scale(this->objects[i].scale.x, this->objects[i].scale.y, this->objects[i].scale.z);
				nouJugador->is_collider = true;
				nouJugador->setCollisionModel();
				Game::instance->player.push_back(nouJugador);
				break;

			case 2:
				nouEnemic = new GameObjectEnemy();
				nouEnemic->name = this->objects[i].name;
				nouEnemic->mesh = resources->getMesh(this->objects[i].mesh);
				nouEnemic->shader = resources->getShader(this->objects[i].shader);
				nouEnemic->texture = resources->getTexture(this->objects[i].texture);
				nouEnemic->model.traslate(this->objects[i].position.x, this->objects[i].position.y, this->objects[i].position.z);
				nouEnemic->model.rotateVector(this->objects[i].rotation);
				nouEnemic->model.scale(this->objects[i].scale.x, this->objects[i].scale.y, this->objects[i].scale.z);
				nouEnemic->waypoints = this->objects[i].waypoints;
				nouEnemic->is_collider = true;
				nouEnemic->setCollisionModel();
				Game::instance->enemies.push_back(nouEnemic);
				break;

			case 3:
				novaMesh = new GameObjectMesh();
				novaMesh->name = this->objects[i].name;
				novaMesh->mesh = resources->getMesh(this->objects[i].mesh);
				novaMesh->shader = resources->getShader(this->objects[i].shader);
				novaMesh->texture = resources->getTexture(this->objects[i].texture);
				novaMesh->model.traslate(this->objects[i].position.x, this->objects[i].position.y, this->objects[i].position.z);
				novaMesh->model.rotateVector(this->objects[i].rotation);
				novaMesh->is_collider = true;
				novaMesh->setCollisionModel();
				novaMesh->model.scale(this->objects[i].scale.x, this->objects[i].scale.y, this->objects[i].scale.z);
				Game::instance->meshes.push_back(novaMesh);
				break;

			case 4:
				nouEnvironment = new GameObjectEnvironment();
				nouEnvironment->name = this->objects[i].name;
				nouEnvironment->mesh = resources->getMesh(this->objects[i].mesh);
				nouEnvironment->shader = resources->getShader(this->objects[i].shader);
				nouEnvironment->texture = resources->getTexture(this->objects[i].texture);
				Game::instance->sky.push_back(nouEnvironment);
				break;

			default:
				std::cout << "Error loading assets (1)" << std::endl;

				break;

		}
	}

	escena = new Scene();

	escena->camera = new Camera();
	escena->camera->lookAt(Vector3(0, 25, 25), Vector3(0, 0, 0), Vector3(0, 1, 0)); //position the camera and point to 0,0,0
	escena->camera->setPerspective(70.0f, (float)800 / (float)600, 0.1f, 1000.0f); //set the projection, we want to be perspective

	return escena;
	
}