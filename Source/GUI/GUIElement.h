//
//  GUIElement.h
//  COMP371_Project
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#ifndef GUIElement_h
#define GUIElement_h

#include <glm/glm.hpp>

#include <string>

class Renderer;
class TextRenderer;
class Shader;

/*
 Provides the base of any GUI Element. Defines the relevant states shared by
 each GUI element and defines the template functions. GUI element should
 maybe be contained within a container (TBD)
*/

class GUIElement {
public:
    GUIElement();
    // getters
    std::string GetName() { return mName; };
    glm::vec2 GetPosition() { return mPosition; };
    glm::vec2 GetScale() { return mScale; };
    glm::vec4 GetForeColor() { return mForeColor; };
    glm::vec4 GetBackColor() { return mBackColor; };
    
    // setters
    void SetName(std::string name);
    void SetPosition(glm::vec2 position);
    void SetScale(glm::vec2 scale);
    void SetForeColor(glm::vec4 foreColor);
    void SetBackColor(glm::vec4 backColor);
    
    // re-calculates model matrix
    virtual void CalculateModel() = 0;
    
    // renders the GUIElement, should be overriden in subclasses (TO BE UPDATED)
    virtual void Render(Renderer *renderer, TextRenderer *text, Shader shader) = 0;
    
    // @TODO Should take care of fired events when element is pressed
    // TBD
    
protected:
    std::string mName; // name of the GUI element to identify from other controls
    glm::vec2 mPosition; // position of the GUI element
    glm::vec2 mScale; // the scale of the GUI element
    glm::vec4 mForeColor; // the GUI elements foreground/text color
    glm::vec4 mBackColor; // the GUI elements background color
    glm::mat4 mModel; // the world-space model matrix for rendering the GUI element
};

#endif /* GUIElement_h */
