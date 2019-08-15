//
//  GUIButton.h
//  COMP371_Project
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#ifndef GUIButton_h
#define GUIButton_h

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "GUIElement.h"

#include <string>

class Renderer;
class TextRenderer;
class Shader;

/*
 A button to be used for GUIs. GUIButton contains text and a background color
 on a rectangle surrounding the text. A mouse hovering over the rectangle the text
 color changes.
*/
class GUIButton : public GUIElement {
public:
    GUIButton();
    
    // getters
    std::string GetText() { return mText; };
    glm::vec4 GetHoverColor() { return mHoverColor; };
    
    // setters
    void SetText(std::string text);
    void SetHoverColor(glm::vec4 color);
    
    // renders the text of the button
    void Render(Renderer *renderer, TextRenderer *textRenderer, Shader Shader);
    
private:
    // text to render for the button
    std::string mText;
    // color of the text when the mouse hovers the button
    glm::vec4 mHoverColor;
};

#endif /* GUIButton_h */
