//
//  GUILost.cpp
//  COMP371_Framework
//
//  Created by Corentin Artaud on 2019-08-11.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "GUILost.h"

#include "GUIButton.h"

#include "ResourceManager.h"
#include "Renderer.h"
#include "TextRenderer.h"
#include "Game.h"
#include "AudioEngine.h"
#include "EventManager.h"


GUILost::GUILost() { }

bool GUILost::Initialize() {
    SetScale(glm::vec2(EventManager::GetScreenWidth(), EventManager::GetScreenHeight()));
    
    // start game
    std::shared_ptr<GUIButton> startNewGame(new GUIButton); // selection 0
    startNewGame->SetName("startNewGame");
    startNewGame->SetPosition(glm::vec2(mScale.x * 0.3f, mScale.y / 2 - 100.0f));
    startNewGame->SetScale(glm::vec2(mScale.x * 0.4f, 20.0f));
    startNewGame->SetForeColor(glm::vec3(1.0f));
    startNewGame->SetHoverColor(glm::vec4(0.0f));
    startNewGame->SetText("Start New Game");
    // quit game
    std::shared_ptr<GUIButton> quitGame(new GUIButton); // selection 2
    quitGame->SetName("quitGame");
    quitGame->SetPosition(glm::vec2(mScale.x * 0.35f, mScale.y / 2));
    quitGame->SetScale(glm::vec2(mScale.x * 0.4f, 20.0f));
    quitGame->SetForeColor(glm::vec3(1.0f));
    quitGame->SetHoverColor(glm::vec4(0.0f));
    quitGame->SetText("Quit Game");
    
    AddElement(startNewGame);
    AddElement(quitGame);
    
    return true;
}

void GUILost::Update(float dt) { }

void GUILost::RenderBackground(Renderer *renderer, TextRenderer *text) {
    // render background
    renderer->Render(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(EventManager::GetScreenWidth(), EventManager::GetScreenHeight()), 0.0f);
    // render title
    text->RenderText("YOU SNOOZE YOU LOSE", 230.0f, EventManager::GetScreenHeight() / 2 - 300.0f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
}

void GUILost::Activate() { }

void GUILost::Deactivate() { }

void GUILost::ButtonPressed(std::shared_ptr<GUIButton> button) {
    std::string buttonName = button->GetName();
    if (buttonName == "startNewGame") {
        Game::GetInstance()->SwitchStates(GAME_ACTIVE);
    } else if (buttonName == "quitGame") {
        Game::GetInstance()->SwitchStates(GAME_NULL);
    } else {
        // do nothing
    }
}
