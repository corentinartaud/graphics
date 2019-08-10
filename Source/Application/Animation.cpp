#include "Animation.h"
#include <string>
#include <iostream>
#include "EventManager.h"
#include "ResourceManager.h"

using namespace std;

Animation::Animation() {

}
float Animation::floatModulo(float top, float bottom)
{
	uint8_t division = top / bottom;
	return top - (bottom * (float)division);
}

void Animation::setPlayerAnimation(GameObject player) {
	addPhantom(player, glfwGetTime());
	const std::string standRight[6] = {
		"Textures/Player/stand/s1.png",
		"Textures/Player/stand/s2.png",
		"Textures/Player/stand/s3.png",
		"Textures/Player/stand/s4.png",
		"Textures/Player/stand/s5.png",
		"Textures/Player/stand/s6.png"
	};
	const std::string walkRight[6] = {
		"Textures/Player/walk/w1.png",
		"Textures/Player/walk/w2.png",
		"Textures/Player/walk/w3.png",
		"Textures/Player/walk/w4.png",
		"Textures/Player/walk/w5.png",
		"Textures/Player/walk/w6.png"
	};
	const std::string standLeft[6] = {
		"Textures/Player/stand/Mirrored/s1.png",
		"Textures/Player/stand/Mirrored/s2.png",
		"Textures/Player/stand/Mirrored/s3.png",
		"Textures/Player/stand/Mirrored/s4.png",
		"Textures/Player/stand/Mirrored/s5.png",
		"Textures/Player/stand/Mirrored/s6.png"
	};
	const std::string walkLeft[6] = {
		"Textures/Player/walk/Mirrored/w1.png",
		"Textures/Player/walk/Mirrored/w2.png",
		"Textures/Player/walk/Mirrored/w3.png",
		"Textures/Player/walk/Mirrored/w4.png",
		"Textures/Player/walk/Mirrored/w5.png",
		"Textures/Player/walk/Mirrored/w6.png"
	};
#define still 0
#define forward 1
#define backward 2
	float positionX = player.mPosition.x;
	static uint8_t pastDirection = 0;	//stores past direction of movement, everytime the movement direction changes, restart the animation timer
	static float pastPositionX = 0;	//stores past position, knowign past position and new position give direction, basically velocity beign positive or negative
	static bool mirroredStatus = false;	//stores whether player texture should be mirrored
	uint8_t direction = 0;	//direction of movement
		//checking current movement direction
	if (positionX > pastPositionX) {
		direction = forward;
		mirroredStatus = false;
	}
	else if (positionX < pastPositionX) {
		direction = backward;
		mirroredStatus = true;
	}
	else {
		direction = still;
	}
	pastPositionX = positionX;
	//calculating time since animation began
	static float timeElapsed = 0;
	if (pastDirection != direction) {
		timeElapsed = 0;
	}
	else {
		timeElapsed += EventManager::GetFrameTime();
	}
	pastDirection = direction;
	//calculate which animation frame to be in
#define totalCycleTime 0.5f //in seconds
	float cycleTime = floatModulo(timeElapsed, totalCycleTime);
	int frameNumber = cycleTime / (totalCycleTime / 6);	//calculate frame number from 0-5
	std::cout << timeElapsed << endl;
	frameNumber = min(frameNumber, 5);	//clamp upper
	frameNumber = max(frameNumber, 0);	//clamp lower
	std::string framePath;
	if (mirroredStatus == true) {
		if (direction == 0) {
			framePath = standLeft[frameNumber];
		}
		else framePath = walkLeft[frameNumber];
	}
	else {
		if (direction == 0) {
			framePath = standRight[frameNumber];
		}
		else framePath = walkRight[frameNumber];
	}
#if defined(PLATFORM_OSX)	
	ResourceManager::LoadTexture(Animation::getAnimationTexture(player->mPosition.x).c_str(), GL_TRUE, "player");	//update texture
	return framePath;
#else 
	ResourceManager::LoadTexture(("../Assets/" + framePath).c_str(), GL_TRUE, "player");	//update texture
	//return "../Assets/" + framePath;
#endif
}

void Animation::Draw(Renderer& renderer, glm::mat4 viewMatrix)
{
#define MODE 1
#if MODE == 1
		//Mode 1: Restrict list size
#define NUMBER_OF_PHANTOMS_TO_KEEP 5
	int size = phatomList.size();
	if (size > NUMBER_OF_PHANTOMS_TO_KEEP) {
		for (int i=0;i<size- NUMBER_OF_PHANTOMS_TO_KEEP;i++)
			phatomList.pop_front();
	}
#else
		//Mode 2: timeout
#define TIMEOUT_TIME 0.3f	//in seconds

	std::list<GameObjectWithTimestamp>::iterator it = phatomList.begin();
	while (it != phatomList.end())
	{
		if (glfwGetTime() - phatomList.front().timestamp> TIMEOUT_TIME){
			phatomList.pop_front();
		}
		else{
			break;
		}
	}
#endif

#ifndef TIMEOUT_TIME
#define TIMEOUT_TIME 0.3f	//how texture color fades out
#endif 
	for (GameObjectWithTimestamp tile : phatomList)
	{
		float mixVariable = (glfwGetTime() - tile.timestamp) / TIMEOUT_TIME*2;
		mixVariable = min(mixVariable, 1.0f);
		mixVariable = max(mixVariable, 0.0f);
		tile.object.mColor = (glm::mix(tile.object.mColor, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f),mixVariable));
		tile.object.Draw(renderer, viewMatrix);
	}
}

void Animation::addPhantom(GameObject object, float time)
{
	GameObjectWithTimestamp temp = { object, time };
	this->phatomList.push_back(temp);
}

