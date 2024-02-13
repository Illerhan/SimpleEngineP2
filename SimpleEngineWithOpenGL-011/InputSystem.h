#pragma once
#include "KeyboardState.h"
#include "MouseState.h"
#include <SDL_events.h>

#include "ControllerState.h"

enum class ButtonState
{
	None,
	Pressed,
	Released,
	Held
};

struct InputState
{
	KeyboardState keyboard;
	MouseState mouse;
	ControllerState	controller;
};

class InputSystem
{
public:
	InputSystem();

	bool processEvent(SDL_Event& event); // Returns isRunning status

	bool initialize();
	void close();

	const InputState getInputState() const { return inputState; }
	bool getIsCursorDisplayed() const { return isCursorDisplayed; }
	void setMouseCursor(bool isCursorDisplayedP);
	void setMouseRelativeMode(bool isMouseRelativeOnP);

	void preUpdate();
	void update();

private:
	InputState inputState;
	bool isCursorDisplayed;
	float filter1D(int input);
	Vector2 filter2D(int inputX, int inputY);

	SDL_GameController* controller;

};

constexpr int CONTROLLER_DEAD_ZONE_1D = 250;
constexpr float CONTROLLER_DEAD_ZONE = 8000.f;
constexpr int CONTROLLER_MAX_VALUE = 30000;
