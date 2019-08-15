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
 each GUI element and defines the template functions. All GUIElements are then
 contained within a Container.
*/

class GUIElement {
public:
    GUIElement();
    // getters
    std::string GetName() { return mName; };
    glm::vec2 GetPosition() { return mPosition; };
    glm::vec2 GetScale() { return mScale; };
    glm::vec3 GetForeColor() { return mForeColor; };
    bool GetMouseEntered() { return mMouseEntered; };
    
    // setters
    void SetName(std::string name);
    void SetPosition(glm::vec2 position);
    void SetScale(glm::vec2 scale);
    void SetForeColor(glm::vec3 foreColor);
    void SetMouseEntered(bool entered);
    
    // check if mouse is around button
    bool IsMouseInside(float x, float y);
    
    // renders the GUIElement, should be overriden in subclasses
    virtual void Render(Renderer *renderer, TextRenderer *text, Shader shader) = 0;
    
protected:
    std::string mName;
    glm::vec2 mPosition;
    glm::vec2 mScale;
    glm::vec3 mForeColor;
    bool mMouseEntered;
};

#endif /* GUIElement_h */
