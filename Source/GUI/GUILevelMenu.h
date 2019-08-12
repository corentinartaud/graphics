//
//  GUILevelMenu.h
//  COMP371_Project
//
//  Created by Corentin Artaud on 2019-08-11.
//  Copyright © 2019 Concordia. All rights reserved.
//

#ifndef GUILevelMenu_h
#define GUILevelMenu_h

#if !defined(PLATFORM_OSX)
#include <memory>
#endif

#include <stdio.h>
#include "GUIContainer.h"

class TextureLoader;
class TextRenderer;
class GUIButton;

class GUILevelMenu : public GUIContainer {
public:
    GUILevelMenu();
    
    // initializes the in-game menu and its all its relevant controls
    bool Initialize() override;
    // updates the game menu plus all its controls
    void Update(float dt) override;
    // render the background texture and color
    void RenderBackground(Renderer *renderer, TextRenderer *text) override;
    
    // activates the main menu
    void Activate() override;
    // deactives the main menu
    void Deactivate() override;
    
    // occurs when a button is pressed
    void ButtonPressed(std::shared_ptr<GUIButton> pButton) override;
};

#endif /* GUILevelMenu_h */
