/* -----------------------------------------------------------------*
*																	*
*	 FileName: Bird.cpp											    *
*	 Description: Create Bird object to render on window			*
*	 Declaration: Header Files/Bird.h								*
*																	*
*	 author: rubel hassan   										*
*	 rubelhassan@outlook.com										*
*																	*
*-------------------------------------------------------------------*/

#include "Bird.h"
#include "SOIL/SOIL.h"
#include <ctime>
#include <cstdlib>


/*void Object::setPosition(Vector2 position){
	m_Position = position;
}

Vector2 Object::getPosition(){
	return m_Position;
}*/


Bird::Bird(){

	//wX = 0.0f, wY = 350.f;
	wX = 0.0f, wY = 0.0f;

	vertSprite[0] = { { wX, wY, 0.0f }, { 0.0f, 0.0f, 0.0f } };
	vertSprite[1] = { { wX + 100.0f, wY, 0.0f }, { 1.0f, 0.0f, 0.0f } };
	vertSprite[2] = { { wX + 100.0f, wY + 100.0f, 0.0f }, { 1.0f, 1.0f, 0.0f } };
	vertSprite[3] = { { wX, wY + 100.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } };


	/*vertSprite[0] = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
	vertSprite[1] = { { 40.0f, 27.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
	vertSprite[2] = { { 36.0f, 72.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
	vertSprite[3] = { { 45.0f, 60.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
	vertSprite[4] = { { 43.0f, 77.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
	vertSprite[5] = { { 60.0f, 44.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
	vertSprite[6] = { { 89.0f, 69.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
	vertSprite[7] = { { 89.0f, 69.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
	vertSprite[8] = { { 86.0f, 64.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
	vertSprite[9] = { { 67.0f, 27.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };*/
	
	//srand(static_cast <unsigned> (time(0)));
	float yRand = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/115.0f));
	yRand += 350.0f;

	//m_TextureBufferID = 0;
	m_Position.x = 0.0f;
	m_Position.y = (GLfloat)yRand;
}

Bird::Bird(GLfloat w, GLfloat h){

	//wX = 0.0f, wY = 350.f;
	wX = 0.0f, wY = 0.0f;

	vertSprite[0] = { { wX, wY, 0.0f }, { 0.0f, 0.0f, 0.0f } };
	vertSprite[1] = { { wX + w, wY, 0.0f }, { 1.0f, 0.0f, 0.0f } };
	vertSprite[2] = { { wX + w, wY + h, 0.0f }, { 1.0f, 1.0f, 0.0f } };
	vertSprite[3] = { { wX, wY + h, 0.0f }, { 0.0f, 1.0f, 0.0f } };

	// create random y position to translate between 350.0f to 460.0f
	float yRand = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 115.0f));
	yRand += 350.0f;


	//m_TextureBufferID = 0;
	m_Position.x = 0.0f;
	m_Position.y = (GLfloat)yRand;
}

Bird::~Bird(){
	
}



void Bird::update(){
	m_Velocity.y = m_Velocity.y*(-1.0f);
	m_Position = addVector2(m_Position, m_Velocity);
	
	if (m_Position.x > 960)
		m_Position.x = 0.0f;
}