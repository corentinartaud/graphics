//
//  GUIPauseMenu.cpp
//  COMP371_Framework
//
//  Created by Steven Anthony on 2019-08-10.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "GUIPauseMenu.h"
#include "GUIButton.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "EventManager.h"
#include "TextRenderer.h"
#include "AudioEngine.h"
#include "Game.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

using namespace std;

GUIPauseMenu::GUIPauseMenu() { }

bool GUIPauseMenu::Initialize() {
    // set scale
    SetScale(glm::vec2(EventManager::GetScreenWidth(), EventManager::GetScreenHeight()));
    
    // Resume Game
    std::shared_ptr<GUIButton> resumeGame(new GUIButton);
    resumeGame->SetName("resumeGame");
    resumeGame->SetPosition(glm::vec2(mScale.x * 0.35f, mScale.y / 2 - 100.0f));
    resumeGame->SetScale(glm::vec2(mScale.x * 0.4f, 20.0f));
    resumeGame->SetForeColor(glm::vec3(1.0f));
    resumeGame->SetHoverColor(glm::vec4(0.0f));
    resumeGame->SetText("Resume Game");
    
    // Resume Game
    std::shared_ptr<GUIButton> changeLevel(new GUIButton);
    changeLevel->SetName("changeLevel");
    changeLevel->SetPosition(glm::vec2(mScale.x * 0.35f, mScale.y / 2));
    changeLevel->SetScale(glm::vec2(mScale.x * 0.4f, 20.0f));
    changeLevel->SetForeColor(glm::vec3(1.0f));
    changeLevel->SetHoverColor(glm::vec4(0.0f));
    changeLevel->SetText("Change Level");
    
    
    // Save Game
    std::shared_ptr<GUIButton> saveGame(new GUIButton);
    saveGame->SetName("saveGame");
    saveGame->SetPosition(glm::vec2(mScale.x * 0.35f, mScale.y / 2 + 100.0f));
    saveGame->SetScale(glm::vec2(mScale.x * 0.4f, 20.0f));
    saveGame->SetForeColor(glm::vec3(1.0f));
    saveGame->SetHoverColor(glm::vec4(0.0f));
    saveGame->SetText("Save Game");
    
    // Quit Game
    std::shared_ptr<GUIButton> quitGame(new GUIButton);
    quitGame->SetName("quitGame");
    quitGame->SetPosition(glm::vec2(mScale.x * 0.35f, mScale.y / 2 + 200.0f));
    quitGame->SetScale(glm::vec2(mScale.x * 0.4f, 20.0f));
    quitGame->SetForeColor(glm::vec3(1.0f));
    quitGame->SetHoverColor(glm::vec4(0.0f));
    quitGame->SetText("Quit Game");

    AddElement(resumeGame);
    AddElement(saveGame);
    AddElement(changeLevel);
    AddElement(quitGame);
    
    return true;
}

void GUIPauseMenu::Update(float dt) { }

void GUIPauseMenu::RenderBackground(Renderer *renderer, TextRenderer *text){
    // render background
    renderer->Render(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(EventManager::GetScreenWidth(), EventManager::GetScreenHeight()), 0.0f);
    // render title
    text->RenderText("PAUSED GAME", 360.0f, EventManager::GetScreenHeight() / 2 - 300.0f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
}

void GUIPauseMenu::Activate() {
    Game::GetInstance()->GetAudio()->StopAll();
#if defined(PLATFORM_OSX)	
	Game::GetInstance()->GetAudio()->Play("Sounds/the_final_battle.wav", true);
#else
	Game::GetInstance()->GetAudio()->Play("../Assets/Sounds/the_final_battle.wav", true);
#endif
    
}

void GUIPauseMenu::Deactivate() {
	if (!(Game::GetInstance()->GetGameState() == GameState::GAME_LEVEL))
	{
#if defined(PLATFORM_OSX)	
		Game::GetInstance()->GetAudio()->Stop("Sounds/the_final_battle.wav");
#else
		Game::GetInstance()->GetAudio()->Stop("../Assets/Sounds/the_final_battle.wav");
#endif
	}
}

void GUIPauseMenu::ButtonPressed(std::shared_ptr<GUIButton> button){
    std::string buttonName = button->GetName();
    if(buttonName == "resumeGame"){
        Game::GetInstance()->SwitchStates(GAME_ACTIVE);
    } else if (buttonName == "quitGame"){
        Game::GetInstance()->SwitchStates(GAME_NULL);
    } else if (buttonName == "saveGame") {
        // to be implemented
    } else  if (buttonName == "changeLevel") {
        Game::GetInstance()->SwitchStates(GAME_LEVEL);
    } else {
        // do nothing
    }
}



