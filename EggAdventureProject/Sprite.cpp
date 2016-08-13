/* -----------------------------------------------------------------*
*																	*
*	 FileName: Sprite.cpp											*
*	 Description: Create and render objects on window				*
*	 Declaration: Header Files/Sprite.h								*
*																	*
*	 author: rubel hassan											*
*	 rubelhassan@outlook.com										*
*																	*
*-------------------------------------------------------------------*/

#include "Sprite.h"
#include <GL/glew.h>
#include "SOIL/SOIL.h"

#include "VertexStucture.h"




void Sprite::setPosition(Vector2 position){
	m_Position = position;
}

Vector2 Sprite::getPosition(){
	return m_Position;
}

Sprite::Sprite(GLuint textureID){
	m_TextureBufferID = textureID;
}

Sprite::Sprite(){
	//wX = 500.0f, wY = 60.f;
	wX = 0.0f, wY = 0.0f;
	
	vertSprite[0] = { { wX, wY, 0.0f }, { 0.0f, 0.0f, 0.0f } };
	vertSprite[1] = { { wX + 100.0f, wY, 0.0f }, { 1.0f, 0.0f, 0.0f } };
	vertSprite[2] = { { wX + 100.0f, wY + 70.0f, 0.0f }, { 1.0f, 1.0f, 0.0f } };
	vertSprite[3] = { { wX, wY + 70.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } };
	

	m_TextureBufferID = 0;
	m_Position.x = 500.0f;
	m_Position.y = 60.0f;
}

Sprite::~Sprite(){
	glDeleteTextures(1, &m_TextureBufferID);
	glDeleteBuffers(1, &m_VertexBufferID);
}

/* ----------        INIT		----------------*/
void Sprite::init(const char* filename){
	loadAndBufferImage(filename);
	glGenBuffers(1, &m_VertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertSprite), vertSprite, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(VertexData), (GLvoid *)offsetof(VertexData, position));

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(3, GL_FLOAT, sizeof(VertexData), (GLvoid *)offsetof(VertexData, texture));

	render();
}


/* ----------        RENDER		----------------*/
void Sprite::render(){
	glBindTexture(GL_TEXTURE_2D, m_TextureBufferID);
	glLoadIdentity();
	glTranslatef(m_Position.x, m_Position.y, 0.0f);
	glDrawArrays(GL_QUADS, 0, 4);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteTextures(1, &m_TextureBufferID);
	glDeleteBuffers(1, &m_VertexBufferID);
}

void Sprite::update(int key){
	m_Position = addVector2(m_Position , m_Velocity);
}

void Sprite::update(){
	m_Position = addVector2(m_Position, m_Velocity);
}



/* ----------        LOAD_AND_BUFFER_IMAGE		----------------*/
void Sprite::loadAndBufferImage(const char *filename){

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &m_TextureBufferID);
	glBindTexture(GL_TEXTURE_2D, m_TextureBufferID);

	unsigned char* image = SOIL_load_image(filename, &imageWidth, &imageHeight, 0, SOIL_LOAD_AUTO);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);


	//std::cout << width << " " << height << std::endl;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	SOIL_free_image_data(image);
}


void Sprite::setVelocity(Vector2 newVector){

	m_Velocity = newVector;
}


Vector2 Sprite::getVelocity(){

	return m_Velocity;
}