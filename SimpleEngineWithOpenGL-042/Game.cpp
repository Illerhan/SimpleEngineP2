#include "Game.h"

#include <algorithm>
#include <sstream>

#include "Actor.h"
#include "Timer.h"
#include "Assets.h"
#include "MeshComponent.h"
#include "CubeActor.h"
#include "SphereActor.h"
#include "PlaneActor.h"
#include "FPSActor.h"
#include "TargetActor.h"
#include "PauseScreen.h"

bool Game::initialize()
{
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);

	bool isInputInit = inputSystem.initialize();
	bool isFontInit = Font::initialize();

	return isWindowInit && isRendererInit && isInputInit && isFontInit; // Return bool && bool && bool ...to detect error
}

std::vector<std::vector<int>> Game::loadLevel(const std::string& filename) {
	std::ifstream file(filename);
	std::vector<std::vector<int>> level;
	std::string line;

	if (!file.is_open()) {
		std::cerr << "Failed to open level file." << std::endl;
		return level;
	}

	while (std::getline(file, line)) {
		std::vector<int> row;
		std::istringstream iss(line);
		int value;
		while (iss >> value) {
			row.push_back(value);
		}
		level.push_back(row);
	}

	return level;
}

void Game::load()
{
	inputSystem.setMouseRelativeMode(true);

	Assets::loadShader("Res\\Shaders\\Sprite.vert", "Res\\Shaders\\Sprite.frag", "", "", "", "Sprite");
	Assets::loadShader("Res\\Shaders\\Phong.vert", "Res\\Shaders\\Phong.frag", "", "", "", "Phong");
	Assets::loadShader("Res\\Shaders\\BasicMesh.vert", "Res\\Shaders\\BasicMesh.frag", "", "", "", "BasicMesh");

	Assets::loadTexture(renderer, "Res\\Textures\\Default.png", "Default");
	Assets::loadTexture(renderer, "Res\\Textures\\Cube.png", "Cube");
	Assets::loadTexture(renderer, "Res\\Textures\\HealthBar.png", "HealthBar");
	Assets::loadTexture(renderer, "Res\\Textures\\Plane.png", "Plane");
	Assets::loadTexture(renderer, "Res\\Textures\\Radar.png", "Radar");
	Assets::loadTexture(renderer, "Res\\Textures\\Sphere.png", "Sphere");
	Assets::loadTexture(renderer, "Res\\Textures\\Crosshair.png", "Crosshair");
	Assets::loadTexture(renderer, "Res\\Textures\\RacingCar.png", "RacingCar");
	Assets::loadTexture(renderer, "Res\\Textures\\Rifle.png", "Rifle");
	Assets::loadTexture(renderer, "Res\\Textures\\Target.png", "Target");
	Assets::loadTexture(renderer, "Res\\Textures\\ButtonYellow.png", "ButtonYellow");
	Assets::loadTexture(renderer, "Res\\Textures\\ButtonBlue.png", "ButtonBlue");
	Assets::loadTexture(renderer, "Res\\Textures\\DialogBG.png", "DialogBG");
	Assets::loadTexture(renderer, "Res\\Textures\\Crosshair.png", "Crosshair");
	Assets::loadTexture(renderer, "Res\\Textures\\CrosshairRed.png", "CrosshairRed");
	Assets::loadTexture(renderer, "Res\\Textures\\Radar.png", "Radar");
	Assets::loadTexture(renderer, "Res\\Textures\\Blip.png", "Blip");
	Assets::loadTexture(renderer, "Res\\Textures\\RadarArrow.png", "RadarArrow");
	Assets::loadTexture(renderer, "Res\\Textures\\HitPoint.png", "HitPoint");

	Assets::loadMesh("Res\\Meshes\\Cube.gpmesh", "Mesh_Cube");
	Assets::loadMesh("Res\\Meshes\\Plane.gpmesh", "Mesh_Plane");
	Assets::loadMesh("Res\\Meshes\\Sphere.gpmesh", "Mesh_Sphere");
	Assets::loadMesh("Res\\Meshes\\Rifle.gpmesh", "Mesh_Rifle");
	Assets::loadMesh("Res\\Meshes\\RacingCar.gpmesh", "Mesh_RacingCar");
	Assets::loadMesh("Res\\Meshes\\Target.gpmesh", "Mesh_Target");

	Assets::loadFont("Res\\Fonts\\Carlito-Regular.ttf", "Carlito");
	Assets::loadText("Res\\Localization\\English.gptext");


	fps = new FPSActor();
	fps->setPosition(Vector3(0,0,100.f));
	
	// Load the level data from the file
	std::vector<std::vector<int>> level = loadLevel("level.txt");
	std::vector<std::vector<int>> level2 = loadLevel("level2.txt");

	// Iterate through the level data and create CubeActors where needed
	const Vector3 cubeSize = Vector3(500.0f,500.f,550.f); // Example size for each cube
	const float startX = -5000.f; // Starting position for the level
	const float startY = -5000.f;

	for (size_t y = 0; y < level.size(); ++y) {
		for (size_t x = 0; x < level[y].size(); ++x) {
			if (level[y][x] == 1) {
				CubeActor* cube = new CubeActor();
				cube->setPosition(Vector3(startX + x * cubeSize.x, startY + y * cubeSize.y, 0.0f));
				cube->setScale(cubeSize);
				//AABB cubeColl(Vector3(startX + x-0.5,startY + y  -0.5f,0),Vector3(startX+ x+ 0.5f, startY + y  + 0.5f, 0));
				//cubes.push_back(cubeColl);
			} else if (level[y][x] == 2) {
				std::cout << y << x << std::endl;
				//fps->setPosition(Vector3(x,y,650.f));
			} else if (level[y][x] == 3) {
				// Handle level end if needed
			}
		}
	}

	for (size_t y = 0; y < level2.size(); ++y) {
		for (size_t x = 0; x < level2[y].size(); ++x) {
			if (level2[y][x] == 1) {
				CubeActor* cube = new CubeActor();
				cube->setPosition(Vector3(startX + x * cubeSize.x, startY + y * cubeSize.y, 550));
				cube->setScale(cubeSize);
			} else if (level2[y][x] == 2) {
				std::cout << y << x << std::endl;
				//fps->setPosition(Vector3(x,y,75.f));
			} else if (level2[y][x] == 3) {
				// Handle level end if needed
			}
		}
	}
	
	CubeActor* a = new CubeActor();
	a->setPosition(Vector3(200.0f, 105.0f, 0.0f));
	a->setScale(Vector3(100.0f,100.0f,100.0f));
	
	Quaternion q(Vector3::unitY, -Maths::piOver2);
	q = Quaternion::concatenate(q, Quaternion(Vector3::unitZ, Maths::pi + Maths::pi / 4.0f));
	a->setRotation(q);

	// Floor and walls

	// Setup floor 1
	const float start = -5000.f;
	const float size = 550.f;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j <19; j++)
		{
			PlaneActor* p = new PlaneActor();
			p->setPosition(Vector3(start + i * size, start + j * size, -100.0f));
		}
	}

	// Setup floor 2

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j <19; j++)
		{
			PlaneActor* p = new PlaneActor();
			p->setPosition(Vector3(start + i * size, start + j * size, 550.0f));
		}
	}

	//Left/right walls
	q = Quaternion(Vector3::unitX, Maths::piOver2);
	for (int i = 0; i < 20; i++)
	{
		PlaneActor* p = new PlaneActor();
		p->setPosition(Vector3(start + i * size, start - size+50, 550.f));
		p->setRotation(q);
	
		p = new PlaneActor();
		p->setPosition(Vector3(start + i * size, -start + size-150, 550.f));
		p->setRotation(q);
	}
	
	q = Quaternion::concatenate(q, Quaternion(Vector3::unitZ, Maths::piOver2));
	// Forward/back walls
	for (int i = 0; i < 20; i++)
	{
		PlaneActor* p = new PlaneActor();
		p->setPosition(Vector3(start - size+50, start + i * size, 550.f));
		p->setRotation(q);
	
		p = new PlaneActor();
		p->setPosition(Vector3(-start + size+250, start + i * size, 550.f));
		p->setRotation(q);
	}

	//Left/right walls 2
	q = Quaternion(Vector3::unitX, Maths::piOver2);
	for (int i = 0; i < 20; i++)
	{
		PlaneActor* p = new PlaneActor();
		p->setPosition(Vector3(start + i * size, start - size+50, 0.0f));
		p->setRotation(q);
	
		p = new PlaneActor();
		p->setPosition(Vector3(start + i * size, -start + size-150, 0.0f));
		p->setRotation(q);
	}
	
	q = Quaternion::concatenate(q, Quaternion(Vector3::unitZ, Maths::piOver2));
	// Forward/back walls 2
	for (int i = 0; i < 20; i++)
	{
		PlaneActor* p = new PlaneActor();
		p->setPosition(Vector3(start - size+50, start + i * size, 0.0f));
		p->setRotation(q);
	
		p = new PlaneActor();
		p->setPosition(Vector3(-start + size+250, start + i * size, 0.0f));
		p->setRotation(q);
	}

	// Setup lights
	renderer.setAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	DirectionalLight& dir = renderer.getDirectionalLight();
	dir.direction = Vector3(0.0f, -0.707f, -0.707f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	// Create spheres with audio components playing different sounds
	SphereActor* soundSphere = new SphereActor();
	soundSphere->setPosition(Vector3(500.0f, -75.0f, 0.0f));
	soundSphere->setScale(Vector3(1,1,1));


	// HUD
	hud = new HUD();
	/*
	Actor* crosshairActor = new Actor();
	crosshairActor->setScale(2.0f);
	crosshair = new SpriteComponent(crosshairActor, Assets::getTexture("Crosshair"));
	*/

	// Start music

	TargetActor* t = new TargetActor();
	t->setPosition(Vector3(1450.0f, 0.0f, 100.0f));
	t = new TargetActor();
	t->setPosition(Vector3(1450.0f, 0.0f, 400.0f));
	t = new TargetActor();
	t->setPosition(Vector3(1450.0f, -500.0f, 200.0f));
	t = new TargetActor();
	t->setPosition(Vector3(1450.0f, 500.0f, 200.0f));
}

void Game::processInput()
{
	inputSystem.preUpdate();

	// SDL Event
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		bool isRunning = inputSystem.processEvent(event);
		if (!isRunning) state = GameState::Quit;
	}

	inputSystem.update();
	const InputState& input = inputSystem.getInputState();

	if (state == GameState::Gameplay)
	{
		// Escape: pause game
		if (input.keyboard.getKeyState(SDL_SCANCODE_ESCAPE) == ButtonState::Released)
		{
			new PauseScreen();
			return;
		}

		// Actor input
		isUpdatingActors = true;
		for (auto actor : actors)
		{
			actor->processInput(input);
		}
		isUpdatingActors = false;
	}
	else
	{
		if (!UIStack.empty())
		{
			UIStack.back()->processInput(input);
		}
	}
}

void Game::update(float dt)
{
	// Update audio

	if (state == GameState::Gameplay)
	{
		// Update actors 
		isUpdatingActors = true;
		for (auto actor : actors)
		{
			actor->update(dt);
		}
		isUpdatingActors = false;

		// Move pending actors to actors
		for (auto pendingActor : pendingActors)
		{
			pendingActor->computeWorldTransform();
			actors.emplace_back(pendingActor);
		}
		pendingActors.clear();

		// Delete dead actors
		vector<Actor*> deadActors;
		for (auto actor : actors)
		{
			if (actor->getState() == Actor::ActorState::Dead)
			{
				deadActors.emplace_back(actor);
			}
		}
		for (auto deadActor : deadActors)
		{
			delete deadActor;
		}
	}

	// Update UI screens
	for (auto ui : UIStack)
	{
		if (ui->getState() == UIState::Active)
		{
			ui->update(dt);
		}
	}
	// Delete any UIScreens that are closed
	auto iter = UIStack.begin();
	while (iter != UIStack.end())
	{
		if ((*iter)->getState() == UIState::Closing)
		{
			delete* iter;
			iter = UIStack.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void Game::render()
{
	renderer.beginDraw();
	renderer.draw();
	renderer.endDraw();
}

void Game::loop()
{
	Timer timer;
	float dt = 0;
	while (state != GameState::Quit)
	{
		float dt = timer.computeDeltaTime() / 1000.0f;
		processInput();
		update(dt);
		render();
		timer.delayTime();
	}
}

void Game::unload()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!actors.empty())
	{
		delete actors.back();
	}

	// Resources
	Assets::clear();
}

void Game::close()
{
	Font::close();
	inputSystem.close();
	renderer.close();
	window.close();
	SDL_Quit();
}

void Game::setState(GameState stateP)
{
	state = stateP;
}

void Game::addActor(Actor* actor)
{
	if (isUpdatingActors)
	{
		pendingActors.emplace_back(actor);
	}
	else
	{
		actors.emplace_back(actor);
	}
}

void Game::removeActor(Actor* actor)
{
	// Erase actor from the two vectors
	auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
	if (iter != end(pendingActors))
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, end(pendingActors) - 1);
		pendingActors.pop_back();
	}
	iter = std::find(begin(actors), end(actors), actor);
	if (iter != end(actors))
	{
		std::iter_swap(iter, end(actors) - 1);
		actors.pop_back();
	}
}

void Game::pushUI(UIScreen* screen)
{
	UIStack.emplace_back(screen);
}

void Game::addPlane(PlaneActor* plane)
{
	planes.emplace_back(plane);
}

void Game::removePlane(PlaneActor* plane)
{
	auto iter = std::find(begin(planes), end(planes), plane);
	planes.erase(iter);
}

void Game::addCubes(CubeActor* cube)
{
	cubes.emplace_back(cube);
}

void Game::removeCube(CubeActor* cube)
{
	auto iter = std::find(begin(cubes), end(cubes), cube);
	cubes.erase(iter);
}
