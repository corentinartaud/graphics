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

/*
 A button to be used for GUIs. GUIButton contains text and a background color
 on a rectangle surrounding the text. A mouse hovering over the rectangle the text
 color amplifies.
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
    
    // calcualtes the world-space model matrix for rendering the button
    void CalculateModel();
    // renders the button's background contained and foreground text
    void Render();
    
private:
    std::string mText; // text to render at the center of the button
    glm::vec4 mHoverColor; // color of the th text when the mouse hovers the button
};

#endif /* GUIButton_h */
