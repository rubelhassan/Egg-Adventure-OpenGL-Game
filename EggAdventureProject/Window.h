/* -----------------------------------------------------------------*
 *																	*
 *	 FileName: Window.h												*
 *	 Description: Create and Initilize glfw window and opengl		*
 *	 author: rubel hassan   										*			
 *   rubelhassan@outlook.com										*
 *																	*
 *------------------------------------------------------------------*/

#ifndef WINDOW_H_INC
#define WINDOW_H_INC


#define MAX_KEYS 1024
#define MAX_BUTTONS 32


#include <GL/glew.h>
#include<iostream>
#include<GLFW/glfw3.h>
#include <vector>

#include "Player.h"
#include "Bird.h"
#include "Egg.h"
#include "Font.h"


class Window{

//	PUBLIC MEMBERS
public:
	static bool m_Keys[MAX_KEYS];
	static bool m_MouseButtons[MAX_BUTTONS];

//	PRIVATE MEMBERS
private:
	int randNum;
	int height, width;
	int m_Width, m_Height;
	const char *m_Title;
	GLfloat eggSpeed = 0.5f;

	GLuint tex_ID;
	bool m_Closed;
	GLuint m_VertexBufferID;

	Player* m_Buscket;
	Bird* m_Birds[5];
    
	Font* m_Font;
	Font* endGameFont[3];
	std::vector<Egg*> *m_Eggs;

    double mx, my;
	bool createEgg = true;
	int eggPredict = 3;
	
	int totalScore = 0;
	bool end = false;
// PROTECTED MEMBERS
protected:
	GLFWwindow *m_Window;


// PUBLIC FUNCTIONS
public:
	Window(const char *title, int width, int height);
	~Window();

	void render();
	void update();
	bool closed() const;
	void clear() const;

	int getWidth() const;
	int getHeight() const;

	void setgl();
	void draw();
	void loadAndBufferImage(const char *filename, int n);
	
	bool isKeyPressed(unsigned int keycode) const;
	bool isMousePressed(unsigned int button) const;

// PRIVATE FUNCTIONS
private:
	bool init();
	friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend static void end_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void dropEggs(int n);

	// text rendering
	void render_text(const char *text, float x, float y, float sx, float sy);
	void renderText(char* t);
	void close();
};

#endif //	<-- WINDOW_H_INC
