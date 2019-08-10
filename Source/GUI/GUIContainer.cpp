//
//  GUIContainer.cpp
//  COMP371_Framework
//
//  Created by Corentin Artaud on 2019-08-09.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "GUIContainer.h"

#include "ResourceManager.h"
#include "TextRenderer.h"

GUIContainer::GUIContainer() { }

void GUIContainer::AddElement(std::shared_ptr<GUIElement> element) {
    // check if it doesn't already exist
    for (auto it = mElements.begin(); it != mElements.end(); ++it)
        if((*it) == element)
            return;
    mElements.push_back(element);
}

void GUIContainer::RemoveElement(std::shared_ptr<GUIElement> element) {
    mElements.erase(std::remove(mElements.begin(), mElements.end(), element), mElements.end());
}

void GUIContainer::SetActive(bool active) {
    bool changed = mIsActive != active;
    mIsActive = active;
    if(mIsActive)
        Activate();
    else if(changed)
        Deactivate();
}
void GUIContainer::SetPosition(glm::vec2 position) {
    mPosition = position;
}
void GUIContainer::SetScale(glm::vec2 scale) {
    mScale = scale;
}

void GUIContainer::Activate() { }

void GUIContainer::Deactivate() { }

void GUIContainer::Render(Renderer *renderer, TextRenderer *textRenderer) {
    RenderBackground(renderer, textRenderer);
    Shader shader = ResourceManager::LoadShader("Shaders/gui.vertexshader", "Shaders/gui.fragmentshader", "gui");
    for(auto it = mElements.begin(); it != mElements.end(); ++it)
        (*it)->Render(renderer, textRenderer, shader);
}

void GUIContainer::RenderBackground(Renderer *renderer, TextRenderer *textRenderer) {
    // by default there is no background, initialize in derived classes if necessary
}
