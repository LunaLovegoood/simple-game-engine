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