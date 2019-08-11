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
	double timestamp;
};
struct AnimationObject {
	GameObject object;
	double timestamp;
	int id;
};
enum smokeTypes {
	Run,
	Jump
};
class Animation {
public:
		//Constr
	Animation();

		//Player Animation
	float floatModulo(float top, float bottom);
	void setPlayerAnimation(GameObject player);

		//Phantoms
	void DrawPhantom(Renderer& renderer, glm::mat4 viewMatrix);
	std::list<GameObjectWithTimestamp> phantomList;
	void addPhantom(GameObject object);

		//Smoke List
	std::list<GameObjectWithTimestamp> smokeList;
	void DrawSmoke(Renderer& renderer, glm::mat4 viewMatrix);
	void addSmoke(GameObject player, smokeTypes type);
};

#endif
