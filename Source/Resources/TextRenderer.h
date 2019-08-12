//
//  TextRenderer.h
//  COMP371_Project
//
//  Created by Corentin Artaud on 2019-08-09.
//  Copyright © 2019 Concordia. All rights reserved.
//

#ifndef TextRenderer_h
#define TextRenderer_h

#include <map>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "TextureLoader.h"
#include "Shader.h"


/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    int TextureID;   // ID handle of the glyph texture
    glm::vec2 Size;    // Size of glyph
    glm::vec2 Bearing; // Offset from baseline to left/top of glyph
    int Advance;     // Horizontal offset to advance to next glyph
};


/*
 A renderer class for rendering text displayed by a font loaded using the
 FreeType library. A single font is loaded, processed into a list of Character
 items for later rendering.
*/
class TextRenderer {
public:
    // Constructor // Destructor
    TextRenderer();
    ~TextRenderer();
    // Holds a list of pre-compiled Characters
    std::map<char, Character> Characters;
    // Shader used for text rendering
    Shader TextShader;
    // Initializer
    void Initialize(float width, float height);
    // Pre-compiles a list of characters from the given font
    void LoadFont(std::string font, int fontSize);
    // Renders a string of text using the precompiled list of characters
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));
private:
    // Render state
    unsigned int mVAO;
    unsigned int mVBO;
};

#endif /* TextRenderer_h */
