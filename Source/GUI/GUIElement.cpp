//
//  GUIElement.cpp
//  COMP371_Framework
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "GUIElement.h"
#include <iostream>

#include <iostream>

GUIElement::GUIElement() : mForeColor(1.0f) { }

void GUIElement::SetName(std::string name) {
    mName = name;
}

void GUIElement::SetPosition(glm::vec2 position) {
    mPosition = position;
}

void GUIElement::SetScale(glm::vec2 scale) {
    mScale = scale;
}

void GUIElement::SetForeColor(glm::vec3 foreColor) {
    mForeColor = foreColor;
}

void GUIElement::SetMouseEntered(bool entered) {
    mMouseEntered = entered;
}

bool GUIElement::IsMouseInside(float x, float y) {
    bool inside = true;
    glm::vec2 AABBCenter = mPosition + mScale * 0.4f;
    glm::vec2 AABBHalfWidths = glm::vec2(mScale.x * 0.4f, mScale.y);
    // - check if target is outside AABB and if so change center accordingly
    if (x > AABBCenter.x + AABBHalfWidths.x)      // target at right side of box
        inside = false;
    else if (x < AABBCenter.x - AABBHalfWidths.x) // target at left side of box
        inside = false;
    if (y > AABBCenter.y + AABBHalfWidths.y)      // target at bottom side of box
        inside = false;
    else if (y < AABBCenter.y - AABBHalfWidths.y) // target at top side of box
        inside = false;
    return inside;
}
