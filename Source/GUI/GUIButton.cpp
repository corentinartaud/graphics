//
//  GUIButton.cpp
//  COMP371_Framework
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "GUIButton.h"
#include "Renderer.h"
#include "TextRenderer.h"
#include "EventManager.h"
#include "ResourceManager.h"

#include <iostream>

GUIButton::GUIButton() { }

void GUIButton::SetText(std::string text) {
    mText = text;
}

void GUIButton::SetHoverColor(glm::vec4 color) {
    mHoverColor = color;
}

void GUIButton::Render(Renderer *renderer, TextRenderer *text, Shader shader) {
    text->RenderText(mText, mPosition.x, mPosition.y, 1.0f, mMouseEntered ? mHoverColor : mForeColor);
}
