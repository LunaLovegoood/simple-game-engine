// Simple game engine
// Copyright (C) 2018 Yurii Khomiak 
// Yurii Khomiak licenses this file to you under the MIT license. 
// See the LICENSE file in the project root for more information.

#include "Sprite.h"
#include "Vertex.h"

#include <cstddef>


const int NUM_QUAD_VERTICES = 6;

Sprite::Sprite(float x, float y, float width, float height)
	: x_(x), y_(y), 
	width_(width), height_(height)
{
	glGenBuffers(1, &vboID_);

	loadBuffer();
}

Sprite::~Sprite()
{
	if (vboID_)
	{
		glDeleteBuffers(1, &vboID_);
	}
}

// Initialize the sprite
void Sprite::init(float x, float y, float width, float height)
{
	x_ = x;
	y_ = y;
	width_ = width;
	height_ = height;

	if (!vboID_)
	{
		glGenBuffers(1, &vboID_);
	}

	loadBuffer();
}

// Load data into buffer
void Sprite::loadBuffer()
{
	// Vertex coordinates
	Vertex vertexData[NUM_QUAD_VERTICES];

	// First triangle
	vertexData[0].position = { x_, y_ };

	vertexData[1].position = { x_, y_ + height_ };

	vertexData[2].position = { x_ + width_, y_ + height_ };

	// Second triangle
	vertexData[3].position = { x_, y_ };

	vertexData[4].position = { x_ + width_, y_ };

	vertexData[5].position = { vertexData[2].position.x, vertexData[2].position.y };

	// Initialize color of vertices
	vertexData[1].color = { 0, 0, 255, 255 };
	vertexData[2].color = vertexData[5].color = { 255, 0, 0, 255 };
	vertexData[4].color = { 0, 255, 0, 255 };
	vertexData[0].color = vertexData[3].color = { 255, 255, 255, 255 };

	// Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, vboID_);

	// Upload data into buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	// Unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Draw sprite
void Sprite::draw() const
{
	if (!vboID_)
	{
		return;
	}

	// Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, vboID_);

	// Enable first array
	glEnableVertexAttribArray(0);

	// Setting position attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
	// Setting color attribute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, color));

	// Draw from buffer
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// Disable first array
	glDisableVertexAttribArray(0);

	// Unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}