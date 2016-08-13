/* -----------------------------------------------------------------*
*																	*
*	 FILE NAME: Vector2.h											*
*	 DESCRIPTION: Create Vector2 struct to store x, y coords value	*
*	 DEFINATION: Source Files/Vector2.cpp							*
*																	*
*																	*
*	 author: rubel hassan											*
*    rubelhassan@outlook.com										*
*																	*
*-------------------------------------------------------------------*/

#ifndef VECTOR_2_H_INC
#define VECTOR_2_H_INC
#include <GL/glew.h>


struct Vector2{

	Vector2() : x(0.0f), y(0.0f) {

	}

	GLfloat x;
	GLfloat y;

};


Vector2 makeVector2(GLfloat x, GLfloat y);
Vector2 addVector2(Vector2 first, Vector2 second);

#endif // <-- VECTOR_2_H_INC