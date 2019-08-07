//
//  main.cpp
//  COMP371_Framework
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "Game.h"
#include "EventManager.h"

int main(int argv, char* argc[]) {
    EventManager::Initialize();
    
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
