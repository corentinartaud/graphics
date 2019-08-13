//
//  GUIContainer.h
//  COMP371_Project
//
//  Created by Corentin Artaud on 2019-08-09.
//  Copyright © 2019 Concordia. All rights reserved.
//

#ifndef GUIContainer_h
#define GUIContainer_h

#include "GUIElement.h"
#include "GUIButton.h"

#include <vector>
#if !defined(PLATFORM_OSX)	
#include <memory>
#endif
class Renderer;
class TextRenderer;

/*
 A container is used for rendering and containing GUI elements. A GUI container
 is required to render the GUI components; each GUI element requires a parent GUI
 container. The GUI Container stores any number of GUI elements and processes their
 actions respectively.
 */
class GUIContainer {
public:
    GUIContainer();
    
    // getters
    bool IsActive() { return mIsActive; };
    glm::vec2 GetPosition() { return mPosition; };
    glm::vec2 GetScale() { return mScale; };
    
    // setters
    void SetActive(bool active);
    void SetPosition(glm::vec2 position);
    void SetScale(glm::vec2 scale);
    
    // initializes the GUI container;
    virtual bool Initialize() = 0;
    
    virtual void Update(float dt) = 0;
    
    virtual void Render(Renderer *renderer, TextRenderer *textRenderer);
    
    virtual void RenderBackground(Renderer *renderer, TextRenderer *textRenderer);
    
    // sets the current GUI container as the active GUI container
    virtual void Activate();
    // deactivates the GUI container
    virtual void Deactivate();
    
    // occurs when the mouse has changed position
    void OnMouseMove(float x, float y);
    // occurs when the mouse button is clicked
    void OnMouseClick(bool leftButton);
    
    // is called whenever any of its GUIButton elements are pressed.
    virtual void ButtonPressed(std::shared_ptr<GUIButton> button);
    
protected:
    // add a GUI element to the conainer
    void AddElement(std::shared_ptr<GUIElement> element);
    // remove a GUI element from the container
    void RemoveElement(std::shared_ptr<GUIElement> element);
    
    bool mIsActive; // is the container currently active (being rendered, responding to user inputs)
    glm::vec2 mPosition; // sets the top-left position of the container
    glm::vec2 mScale; // defines the scale of the container
private:
    std::vector<std::shared_ptr<GUIElement>> mElements; // a list of GUI elements contained
};


#endif /* GUIContainer_h */
