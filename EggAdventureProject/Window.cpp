/* -----------------------------------------------------------------*
 *																	*
 *	 FileName: Window.cpp											*
 *	 Description: Create and Initilize glfw window and opengl		*
 *   Declaration: Header Files/Window.h								*
 *	 author: rubel hassan											*
 *   rubelhassan@outlook.com										*
 *																	*
 *------------------------------------------------------------------*/

#include "SOIL/SOIL.h"
#include "Window.h"
#include <cstdlib>
#include <ctime>

#include "VertexStucture.h"


#define EGG_PREDICT_MAX 10000

VertexData vertices[] = {
	{ { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f ,0.0f} },
	{ { 960.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } },
	{ { 960.0f, 540.0f, 0.0f }, { 1.0f, 1.0f, 0.0f } },
	{ { 0.0f, 540.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } }
};



bool Window::m_Keys[MAX_KEYS];
bool Window::m_MouseButtons[MAX_BUTTONS];

/******************************************************************************
 *		  NON MEMBER GLOBAL FUNCTIONS FORWARD DECLARATION                     *
 ******************************************************************************/

void windowResize(GLFWwindow *window, int width, int height);



/******************************************************************************
 *				CONSTURCTOR AND DESTRUCTOR DEFINATIONS                        *
 ******************************************************************************/

Window::Window(const char *title, int width, int height){
	m_Title = title;
	m_Width = width;
	m_Height = height;

	m_VertexBufferID = 0;

	if (!init())
		glfwTerminate();

	for (int i = 0; i < MAX_KEYS; i++){
		m_Keys[i] = false;
	}

	for (int i = 0; i < MAX_BUTTONS; i++){
		m_MouseButtons[i] = false;
	}	

	std::cout << "**************************  Welcome to EGG ADVENTURE!!! ************************" << std::endl;
	std::cout << "***************  Created with C++, OpenGL, GLFW, SOIL, FREETYPE   **************" << std::endl;
	std::cout << "**************************  Developed by Rubel Hassan   ************************" << std::endl;

}

/* --------    Clear memory after object terminates --------------------- */
Window::~Window(){
	glfwTerminate();
	for (std::vector<Egg*>::iterator eggIter = m_Eggs->begin();
		eggIter != m_Eggs->end(); eggIter++){

		delete (*eggIter);
	}

	delete m_Eggs;
	delete m_Buscket;

	glDeleteTextures(1, &tex_ID);
	glDeleteBuffers(1, &m_VertexBufferID);

	glfwDestroyWindow(m_Window);
}



/******************************************************************************
*				WINDOW CLASS MEMBER FUNCTIONS DEFINATION                      *
******************************************************************************/

/* -----------------      CLOSED   ---------------------------*/

bool Window::closed() const{
	return glfwWindowShouldClose(m_Window) == 1;
}

/* -----------------      INIT   ---------------------------*/

bool Window::init(){

	if (!glfwInit()){
		std::cout << "GLFW init error!" << std::endl;
		return false;
	}

	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

	if (!m_Window){
		glfwTerminate();
		std::cout << "Failed to create GLFW Window!" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, this);
	glfwSetWindowSizeCallback(m_Window, windowResize);
	glfwSetKeyCallback(m_Window, key_callback);

	if (glewInit() != GLEW_OK){
		std::cout << "GLEW init failure!" << std::endl;
		return false;
	}

	

	return true;
}


/* -----------------      GETWIDTH , GETHEIGHT   ---------------------------*/

int Window::getWidth() const{
	return m_Width;
}

int Window::getHeight() const{
	return m_Height;
}


/* -----------------      SETGL   ---------------------------*/

void Window::setgl(){

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, (float)getWidth(), 0.0f, (float)getHeight(), -1.0f, 0.0f);
	//gluOrtho2D(0,mainWindow.getWidth(), 0, mainWindow.getHeight());
	glMatrixMode(GL_MODELVIEW);


/* ---------       OBJECTS INITILIZATION             ------------ */
	
	m_Buscket = new Player();
	//m_Buscket->setVelocity(makeVector2(0.1f, 0.1f));

	m_Font = new Font("FreeSans.ttf", 28, "SCORE: 0");

	m_Birds[0] = new Bird();
	m_Birds[0]->setVelocity(makeVector2(1.0f, 15.0f));


	m_Birds[1] = new Bird();
	m_Birds[1]->setVelocity(makeVector2(0.5f, 10.0f));


	m_Birds[2] = new Bird();
	m_Birds[2]->setVelocity(makeVector2(2.0f, 7.5f));

	
	m_Birds[3] = new Bird();
	m_Birds[3]->setVelocity(makeVector2(3.0f, 5.0f));

	
	m_Birds[4] = new Bird();
	m_Birds[4]->setVelocity(makeVector2(4.0f, 2.5f));

	m_Eggs = new std::vector<Egg*>;


}

/* -----------------      CLEAR   ---------------------------*/

void Window::clear() const{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


/* -----------------      RENDER   ---------------------------*/

void Window::render(){

	// load image as texture
	loadAndBufferImage("images/background.png", 0);

	// set buffer arrays with position and text coords data
	glGenBuffers(1, &m_VertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(VertexData), (GLvoid *)offsetof(VertexData, position));

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(3, GL_FLOAT, sizeof(VertexData), (GLvoid *)offsetof(VertexData, texture));

	glPushMatrix();
	glDrawArrays(GL_QUADS, 0, 4);
	glPopMatrix();

	glDeleteTextures(1, &tex_ID);
	glDeleteBuffers(1, &m_VertexBufferID);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindTexture(GL_TEXTURE_2D, 0);

	
	glPushMatrix();
	m_Buscket->init("images/bucket.png");
	glPopMatrix();

	glPushMatrix();
	m_Font->render(850.0f, 530.0f, 1);
	glPopMatrix();
	

	for (int i = 0; i < 5; i++){
		glPushMatrix();
		m_Birds[i]->init("images/bird.png");
		glPopMatrix();
	}


	if (!m_Eggs->empty()){
		for (std::vector<Egg*>::iterator eggIter = m_Eggs->begin();
			eggIter != m_Eggs->end(); eggIter++){
			glPushMatrix();
			(*eggIter)->init("images/egg.png");
			glPopMatrix();
		}
	}
	

}


/* -----------------      DROP_EGGS  ---------------------------*/

void Window::dropEggs(int n){
	Egg *newEgg = new Egg(m_Birds[n]->getPosition().x, m_Birds[n]->getPosition().y);
	newEgg->setVelocity( makeVector2(0.0f, (GLfloat)-(n*eggSpeed + 0.1)) );
	m_Eggs->push_back(newEgg);
}


/* -----------------      DRAW PER FRAME  ---------------------------*/

void Window::draw(){
	for (int i = 0; i < 5; i++)
		m_Birds[i]->update();

	if (!m_Eggs->empty()){
		for (std::vector<Egg*>::iterator eggIter = m_Eggs->begin();
			eggIter != m_Eggs->end();){

			//(*eggIter)->update(1);

			if (((*eggIter)->getPosition().y <= m_Buscket->getPosition().y + 60.0f)
				&& ((*eggIter)->getPosition().y >= m_Buscket->getPosition().y)){

				if (((*eggIter)->getPosition().x > m_Buscket->getPosition().x) &&
					((*eggIter)->getPosition().x < m_Buscket->getPosition().x + 100.0f)){
					
					delete (*eggIter);
					eggIter = m_Eggs->erase(eggIter);

					totalScore += 10;
					std::cout << "Egg is caught " <<totalScore<< std::endl;
					delete m_Font;
					m_Font = new Font("FreeSans.ttf", 28, "SCORE: " + std::to_string(totalScore));
					m_Font->render(850.0f, 530.0f, 1);

					if (end){
						
						GLFWwindowrefreshfun();
						glfwWaitEvents();

						int key = glfwGetKey(m_Window, GLFW_KEY_ENTER);
						if (key == GLFW_KEY_ENTER){
							close();
						}

					} // check end game


				}
				else{
					(*eggIter)->update(1);
					eggIter++; // increment
				}

			}else if ((*eggIter)->getPosition().y < m_Buscket->getPosition().y){
				std::cout << "Window.cpp:: egg is out" << std::endl;
				delete (*eggIter);
				eggIter = m_Eggs->erase(eggIter);

			}else{
				(*eggIter)->update(1);
				eggIter++; // increment
			}


		}

		// checking for highscore it it is equal or above 100 = 10 eggs to pick up
		if ( totalScore >= 100){
			endGameFont[0] = new Font("FreeSans.ttf", 28, "LEVEL FINISHED");
			endGameFont[0]->render((GLfloat)m_Width / 2.0, ((GLfloat)m_Height / 2.0) + 50, 1);

			endGameFont[1] = new Font("FreeSans.ttf", 16, "PRESS ENTER");
			endGameFont[1]->render((GLfloat)m_Width / 2.0, (GLfloat)m_Height / 2.0 - 30.0f, 2);

			endGameFont[1] = new Font("FreeSans.ttf", 16, "TO EXIT");
			endGameFont[1]->render((GLfloat)m_Width / 2.0, (GLfloat)m_Height / 2.0, 2);

			end = true;
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetKeyCallback(m_Window, end_callback);
		}


	} // END OF IF

	
	//std::cout << "Window.cpp: "<< Egg::count << std::endl;

	/*if (Window::m_Keys[GLFW_KEY_LEFT] == true){
		m_Buscket->update(0);
		Window::m_Keys[GLFW_KEY_LEFT] = false;
	}
	if (Window::m_Keys[GLFW_KEY_RIGHT] == true){
		m_Buscket->update(1);
		Window::m_Keys[GLFW_KEY_RIGHT] = false;
	}*/
}


/* -----------------      UPDATE   ---------------------------*/

void Window::update(){
	if (createEgg){
		if (eggPredict % 5 == 0){
			randNum = rand() % 5;
			dropEggs(randNum);
		}
		//createEgg = false;

	}else{
		createEgg = true;
	}

	eggPredict++;
	if (eggPredict > EGG_PREDICT_MAX) eggPredict = 0;

	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}


/* -----------------      LOAD_AND_BUFFER_IMAGE   ---------------------------*/

void Window::loadAndBufferImage(const char *filename, int n){

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &tex_ID);
	// glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_ID);

	unsigned char* image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_AUTO);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);


	//std::cout << width << " " << height << std::endl;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	SOIL_free_image_data(image);
}



/******************************************************************************
 *				NON MEMBER GLOBAL FUNCTIONS DEFINATION                        *
 *****************************************************************************/
void windowResize(GLFWwindow *window, int w, int h){
	glViewport(0, 0, w, h);
}



/****************************************************************************
*						INPUT HANDLING FUNCTIONS                            *
*****************************************************************************/

bool Window::isMousePressed(unsigned int button) const{
	if (button >= MAX_BUTTONS)
		return false;

	return m_MouseButtons[button];

}

bool Window::isKeyPressed(unsigned int keycode) const{
	if (keycode >= MAX_KEYS)
		return false;


	return m_Keys[keycode];

}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	Window::m_Keys[key] = (action != GLFW_RELEASE);

	if (key == GLFW_KEY_LEFT){
		win->m_Buscket->update(0); // MOVE BUSCKET TO LEFT
	}

	if (key == GLFW_KEY_RIGHT){
		win->m_Buscket->update(1); // MOVE BUSCKET TO RIGHT
	}
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
	glfwGetWindowUserPointer(window);
	Window::m_MouseButtons[button] = (action != GLFW_RELEASE);
}

void end_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (key == GLFW_KEY_ENTER){
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->close();
	}
}

void Window::close(){
	glfwSetWindowShouldClose(m_Window, GL_TRUE);
}