#pragma once
#include <vector>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Window.h"
#include "Vector2.h"
#include "RendererOGL.h"
#include "AudioSystem.h"
#include "InputSystem.h"
#include "PhysicsSystem.h"
#include "PlaneActor.h"
#include "CubeActor.h"

using std::vector;

class Game
{
public:
	static Game& instance()
	{
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

private:
	Game() : isRunning(true), isUpdatingActors(false), fps(nullptr), crosshair(nullptr) {}

public:
	bool initialize();
	void load();
	void loop();
	void unload();
	void close();

	void addActor(Actor* actor);
	void removeActor(Actor* actor);
	
	RendererOGL& getRenderer() { return renderer; }
	//AudioSystem& getAudioSystem() { return audioSystem; }
	PhysicsSystem& getPhysicsSystem() { return physicsSystem; }

	// Game-specific
	void addPlane(class PlaneActor* plane);
	void addCubes(CubeActor* cube);
	void removePlane(class PlaneActor* plane);
	void initiateGame();
	void deleteCubes(vector<CubeActor*>& cubes);
	vector<CubeActor*>& getCubes() {return cubes;}
	vector<PlaneActor*>& getPlanes() { return planes; }
	class CubeActor* getArrow() {return arrow; }
	void setScore(){score += 1;}
	void setScore(int scoreP){score = scoreP;}
	int getScore(){return score;}


private:
	void processInput();
	void update(float dt);
	void render();
	bool isRunning;
	Window window;
	RendererOGL renderer;
	//AudioSystem audioSystem;
	InputSystem inputSystem;
	PhysicsSystem physicsSystem;

	bool isUpdatingActors;
	bool directionSelected = false;
	vector<Actor*> actors;
	vector<Actor*> pendingActors;

	// Game specific
	//SoundEvent musicEvent;
	class FPSActor* fps;
	class FollowActor* follow;
	class CubeActor* arrow;
	class SpriteComponent* crosshair;
	vector<PlaneActor*> planes;
	vector<CubeActor*> cubes;
	class Quaternion q();
	int score;

};

