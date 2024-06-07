#pragma once
#include <valarray>
#include <vector>

#include "AABB.h"
#include "ActivableDoor.h"
#include "Actor.h"
#include "CubeActor.h"
#include "ElevatorActor.h"
#include "EndPoint.h"
#include "SpriteComponent.h"
#include "Window.h"
#include "Vector2.h"
#include "RendererOGL.h"
#include "InputSystem.h"
#include "PhysicsSystem.h"
#include "PlaneActor.h"
#include "HUD.h"
#include "HUDHitPoint.h"
#include "ShootButton.h"

class ElevatorDoor;
using std::vector;

enum class GameState
{
	Gameplay, Pause, Quit
};

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
		Game() : state(GameState::Gameplay), isUpdatingActors(false), fps(nullptr), crosshair(nullptr) {}

	public:
		bool initialize();
		std::vector<std::vector<int>> loadLevel(const std::string& filename);
	
		void load();
		void loop();
		void unload();
		void close();

		GameState getState() const { return state; }
		void setState(GameState stateP);

		void addActor(Actor* actor);
		void removeActor(Actor* actor);
		RendererOGL& getRenderer() { return renderer; }
		
		PhysicsSystem& getPhysicsSystem() { return physicsSystem; }
		InputSystem& getInputSystem() { return inputSystem; }
		const vector<class UIScreen*>& getUIStack() { return UIStack; }
		void pushUI(class UIScreen* screen);
		HUD* getHUD() { return hud; }
		EndPoint* getEnd(){ return endPoint;}
		ElevatorActor* getElevator(){ return elevator;}

		// Game-specific
		void addPlane(class PlaneActor* plane);
		void removePlane(class PlaneActor* plane);
		void addCubes(class CubeActor* cube);
		void removeCube(class CubeActor* cube);
		void addDoor(class ActivableDoor* door);
		void removeDoor(class ActivableDoor* door);
		void addButton(class ShootButton* button);
		void removeButton(class ShootButton* button);
	
		vector<PlaneActor*>& getPlanes() { return planes; }
		vector<CubeActor*>& getCubes() { return cubes; }
		class FPSActor* getPlayer() { return fps; }
		HUDHitPoint* getHpHUD() const{ return hpHUD; }
		ElevatorDoor* getElevatorDoor() const{return elevatorDoor;}
		vector<ActivableDoor*>& getDoors() { return doors; }
		vector<ShootButton*>& getButtons() { return buttons; }

	private:
		void processInput();
		void update(float dt);
		void render();

		GameState state;
		Window window;
		RendererOGL renderer;

		InputSystem inputSystem;
		PhysicsSystem physicsSystem;
		vector<class UIScreen*> UIStack;
		HUD* hud;

		bool isUpdatingActors;
		vector<Actor*> actors;
		vector<Actor*> pendingActors;
	
		// Game specific

		class FPSActor* fps;
		class SpriteComponent* crosshair;
		vector<PlaneActor*> planes;
		vector<CubeActor*> cubes;
		HUDHitPoint* hpHUD;
		int previousHP = 4;
		EndPoint* endPoint;
		ElevatorActor* elevator;
		ElevatorDoor* elevatorDoor;
		vector<ActivableDoor*> doors;
		vector<ShootButton*> buttons;
	
	};

