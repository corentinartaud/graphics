//
//  GUIGameMenu.h
//  COMP371_Project
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#ifndef GUIGameMenu_h
#define GUIGameMenu_h
#if !defined(PLATFORM_OSX)	
	#include <memory>
#endif

#include "GUIContainer.h"

class TextureLoader;
class TextRenderer;
class GUIButton;

class GUIMainMenu : public GUIContainer {
public:
    int currentSelection;
    GUIMainMenu();
    
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
    
    void changeMenuState();
    void selectionUp();
    void selectionDown();
    void select();
};

#endif /* GUIGameMenu_h */
