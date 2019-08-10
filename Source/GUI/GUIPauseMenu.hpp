//
//  GUIPauseMenu.hpp
//  COMP371_Framework
//
//  Created by Steven Anthony on 2019-08-10.
//  Copyright © 2019 Concordia. All rights reserved.
//

#ifndef GUIPauseMenu_hpp
#define GUIPauseMenu_hpp
#if !defined(PLATFORM_OSX)
#include <memory>

#endif

#include <stdio.h>
#include "GUIContainer.h"

class TextureLoader;
class TextRenderer;
class GUIButton;

class GUIPauseMenu : public GUIContainer {
public:
    int currentSelection;
    GUIPauseMenu();
    
    // initializes the in-game menu and its all its relevant controls
    bool Initialize();
    // updates the game menu plus all its controls
    void Update(float dt);
    // render the background texture and color
    void RenderBackground(Renderer *renderer, TextRenderer *text);
    
    // activates the main menu
    void Activate();
    // deactives the main menu
    void Deactivate();
    
    // occurs when a button is pressed
    void ButtonPressed(std::shared_ptr<GUIButton> pButton);
};

#endif /* GUIPauseMenu_hpp */
