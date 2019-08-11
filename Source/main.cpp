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
    
    Game goldenSphere;
    
    goldenSphere.GameLoop();
    
    EventManager::Shutdown();
    
    return 0;
}
