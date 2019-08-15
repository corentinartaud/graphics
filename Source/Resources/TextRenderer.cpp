//
//  TextRenderer.cpp
//  COMP371_Framework
//
//  Created by Corentin Artaud on 2019-08-09.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "TextRenderer.h"
#include "ResourceManager.h"

#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>

TextRenderer::TextRenderer() { }

TextRenderer::~TextRenderer() { }

void TextRenderer::Initialize(float width, float height) {
    TextShader = ResourceManager::GetShader("text");
    TextShader.SetMatrix4("projection", glm::ortho(0.0f, width, height, 0.0f), GL_TRUE);
    TextShader.SetInteger("text", 0);
    
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextRenderer::LoadFont(std::string font, int fontSize) {
    Characters.clear();
    
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    
    FT_Face face;
    if (FT_New_Face(ft, font.c_str(), 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    
    FT_Set_Pixel_Sizes(face, 0, fontSize);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    for (GLubyte i = 0; i < 128; i++) {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        // store characters
        Character character = {
            static_cast<int>(texture),
            glm::vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::vec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<int>(face->glyph->advance.x)
        };
        Characters.insert(std::pair<char, Character>(i, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void TextRenderer::RenderText(std::string text, float x, float y, float scale, glm::vec3 color) {
    TextShader.Use();
    TextShader.SetVector3f("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(mVAO);
    
    std::string::const_iterator it;
    for (it = text.begin(); it != text.end(); it++) {
        Character ch = Characters[*it];
        
        GLfloat xpos = x + ch.Bearing.x * scale;
        GLfloat ypos = y + (this->Characters['H'].Bearing.y - ch.Bearing.y) * scale;
        
        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;
        GLfloat vertices[] = {
            xpos,     ypos + h,   0.0, 1.0,
            xpos + w, ypos,       1.0, 0.0,
            xpos,     ypos,       0.0, 0.0,

            xpos,     ypos + h,   0.0, 1.0,
            xpos + w, ypos + h,   1.0, 1.0,
            xpos + w, ypos,       1.0, 0.0
        };
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // advance cursors for next glyph
        // Bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
        x += (ch.Advance >> 6) * scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
