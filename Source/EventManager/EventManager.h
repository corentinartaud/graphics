//
//  EventManager.h
//  COMP371_Project
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#ifndef EventManager_h
#define EventManager_h

#include <GLFW/glfw3.h>

struct GLFWwindow;

class EventManager {
public:
    static void Initialize();
    static void Shutdown();
    
    static void BeginFrame();
    static void EndFrame();
    
    static void Update();
    
    static float GetFrameTime();
    static void SetWindowShouldClose();
    static bool ExitRequested();
    
    static GLuint GetScreenWidth() { return SCREEN_WIDTH; };
    static GLuint GetScreenHeight() { return SCREEN_HEIGHT; };
    
    static GLFWwindow* GetWindow() { return spWindow; };
    
private:
    // GLFW function declerations
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    
    // Time
    static double sLastFrameTime;
    static float sFrameTime;
    
    // Window
    static GLFWwindow* spWindow;
    
    // The Width of the screen
    static const GLuint SCREEN_WIDTH = 1024;
    // The height of the screen
    static const GLuint SCREEN_HEIGHT = 768;
    
    // GLFW function declerations
    static void mouse_move_callback(GLFWwindow* window, double x, double y);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};

#endif /* EventManager_h */
