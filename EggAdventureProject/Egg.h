/* -----------------------------------------------------------------*
 *																	*
 *	 CLASS NAME: Egg												*
 *	 DESCRIPTION: Create Egg object to render on window				*
 *	 DEFINATION: Source Files/Egg.cpp								*
 *	 BASE CLASS: Sprite.h											*
 *																	*
 *	 author: rubel hassan											*
 *   rubelhassan@outlook.com										*
 *																	*
 *-------------------------------------------------------------------*/

#ifndef EGG_H_INC
#define EGG_H_INC


#include <iostream>
#include "Sprite.h"

class Egg : public Sprite{

public:
	static int count;
private:

public:
	Egg();
	~Egg();
	Egg(GLfloat x, GLfloat y);
	void update(int key);

};

#endif // <-- EGG_H_INC
