/* -------------------------------------------------------------------
*
*	FileName: main.cpp
*	Description: Initialize Window and Run Game
*	author: rubel hassan
*	rubelhassan@outlook.com
*
*------------------------------------------------------------------*/

#include <stdlib.h>
#include <cstdlib>
#include <GL/glew.h>
#include "Window.h"
#include <iostream>

#define Updates_Per_Second 60


int main(int agrc, char* argv[]){


	Window mainWindow("Egg Adventure", 960, 540);
	
	glfwSwapInterval(0);
	double lastTime = glfwGetTime();
	double deltaTime = 0.0f;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	mainWindow.setgl();
	
	
	while (!mainWindow.closed()){

		mainWindow.clear();

		mainWindow.render();
		
		deltaTime += (glfwGetTime() - lastTime)*Updates_Per_Second;
		lastTime = glfwGetTime();

		while (deltaTime >= 1.0f){
			mainWindow.draw();
			--deltaTime;
		}
		
		mainWindow.update();
	}

	return 0;
}


