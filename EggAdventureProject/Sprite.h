/* -----------------------------------------------------------------*
*																	*
*	 CLASS NAME: Sprite 										    *
*	 DESCRIPTION: Create and render objects on window				*
*	 DEFINATION: Source Files/Sprite.cpp							*
*	 BASE CLASS: n/a												*
*																	*
*	 author: rubel hassan											*
*    rubelhassan@outlook.com										*
*																	*
*-------------------------------------------------------------------*/

#ifndef SPRITE_H_INC
#define SPRITE_H_INC

#include <GL/glew.h>
#include <iostream>
#include <GLFW/glfw3.h>

#include "VertexStucture.h"
#include "Vector2.h"


class Sprite{

private:
	GLuint m_TextureBufferID;
	int imageWidth, imageHeight;
	GLuint m_VertexBufferID;


protected:
	Vector2 m_Position;
	Vector2 m_Velocity;
	VertexData vertSprite[4];
	GLfloat wX, wY;

public:

	void setPosition(Vector2 position);
	Vector2 getPosition();
	Sprite(GLuint textureID);
	Sprite();
	~Sprite();
	void render();
	virtual void update(int key);
	void loadAndBufferImage(const char *filename);
	void init(const char* filename);

	void setVelocity(Vector2 newVector);
	Vector2 getVelocity();
	virtual void update();
};

#endif // <-- SPRITE_H_INC