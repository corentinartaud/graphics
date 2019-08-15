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

// All characters of the fonts are loaded here
struct Character {
    int TextureID;
    glm::vec2 Size;
    // Offset from baseline to left/top of glyph
    glm::vec2 Bearing;
    // Horizontal offset to advance to next glyph
    int Advance;
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
    // Initializer
    void Initialize(float width, float height);
    // Pre-compiles a list of characters from the given font
    void LoadFont(std::string font, int fontSize);
    // Renders a string of text using the precompiled list of characters
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));
private:
    // Shader used for text rendering
    Shader TextShader;
    // Holds a list of pre-compiled Characters
    std::map<char, Character> Characters;
    
    unsigned int mVAO;
    unsigned int mVBO;
};

#endif /* TextRenderer_h */
