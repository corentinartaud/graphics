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
#include "GLFW/glfw3.h"

using namespace std;

GUIMainMenu::GUIMainMenu() { }

bool GUIMainMenu::Initialize() {
    currentSelection = 0;
    // start game
    std::shared_ptr<GUIButton> startGame(new GUIButton); // selection 0
<<<<<<< HEAD
    startGame->SetHoverColor(glm::vec4(1.0f));
    startGame->SetText("Start Game");
    // continue (?) will need to cache if we do
    std::shared_ptr<GUIButton> continueGame(new GUIButton); // selection 1
    continueGame->SetHoverColor(glm::vec4(1.0f));
    continueGame->SetText("Continue");
    // start game
    std::shared_ptr<GUIButton> quitGame(new GUIButton); // selection 2
    quitGame->SetHoverColor(glm::vec4(1.0f));
=======
    startGame->SetName("startGame");
    startGame->SetPosition(glm::vec2(mScale.x * 0.35f, mScale.y / 2 - 100.0f));
    startGame->SetScale(glm::vec2(mScale.x * 0.4f, 20.0f));
    startGame->SetForeColor(glm::vec3(1.0f));
    startGame->SetHoverColor(glm::vec4(0.0f));
    startGame->SetText("Start Game");
    // continue (?) will need to cache if we do
    std::shared_ptr<GUIButton> continueGame(new GUIButton); // selection 1
    continueGame->SetName("continueGame");
    continueGame->SetPosition(glm::vec2(mScale.x * 0.35f, mScale.y / 2));
    continueGame->SetScale(glm::vec2(mScale.x * 0.4f, 20.0f));
    continueGame->SetForeColor(glm::vec3(1.0f));
    continueGame->SetHoverColor(glm::vec4(0.0f));
    continueGame->SetText("Continue");
    // start game
    std::shared_ptr<GUIButton> quitGame(new GUIButton); // selection 2
    quitGame->SetName("quitGame");
    quitGame->SetPosition(glm::vec2(mScale.x * 0.35f, mScale.y / 2 + 100.0f));
    quitGame->SetScale(glm::vec2(mScale.x * 0.4f, 20.0f));
    quitGame->SetForeColor(glm::vec3(1.0f));
    quitGame->SetHoverColor(glm::vec4(0.0f));
>>>>>>> bf8cac53ce5ecb9bd4526344924f697b542a919c
    quitGame->SetText("Quit Game");
    
    mBackgroundTexture = &ResourceManager::GetTexture("menu_background");
    return true;
}

void GUIMainMenu::Update(float dt) {
    
    
}

void GUIMainMenu::RenderBackground() {
    
    
}

void GUIMainMenu::select(){
    switch(currentSelection){
        
        case 0: ; // start game
        case 1: ; // continue game
        case 2: ; // exit game
    }
};


void GUIMainMenu::changeMenuState(){
    if(GLFW_KEY_W | GLFW_KEY_UP){
        selectionUp();
    };
    if(GLFW_KEY_S | GLFW_KEY_DOWN){
        selectionDown();
    };
    if(GLFW_KEY_ENTER){
        select();
    };
};

void GUIMainMenu::selectionUp(){
    currentSelection--;
    
    if(currentSelection == -1){
        currentSelection = 2;
    };
};

void GUIMainMenu::selectionDown(){
    currentSelection++;
    
    if(currentSelection == 3){
        currentSelection = 0;
    };
};
