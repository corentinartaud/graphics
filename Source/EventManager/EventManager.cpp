//
//  EventManager.cpp
//  COMP371_Framework
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "Game.h"
#include "Renderer.h"
#include "EventManager.h"

#include <stdio.h>
#include <iostream>
#include <fstream>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


// Time
double EventManager::sLastFrameTime = glfwGetTime();
float  EventManager::sFrameTime = 0.0f;

// Window
GLFWwindow* EventManager::spWindow = nullptr;

void EventManager::Initialize() {
    // Initialise GLFW
    if(!glfwInit()) {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit(-1);
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    
#if defined(PLATFORM_OSX)
    // OS X would use legacy opengl by default, and wouldn't be able to load shaders
    // This is the proper way to setup GLFW to use modern OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#else
    // Allow older laptops to run the framework, even though, our framework
    // is compatible with OpenGL 3.3 (which removed many deprecated features)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_DEPTH_BITS, 32);
#endif
    
    // Open a window and create its OpenGL context
    spWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Golden Sphere", nullptr, nullptr);
    if (spWindow == nullptr) {
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(spWindow);
    // Enables VSYNC on MacOSX
    glfwSwapInterval(1);
    
    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        exit(-1);
    }
    // Somehow, glewInit triggers a glInvalidEnum... Let's ignore it
    glGetError();
    
    // Ensure we can capture the escape key being pressed below
    glfwSetKeyCallback(spWindow, key_callback);

    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    // OpenGL configuration
    glViewport(0, 0, EventManager::GetScreenWidth(), EventManager::GetScreenHeight());
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Initial time
    sLastFrameTime = glfwGetTime();
}

void EventManager::Shutdown() {
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    spWindow = nullptr;
}

void EventManager::BeginFrame() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);
}

void EventManager::EndFrame() {
    // Swap buffers
    glfwSwapBuffers(spWindow);
}

void EventManager::Update() {
    // Update inputs / events
    glfwPollEvents();
    
    // Update frame time
    double currentTime = glfwGetTime();
    sFrameTime = static_cast<float>(currentTime - sLastFrameTime);
    sLastFrameTime = currentTime;
}

float EventManager::GetFrameTime() {
    return sFrameTime;
}

bool EventManager::ExitRequested() {
    return glfwGetKey(spWindow, GLFW_KEY_ESCAPE ) == GLFW_PRESS || glfwWindowShouldClose(spWindow);
}

void EventManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    // When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS)
            Game::GetInstance()->mKeys[key] = GL_TRUE;
        else if (action == GLFW_RELEASE)
             Game::GetInstance()->mKeys[key] = GL_FALSE;
    }
}
