// Simple game engine
// Copyright (C) 2018 Yurii Khomiak 
// Yurii Khomiak licenses this file to you under the MIT license. 
// See the LICENSE file in the project root for more information.

#ifndef VERTEX_H_
#define VERTEX_H_

#include <GL/glew.h>


// Represents 2D position
struct Position
{
	float x{};
	float y{};
};

// Represents RGB and Alpha
struct Color
{
	GLubyte r{ 0 };
	GLubyte g{ 0 };
	GLubyte b{ 0 };
	GLubyte alpha{ 255 };
};

// Represents vertex as it's position and color
struct Vertex
{
	Position position{};

	Color color{};
};

#endif // VERTEX_H_