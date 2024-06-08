#include "WinScreen.h"
#include "Game.h"
#include "DialogBox.h"

WinScreen::WinScreen() : UIScreen()
{
    Game::instance().setState(GameState::Pause);
    Game::instance().getInputSystem().setMouseRelativeMode(false);
    setTitle("WinTitle");
    addButton("PlayAgainButton", [this]() { close(); } );
    addButton("QuitButton", [this]() {
        new DialogBox("QuitText", [this]() { Game::instance().setState(GameState::Quit); });
    });
}

WinScreen::~WinScreen()
{
    Game::instance().setState(GameState::Gameplay);
    Game::instance().getInputSystem().setMouseRelativeMode(true);
}