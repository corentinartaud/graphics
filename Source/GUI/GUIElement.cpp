//
//  GUIElement.cpp
//  COMP371_Framework
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "GUIElement.h"

GUIElement::GUIElement() : mForeColor(1.0f), mBackColor(1.0f) { }

void GUIElement::SetName(std::string name) {
    mName = name;
}

void GUIElement::SetPosition(glm::vec2 position) {
    mPosition = position;
    CalculateModel();
}

void GUIElement::SetScale(glm::vec2 scale) {
    mScale = scale;
    CalculateModel();
}

void GUIElement::SetForeColor(glm::vec4 foreColor) {
    mForeColor = foreColor;
}

void GUIElement::SetBackColor(glm::vec4 backColor) {
    mBackColor = backColor;
}

