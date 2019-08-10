//
//  main.cpp
//  COMP371_Framework
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "Game.h"
#include "EventManager.h"
#include "GUIMainMenu.h"
#include <string>
#include <iostream>

using namespace std;


int main(int argv, char* argc[]) {
    EventManager::Initialize();
    
    GUIMainMenu mainMenu;
    if(mainMenu.Initialize()){
        
        std::cout << "works" << std::endl;
    }
    
    // following 3 lines can be put in the game menu cpp. we can manage it there, same with the do-while. 
    Game goldenSphere(EventManager::GetScreenWidth(), EventManager::GetScreenHeight());
    goldenSphere.Initialize();
    goldenSphere.mState = GAME_ACTIVE;
    
    do {
        EventManager::Update();
        
        float dt = EventManager::GetFrameTime();
        goldenSphere.ProcessInput(dt);
        
        goldenSphere.Update(dt);
        
        goldenSphere.Render();
        
    } while(!EventManager::ExitRequested());

    EventManager::Shutdown();
    
    return 0;
}
