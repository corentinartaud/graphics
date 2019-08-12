//
//  GUILevelMenu.cpp
//  COMP371_Framework
//
//  Created by Corentin Artaud on 2019-08-11.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "GUILevelMenu.h"
#include "GUIButton.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "EventManager.h"
#include "TextRenderer.h"
#include "AudioEngine.h"
#include "Game.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

GUILevelMenu::GUILevelMenu() { }

bool GUILevelMenu::Initialize() {
    // set scale
    SetScale(glm::vec2(EventManager::GetScreenWidth(), EventManager::GetScreenHeight()));
    
    // Resume Game
    std::shared_ptr<GUIButton> l1(new GUIButton);
    l1->SetName("l1");
    l1->SetPosition(glm::vec2(mScale.x * 0.39f, mScale.y / 2 - 50.0f));
    l1->SetScale(glm::vec2(mScale.x * 0.4f, 20.0f));
    l1->SetForeColor(glm::vec3(1.0f));
    l1->SetHoverColor(glm::vec4(0.0f));
    l1->SetText("Level 1");
    
    // Save Game
    std::shared_ptr<GUIButton> l2(new GUIButton);
    l2->SetName("l2");
    l2->SetPosition(glm::vec2(mScale.x * 0.39f, mScale.y / 2 + 50.0f));
    l2->SetScale(glm::vec2(mScale.x * 0.4f, 20.0f));
    l2->SetForeColor(glm::vec3(1.0f));
    l2->SetHoverColor(glm::vec4(0.0f));
    l2->SetText("Level 2");
    
    // Quit Game
    std::shared_ptr<GUIButton> l3(new GUIButton);
    l3->SetName("l3");
    l3->SetPosition(glm::vec2(mScale.x * 0.39f, mScale.y / 2 + 150.0f));
    l3->SetScale(glm::vec2(mScale.x * 0.4f, 20.0f));
    l3->SetForeColor(glm::vec3(1.0f));
    l3->SetHoverColor(glm::vec4(0.0f));
    l3->SetText("Level 3");
    
    AddElement(l1);
    AddElement(l2);
    AddElement(l3);
    
    return true;
}

void GUILevelMenu::Update(float dt) { }

void GUILevelMenu::RenderBackground(Renderer *renderer, TextRenderer *text){
    // render background
    renderer->Render(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(EventManager::GetScreenWidth(), EventManager::GetScreenHeight()), 0.0f);
    // render title
    text->RenderText("GOLDEN SPHERE", 320.0f, EventManager::GetScreenHeight() / 2 - 300.0f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
    // render title
    text->RenderText("CHOSE YOUR LEVEL", 280.0f, EventManager::GetScreenHeight() / 2 - 200.0f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
}

void GUILevelMenu::Activate() { }

void GUILevelMenu::Deactivate() { }

void GUILevelMenu::ButtonPressed(std::shared_ptr<GUIButton> button){
    std::string buttonName = button->GetName();
    if(buttonName == "l1"){
        Game::GetInstance()->SwitchStates(GAME_LEVEL_1);
    } else if (buttonName == "l2"){
        Game::GetInstance()->SwitchStates(GAME_LEVEL_2);
    } else if (buttonName == "l3") {
        Game::GetInstance()->SwitchStates(GAME_LEVEL_3);
    } else {
        // do nothing
    }
}
