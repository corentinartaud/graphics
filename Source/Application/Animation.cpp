#include "Animation.h"
#include <string>
#include <iostream>
#include "EventManager.h"
#include "ResourceManager.h"

using namespace std;

Animation::Animation() {

}
float Animation::floatModulo(float top, float bottom){
	uint8_t division = top / bottom;
	return top - (bottom * (float)division);
}

void Animation::setPlayerAnimation(GameObject player) {
	addPhantom(player);
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

void Animation::DrawPhantom(Renderer& renderer, glm::mat4 viewMatrix){
#define MODE 0
#if MODE == 1
		//Mode 1: Restrict list size
#define NUMBER_OF_PHANTOMS_TO_KEEP 5
	int size = phantomList.size();
	if (size > NUMBER_OF_PHANTOMS_TO_KEEP) {
		for (int i=0;i<size- NUMBER_OF_PHANTOMS_TO_KEEP;i++)
			phantomList.pop_front();
	}
#else
		//Mode 2: timeout
#define TIMEOUT_TIME 0.3f	//in seconds

	std::list<GameObjectWithTimestamp>::iterator it = phantomList.begin();
	while (it != phantomList.end()){
		if (glfwGetTime() - phantomList.front().timestamp> TIMEOUT_TIME){
			phantomList.pop_front();
		}
		else{
			break;
		}
		if (phantomList.empty()) return; //if list is empty now then leave the loop or the next iteration will throw a null pointer exception
	}
#endif

#ifndef TIMEOUT_TIME
#define TIMEOUT_TIME 0.5f	//how texture color fades out
#endif	
		//Draw phantoms and interpolate color/opacity
	for (GameObjectWithTimestamp tile : phantomList){
		float mixVariable = (glfwGetTime() - tile.timestamp) / TIMEOUT_TIME*2;
		mixVariable = min(mixVariable, 1.0f);  //clamp mix
		mixVariable = max(mixVariable, 0.0f);  //clamp mix
		tile.object.mColor = (glm::mix(tile.object.mColor * (glm::vec4(1.0f, 1.0f, 1.0f, 0.6f)), glm::vec4(0.0f, 0.0f, 0.0f, 0.0f),mixVariable));
		tile.object.Draw(renderer, viewMatrix);
	}
}

void Animation::addPhantom(GameObject object){
	GameObjectWithTimestamp temp = { object, glfwGetTime() };
	this->phantomList.push_back(temp);
}

void Animation::DrawSmoke(Renderer& renderer, glm::mat4 viewMatrix) {

#define SMOKE_FADE_TIME 0.8f
		//check if smoke should be deleted
	std::list<GameObjectWithTimestamp>::iterator it = smokeList.begin();
	while (it != smokeList.end()){	//go through list
		if (glfwGetTime() - smokeList.front().timestamp > SMOKE_FADE_TIME) {
			smokeList.pop_front();	//delete the object if needed
		}
		else {
			break;
		}
		if (smokeList.empty()) return;	//if list is empty now then leave the loop or the next iteration will throw a null pointer exception
	}
	//Draw smoke and interpolate color/opacity
	for (GameObjectWithTimestamp tile : smokeList) {
		float mixVariable = (glfwGetTime() - tile.timestamp) / SMOKE_FADE_TIME;
		mixVariable = min(mixVariable, 1.0f);	//clamp mix
		mixVariable = max(mixVariable, 0.0f);   //clamp mix
		tile.object.mColor = (glm::mix(tile.object.mColor*(glm::vec4(1.0f,1.0f,1.0f,0.8f)), glm::vec4(1.0f, 1.0f, 1.0f, 0.0f), mixVariable));	//interpolate color
		tile.object.Draw(renderer, viewMatrix);
	}
}

void Animation::addSmoke(GameObject player, smokeTypes type) {
	GameObject tempObj;
	ResourceManager::LoadTexture("../Assets/Textures/smoke.png", GL_TRUE, "jumpSmoke");	//load jumpSmoke texture
	tempObj.mTexture = ResourceManager::GetTexture("jumpSmoke");	//set texture
	tempObj.mPosition = player.mPosition;	//place at position of input object
	tempObj.mSize = glm::vec2(80.0f, 20.0f);	//set size

	GameObjectWithTimestamp temp = { tempObj, glfwGetTime()};	//make object with timestamp
	smokeList.push_back(temp);	//add to list

	/*
	switch (type) {
	case Run:
		break;
	case Jump:

		break;
	default:
		return;
	}
	*/
}
