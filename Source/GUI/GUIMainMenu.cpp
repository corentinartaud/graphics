//
//  GUIGameMenu.cpp
//  COMP371_Framework
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "GUIMainMenu.h"

#include "GUIButton.h"
#include "ResourceManager.h"

GUIMainMenu::GUIMainMenu() { }

bool GUIMainMenu::Initiailize() {
    // start game
    std::shared_ptr<GUIButton> startGame(new GUIButton);
    startGame->SetHoverColor(glm::vec4(1.0f));
    startGame->SetText("Start Game");
    // continue (?) will need to cache if we do
    std::shared_ptr<GUIButton> continueGame(new GUIButton);
    continueGame->SetHoverColor(glm::vec4(1.0f));
    continueGame->SetText("Continue");
    // start game
    std::shared_ptr<GUIButton> quitGame(new GUIButton);
    quitGame->SetHoverColor(glm::vec4(1.0f));
    quitGame->SetText("Quit Game");
    
    mBackgroundTexture = &ResourceManager::GetTexture("menu_background");
    return true;
}

void GUIMainMenu::Update(float dt) { }

void GUIMainMenu::RenderBackground() { }

void GUIMainMenu::ButtonPressed(GUIButton button) {
    
}
