#include "ControllerState.h"

#include <glew.h>

#include "InputSystem.h"

ControllerState::ControllerState() :
	leftStick(Vector2()),
	rightStick(Vector2()),
	leftTrigger(0.0f),
	rightTrigger(0.0f),
	isConnected(false)
{}

bool ControllerState::getButtonValue(SDL_GameControllerButton button) const
{
	return currentButtons[button] == 1;
}


ButtonState ControllerState::getButtonState(SDL_GameControllerButton button) const
{
	if (previousButtons[button] == 0) {
		if (currentButtons[button] == 0)
			return ButtonState::None;
		return ButtonState::Pressed;
	}
	if (currentButtons[button == 0])
		return ButtonState::Pressed;
	return ButtonState::Held;
}
	

