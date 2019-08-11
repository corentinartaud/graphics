//
//  GUILost.h
//  COMP371_Project
//
//  Created by Corentin Artaud on 2019-08-11.
//  Copyright © 2019 Concordia. All rights reserved.
//

#ifndef GUILost_h
#define GUILost_h

#include <memory>

#include "GUIContainer.h"

class TextRenderer;
class GUIButton;

class GUILost : public GUIContainer {
public:
    GUILost();
    // initializes the lost popup and its all its relevant controls
    bool Initialize();
    // updates the lost pop plus all its controls
    void Update(float dt);
    // render the background texture and color
    void RenderBackground(Renderer *renderer, TextRenderer *text);
    // activates the lost popup
    void Activate();
    // deactives the lost popup
    void Deactivate();
    // occurs when a button is pressed
    void ButtonPressed(std::shared_ptr<GUIButton> pButton);
};

#endif /* GUILost_h */
