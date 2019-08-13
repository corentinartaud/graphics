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

#include <iostream>

GUIContainer::GUIContainer() { }

void GUIContainer::AddElement(std::shared_ptr<GUIElement> element) {
    // check if it doesn't already exist
    for (auto it = mElements.begin(); it != mElements.end(); ++it)
        if((*it) == element)
            return;
    mElements.push_back(element);
}

void GUIContainer::RemoveElement(std::shared_ptr<GUIElement> element) {
#if defined(PLATFORM_OSX)	
	mElements.erase(std::remove(mElements.begin(), mElements.end(), element), mElements.end());
#else
	for (int i = 0; i < mElements.size() - 1; i++){
		if (mElements[i] == element){
			mElements.erase(mElements.begin() + i, mElements.end());
			break;
		}
	}
#endif
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
    if (mIsActive) {
        RenderBackground(renderer, textRenderer);
        for(auto it = mElements.begin(); it != mElements.end(); ++it)
            (*it)->Render(renderer, textRenderer, ResourceManager::GetShader("gui"));
    }
}

void GUIContainer::RenderBackground(Renderer *renderer, TextRenderer *textRenderer) {
    // no background here, initialize in derived classes
}

void GUIContainer::OnMouseMove(float x, float y) {
    if (mIsActive) {
        for (auto it = mElements.begin(); it != mElements.end(); ++it) {
            (*it)->SetMouseEntered(false);
            if ((*it)->IsMouseInside(x, y))
                (*it)->SetMouseEntered(true);
        }
    }
}

void GUIContainer::OnMouseClick(bool leftButton) {
    if (mIsActive) {
        std::shared_ptr<GUIButton> button;
        for (auto it = mElements.begin(); it != mElements.end(); ++it) {
            if((*it)->GetMouseEntered())
                button = std::dynamic_pointer_cast<GUIButton>((*it));
        }
        if (button)
            ButtonPressed(button);
    }
}

void GUIContainer::ButtonPressed(std::shared_ptr<GUIButton> button) { }
