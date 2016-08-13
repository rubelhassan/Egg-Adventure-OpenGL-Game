/* -----------------------------------------------------------------*
*																	*
*	 FileName: Player.cpp											*
*	 Description: Create player to render on window					*
*	 Declaration: Header Files/Player.h								*
*																	*
*	 author: rubel hassan   										*
*	 rubelhassan@outlook.com										*
*																	*
*-------------------------------------------------------------------*/

#include "Player.h"
#include <GLFW/glfw3.h>

Player::Player(){

}


Player::~Player(){

}


void Player::update(int key){

	if (key){
		if (m_Position.x >= 860.0f)
			m_Position.x = 860.0f;
		else 
			m_Position = addVector2(m_Position, makeVector2(15.0f, 0.0f));

	}else{
	 if (m_Position.x <= 0.0f)
		m_Position.x = 0.0f;
	 else 
		 m_Position = addVector2(m_Position, makeVector2(-15.0f, 0.0f));
	}
	
	
}