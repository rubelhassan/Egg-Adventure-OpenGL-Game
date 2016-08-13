/* -----------------------------------------------------------------*
*																	*
*	 FileName: Egg.cpp											    *
*	 Description: Create Egg object to render on window				*
*	 Declaration: Header Files/Bird.h								*
*																	*
*	 author: rubel hassan											*
*	 rubelhassan@outlook.com										*
*																	*
*-------------------------------------------------------------------*/

#include "Egg.h"


int Egg::count = 0;

Egg::Egg(){

	wX = 0.0f, wY = 0.0f;

	vertSprite[0] = { { wX, wY, 0.0f }, { 0.0f, 0.0f, 0.0f } };
	vertSprite[1] = { { wX + 25.0f, wY, 0.0f }, { 1.0f, 0.0f, 0.0f } };
	vertSprite[2] = { { wX + 25.0f, wY + 25.0f, 0.0f }, { 1.0f, 1.0f, 0.0f } };
	vertSprite[3] = { { wX, wY + 25.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } };

	m_Position.x = 50.0f;
	m_Position.y = 400.f;
	count++;
}

Egg::Egg(GLfloat x, GLfloat y){

	wX = 0.0f, wY = 0.0f;

	vertSprite[0] = { { wX, wY, 0.0f }, { 0.0f, 0.0f, 0.0f } };
	vertSprite[1] = { { wX + 25.0f, wY, 0.0f }, { 1.0f, 0.0f, 0.0f } };
	vertSprite[2] = { { wX + 25.0f, wY + 25.0f, 0.0f }, { 1.0f, 1.0f, 0.0f } };
	vertSprite[3] = { { wX, wY + 25.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } };

	m_Position.x = x;
	m_Position.y = y;
	count++;
}


Egg::~Egg(){
	count--;
}


void Egg::update(int key){
	
	m_Position = addVector2(m_Position, m_Velocity);
	// std::cout << "Egg.cpp";
	//std::cout << m_Position.x << " " << m_Position.y << std::endl;

}