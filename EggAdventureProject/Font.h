/* -----------------------------------------------------------------*
*																	*
*	 CLASS NAME: Font												*
*	 DESCRIPTION: Create Font object to render on window			*
*	 DEFINATION: Source Files/Font.cpp								*
*	 BASE CLASS: n/a												*
*																	*
*	 author: rubel hassan											*
*    rubelhassan@outlook.com										*
*																	*
*-------------------------------------------------------------------*/

#ifndef FONT_H_INC
#define FONT_H_INC

#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>

class Font{
private:

	unsigned int m_Width, m_Height, m_Texture;
	static FT_Library LIBRARY;

public:
	Font();
	Font(const char* fontPath, int size, std::string output);
	~Font();
	void render(GLfloat x, GLfloat y, int color);

private:
	bool init();
};


#endif // <-- FONT_H_INC