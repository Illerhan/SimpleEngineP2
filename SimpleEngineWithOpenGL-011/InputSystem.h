#pragma once
#include "KeyboardState.h"
#include "MouseState.h"
#include <SDL_events.h>

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

};
