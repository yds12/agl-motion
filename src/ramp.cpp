#include "agl/motion/ramp.h"

AGL::Ramp::Ramp(AGL::Vector2 &position, AGL::Image* image, AGL::IntVector2 &size, bool leftToRight) 
	: AGL::IPhysicalObject(image, position, size)
{
	this->leftToRight = leftToRight;
}

AGL::Ramp::Ramp(AGL::Drawer* drawer, AGL::Vector2 &position, AGL::Image* image, AGL::IntVector2 &size, bool leftToRight) 
	: AGL::IPhysicalObject(drawer, image, position, size)
{
	this->leftToRight = leftToRight;
}

AGL::Ramp::Ramp(AGL::Drawer* drawer, AGL::Vector2 &position, AGL::Image* image, bool leftToRight) 
	: AGL::IPhysicalObject(drawer, image, position)
{
	this->leftToRight = leftToRight;
}

bool AGL::Ramp::isLeftToRight()
{
	return leftToRight;
}

float AGL::Ramp::getY(float x)
{
	float x1 = leftToRight ? x - position->x : position->x + physicalSize->x - x;
	float y = ((float)physicalSize->y / (float)physicalSize->x) * x1;
	return position->y + physicalSize->y - y;
}

