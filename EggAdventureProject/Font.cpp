/* -----------------------------------------------------------------*
*																	*
*	 FileName: Font.cpp												*
*	 Description: Create and render Fonts on window					*
*	 Declaration: Header Files/Font.h								*
*																	*
*	 author: rubel hassan   										*
*	 rubelhassan@outlook.com										*
*																	*
*-------------------------------------------------------------------*/

#include "Font.h"
#include <iostream>
#include <ftglyph.h>
#include <string>
#include <vector>

#include "Vector2.h"


int to_nearest_pow2(const int num) {
	int nearest = 2;

	while ((nearest <<= 1) < num);

	return nearest;

}


FT_Library Font::LIBRARY = NULL;

Font::Font(){
	
}


Font::Font(const char* fontPath, int size, std::string output): m_Width(64), m_Height(2), m_Texture(0){
	
	init();

	FT_Face face = NULL;
	int error = FT_New_Face(Font::LIBRARY, fontPath, 0, &face);
	
	if (error == FT_Err_Unknown_File_Format) {
		std::cout << "Error: Unknown file format for font \"" << fontPath << "\"" << std::endl;
	}
	else if (error) {
		std::cout << "Error: Could not open font \"" << fontPath << "\"" << std::endl;
	}
	
	
	error = FT_Set_Pixel_Sizes(face, 0, size);

	if (error)
		std::cout << "Error: font.cpp set pixel" << std::endl;


	int numChars = output.size();
	m_Width = to_nearest_pow2(numChars*size);
	m_Height = to_nearest_pow2(size);
	
	std::vector<unsigned char> buffer(m_Width*m_Height, 0);

	Vector2 pen; // initially x and y are 0.0
	
	for (int i = 0; i < (output.size()); i++){
		error = FT_Load_Char(face, output[i], FT_LOAD_RENDER);

		if (error) {
			std::cout << "Error: Could not load char \"" << output[i] << "\"" << std::endl;
			continue;
		}

		FT_Bitmap bmp = face->glyph->bitmap;
		int advance = (face->glyph->advance.x >> 6);

		int bitmapWidth = bmp.width;
		int bitmapHeight = bmp.rows;

		for (int h = 0; h < bitmapHeight; ++h) {
			for (int w = 0; w < bitmapWidth; ++w) {
				int index = h * m_Width + (int)pen.x;

				buffer[index + w] = bmp.buffer[w + bitmapWidth * h];
			}
		}

		pen.x += advance;
	}
	

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, m_Width, m_Height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, &buffer[0]);

	FT_Done_Face(face);
	
}


Font::~Font(){
	glDeleteTextures(1, &m_Texture);
}


bool Font::init(){

	if (Font::LIBRARY == NULL){
		if (FT_Init_FreeType(&Font::LIBRARY)) {
			std::cout << "Font.cpp: Failed to initialize FreeType!" << std::endl;
			return false;
		}
	}
	

	return true;
}

void Font::render(GLfloat x, GLfloat y, int color){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glLoadIdentity();
	glPushMatrix();

	if (color == 1)
		glColor3f(1.0f, 0.0f, 0.0f);
	else
		glColor3f(1.0f, 1.0f, 1.0f);

	// glTranslatef(850.0f, 530.0f, 0.0f);
	glTranslatef(x, y, 0.0f);
	glRotatef(180.0f, -1.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
		glTexCoord2d(0, 0); glVertex2f(0.0f, 0.0f);
		glTexCoord2d(1, 0); glVertex2f(150.0f, 0.0f);
		glTexCoord2d(1, 1); glVertex2f(150.0f, 30.0f);
		glTexCoord2d(0, 1); glVertex2f(0.0f, 30.0f);
		glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(1.0f, 1.0f, 1.0f);

	
}
