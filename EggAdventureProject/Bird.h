/* -----------------------------------------------------------------*
*																	*
*	 CLASS NAME: Bird												*
*	 DESCRIPTION: Create brid object to render on window			*
*	 DEFINATION: Source Files/Bird.cpp								*
*	 BASE CLASS: Sprite.h											*
*																	*
*	 author: rubel hassan											*
*    rubelhassan@outlook.com										*
*																	*
*-------------------------------------------------------------------*/

#ifndef BIRD_H_INC
#define BIRD_H_INC

#include <GL/glew.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include "VertexStucture.h"
#include "Vector2.h"

#include "Sprite.h"

class Bird: public Sprite{


public:

	Bird();
	Bird(GLfloat w, GLfloat h);
	~Bird();
	void update();

};



#endif // <-- BIRD_H_INC