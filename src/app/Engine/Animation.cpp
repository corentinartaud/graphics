//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2019 Concordia University. All rights reserved.
//

#include "Animation.h"
#include "Renderer.h"
#include "World.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <GL/glew.h>

#include "Box2D/Box2D.h"

using namespace glm;
using namespace std;

AnimationKey::AnimationKey() : Model()
{
}

AnimationKey::~AnimationKey()
{
}

void AnimationKey::Update(float dt)
{
	Model::Update(dt);
}

void AnimationKey::Draw()
{
	Model::Draw();
}

bool AnimationKey::ParseLine(const std::vector<ci_string> &token)
{
	if (token.empty())
	{
		return true;
	}
	else
	{
		return Model::ParseLine(token);
	}
}

Animation::Animation() 
	: mName(""), mCurrentTime(0.0f), mDuration(0.0f), mVBO(0), mVAO(0)
{
}

Animation::~Animation()
{
}

void Animation::CreateVertexBuffer()
{
    // This is just to display lines between the animation keys
    for (int i=0; i<(int)mKey.size(); ++i)
    {
        Vertex v;
        v.position = mKey[i].mPosition;
        mVertexBuffer.push_back(v);
    }
    
	// Create a vertex array
	glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

	// Upload Vertex Buffer to the GPU, keep a reference to it (mVertexBufferID)
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*mVertexBuffer.size(), &(mVertexBuffer[0]), GL_STATIC_DRAW);
    
    // Create a vertex array
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);
    
    // Upload Vertex Buffer to the GPU, keep a reference to it (mVertexBufferID)
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*mVertexBuffer.size(), &(mVertexBuffer[0]), GL_STATIC_DRAW);
    
    // 1st attribute buffer : vertex Positions
    glVertexAttribPointer(0,
                          3,                // size
                          GL_FLOAT,        // type
                          GL_FALSE,        // normalized?
                          sizeof(Vertex), // stride
                          (void*)0        // array buffer offset
                          );
    glEnableVertexAttribArray(0);

}

void Animation::Update(float dt)
{
	mCurrentTime += dt;

    while(mCurrentTime > mDuration)
    {
        mCurrentTime -= mDuration;
    }
}

void Animation::Draw()
{
	// @TODO 3 - Draw lines between animation key positions
	//
	// Steps:
	// - Draw the Vertex Buffer
	// - The Shader used to draw the Animation is PathLines, only requires to send the positions of the key positions
	// - You need to bind the vertex buffer created in CreateVertexBuffer() as the input of the vertex shader
	// - Also set the WorldTransform uniform variable in the vertex shader
	// - You Should use GL_LINE_LOOP as a primitive to draw lines (not triangles)
	// - You can look at CubeModel::Draw() for a good example!
    //
    // Notes:
    // The shader is bound in World.cpp and the ViewProjection Matrix uniform is set there...
	// The Model View Projection transforms are computed in the Vertex Shader
    
    // @TODO 3 - Completed Here
    // Followed example from CubeModel::Draw()
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform");
    // Given identity matrix for GL_FLOAT value for the path lines to not attach to the cube and sphere
    glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &mat4(1.0f)[0][0]);

    // Draw the lines! (mVertexBuffer holds the lines)
    glDrawArrays(GL_LINE_LOOP, 0, (int) mVertexBuffer.size());
}


void Animation::Load(ci_istringstream& iss)
{
	ci_string line;

	// Parse model line by line
	while(std::getline(iss, line))
	{
		// Splitting line into tokens
		ci_istringstream strstr(line);
		istream_iterator<ci_string, char, ci_char_traits> it(strstr);
		istream_iterator<ci_string, char, ci_char_traits> end;
		vector<ci_string> token(it, end);

		if (ParseLine(token) == false)
		{
			fprintf(stderr, "Error loading scene file... token:  %s!", token[0].c_str());
			getchar();
			exit(-1);
		}
	}
}


bool Animation::ParseLine(const std::vector<ci_string> &token)
{
    if (token.empty())
    {
        return true;
    }
	else if (token[0] == "name")
	{
		assert(token.size() > 2);
		assert(token[1] == "=");

		mName = token[2];
		return true;
	}
	else if (token[0] == "key")
	{
		assert(token.size() > 5);
        assert(token[1] == "=");
        assert(token[3] == "time");
        assert(token[4] == "=");

		ci_string name = token[2];
		AnimationKey *key = World::GetInstance()->FindAnimationKey(name);
        
		assert(key != nullptr);
		AddKey(key, (float) atof(token[5].c_str()));
		return true;
	}
	return false;
}

void Animation::AddKey(AnimationKey* key, float time)
{
    assert(time >= mDuration);
	mKey.push_back(*key);
    mKeyTime.push_back(time);
    mDuration = time;
}

ci_string Animation::GetName() const
{
	return mName;
}

glm::mat4 Animation::GetAnimationWorldMatrix() const
{
    // @TODO 4 - Find the 2 keys to interpolate the transformation (before and after current time)
    //           Interpolate the position, scaling and rotation separately
    //           Finally concatenate the interpolated transforms into a single
    //           world transform and return it.
    
    mat4 worldMatrix(1.0f);

    // @TODO4 - Completed Here
    // Loop through all the keys
    for (int i = 0; i < mKey.size(); i++) {
        // Check that the keytime is less than the current time of the object
        if (mCurrentTime < mKeyTime[i]) {
            // Calculate the time between two key frames, normalized
            float keyFrameTime = (mCurrentTime - mKeyTime[i - 1]) / (mKeyTime[i] - mKeyTime[i - 1]);
            
            // Interpolate between the 2 keys
            // Returns the linear blend of mKey[i-1] position and mKey[i] position using the floating-point value keyFrameTime
            vec3 position = mix(mKey[i - 1].GetPosition(), mKey[i].GetPosition(), keyFrameTime);
            // Returns the linear blend of mKey[i-1] scaling and mKey[i] scaling using the floating-point value keyFrameTime
            vec3 scaling = mix(mKey[i - 1].GetScaling(), mKey[i].GetScaling(), keyFrameTime);

            // Get the 2 rotations for both keys (i-1 and i) given the rotationAngle and rotationAxis
            quat q1 = angleAxis(radians(mKey[i - 1].GetRotationAngle()), mKey[i - 1].GetRotationAxis());
            quat q2 = angleAxis(radians(mKey[i].GetRotationAngle()), mKey[i].GetRotationAxis());
            
            // Spherical lerp (linear interpolation) of the 2 rotations calculated above
            quat rotation = slerp(q1, q2, keyFrameTime);

            // Calculate the world matrix for the animation
            // Translate : lerp ; toMat4 : spherical lerp (convert quaternion to mat4) ; scale : lerp
            worldMatrix = translate(mat4(1.0f), position) * toMat4(rotation) * scale(mat4(1.0f), scaling);
            
            // Return world matrix if key animation is found
            return worldMatrix;
        }
    }
    
    // Return identity matrix for world matrix if no animation is found
    return worldMatrix;
}
