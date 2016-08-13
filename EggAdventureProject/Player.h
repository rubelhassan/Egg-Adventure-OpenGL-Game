/* -----------------------------------------------------------------*
*																	*
*	 CLASS NAME: Player											    *
*	 DESCRIPTION: Create player to render on window					*
*	 DEFINATION: Source Files/Player.cpp							*
*	 BASE CLASS: Sprite.h											*
*																	*
*	 author: rubel hassan											*
*    rubelhassan@outlook.com										*
*																	*
*-------------------------------------------------------------------*/

#ifndef PLAYER_H_INC
#define PLAYER_H_INC

#include <iostream>
#include "Sprite.h"


class Player : public Sprite{
public:


private:
	
public:
	Player();
	~Player();
	void update(int key);
};

#endif