#include "LoseScreen.h"
#include "Game.h"
#include "DialogBox.h"

LoseScreen::LoseScreen() : UIScreen()
{
    Game::instance().setState(GameState::Pause);
    Game::instance().getInputSystem().setMouseRelativeMode(false);
    setTitle("LoseTitle");
    addButton("RetryButton", [this]() { close(); } );
    addButton("QuitButton", [this]() {close();});
}
LoseScreen::~LoseScreen()
{
    Game::instance().setState(GameState::Gameplay);
    Game::instance().getInputSystem().setMouseRelativeMode(true);
}
