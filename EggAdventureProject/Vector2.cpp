/* -----------------------------------------------------------------*
*																	*
*	 FileName: Vector2.cpp											*
*	 Description: Create Vector2 struct to store x, y coords value	*
*	 Declaration: Header Files/Vector2.h							*
*																	*
*	 author: rubel hassan											*
*	 rubelhassan@outlook.com										*
*																	*
*-------------------------------------------------------------------*/

#include "Vector2.h"


Vector2 makeVector2(GLfloat x, GLfloat y){
	Vector2 newVector;
	newVector.x = x;
	newVector.y = y;
	return newVector;

}


Vector2 addVector2(Vector2 first, Vector2 second){

	Vector2 newVector;
	newVector.x = first.x + second.x;
	newVector.y = first.y + second.y;
	return newVector;
}


