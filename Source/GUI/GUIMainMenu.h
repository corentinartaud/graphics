//
//  GUIGameMenu.h
//  COMP371_Project
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#ifndef GUIGameMenu_h
#define GUIGameMenu_h

class TextureLoader;
class GUIButton;

class GUIMainMenu {
public:
    int currentSelection;
    GUIMainMenu();
    
    // initializes the in-game menu and its all its relevant controls
    bool Initiailize();
    // updates the game menu plus all its controls
    void Update(float dt);
    // render the background texture and color
    void RenderBackground();
    
    void changeMenuState();
    void selectionUp();
    void selectionDown();
    void select();
    
private:
    // texture used for rendering the background
    TextureLoader* mBackgroundTexture; 
    
};

#endif /* GUIGameMenu_h */
