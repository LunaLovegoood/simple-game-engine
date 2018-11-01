// Simple game engine
// Copyright (C) 2018 Yurii Khomiak 
// Yurii Khomiak licenses this file to you under the MIT license. 
// See the LICENSE file in the project root for more information.

#ifndef SPRITE_H_
#define SPRITE_H_

#include <GL/glew.h>

class Sprite
{
public:
	Sprite() = default;
	Sprite(float x, float y, float width, float height);
	~Sprite();

	void init(float x, float y, float width, float height);

	void draw() const;

private:
	float x_{}; // left bottom corner x
	float y_{}; // left bottom corner x
	float width_{};
	float height_{};

	GLuint vboID_{ 0 };

	void loadBuffer();
};

#endif // SPRITE_H_