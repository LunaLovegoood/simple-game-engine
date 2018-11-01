// Simple game engine
// Copyright (C) 2018 Yurii Khomiak 
// Yurii Khomiak licenses this file to you under the MIT license. 
// See the LICENSE file in the project root for more information.

#include "Sprite.h"


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
	float vertexData[12];

	// First triangle
	vertexData[0] = x_;
	vertexData[1] = y_;

	vertexData[2] = x_;
	vertexData[3] = y_ + height_;

	vertexData[4] = x_ + width_;
	vertexData[5] = y_ + height_;

	// Second triangle
	vertexData[6] = x_;
	vertexData[7] = y_;

	vertexData[8] = x_ + width_;
	vertexData[9] = y_;

	vertexData[10] = vertexData[4];
	vertexData[11] = vertexData[5];

	// Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, vboID_);

	// Load data into buffer
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

	// Specify the location and data format of the vertex array
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);

	// Draw from buffer
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// Disable first array
	glDisableVertexAttribArray(0);

	// Unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}