#ifndef Animation_h
#define Animation_h

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <array>
#include "GameObject.h"
#include <list>

struct GameObjectWithTimestamp{
	GameObject object;
	float timestamp;
};
class Animation {
public:
		//Constr
	Animation();
		//Player Animation
	float floatModulo(float top, float bottom);
	void setPlayerAnimation(GameObject player);
		//Phantoms
	void Draw(Renderer& renderer, glm::mat4 viewMatrix);
	std::list<GameObjectWithTimestamp> phatomList;
	void addPhantom(GameObject object, float time);
};

#endif
