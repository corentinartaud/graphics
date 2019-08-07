//
//  GUIButton.cpp
//  COMP371_Framework
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "GUIButton.h"
#include "Renderer.h"

GUIButton::GUIButton() { }

void GUIButton::SetText(std::string text) {
    mText = text;
}

void GUIButton::SetHoverColor(glm::vec4 color) {
    mHoverColor = color;
}

void GUIButton::CalculateModel() {
    mModel = glm::mat4(1.0f);
    mModel *= glm::translate(glm::vec3(mPosition, 1.0f));
    mModel *= glm::scale(glm::vec3(mScale, 1.0f));
}

void GUIButton::Render() {
    if (mBackColor != glm::vec4(1.0f)) {
        
    }
}