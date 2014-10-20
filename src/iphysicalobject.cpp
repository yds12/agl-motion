#include "agl/motion/iphysicalobject.h"

AGL::IPhysicalObject::IPhysicalObject() : AGL::GameObject()
{
	mass = PhysicalEnvironment::defaultObjectMass;
	solid = true;
	isPassable = false;
}

AGL::IPhysicalObject::IPhysicalObject(Vector2 &position) : AGL::GameObject(position)
{
	mass = PhysicalEnvironment::defaultObjectMass;
	solid = true;
	isPassable = false;
}

AGL::IPhysicalObject::IPhysicalObject(Image* image, Vector2 &position) : AGL::GameObject(image, position)
{
	mass = PhysicalEnvironment::defaultObjectMass;
	solid = true;
	physicalSize = new IntVector2(image->size->x, image->size->y);
	isPassable = false;
}

AGL::IPhysicalObject::IPhysicalObject(Drawer* drawer, Image* image, Vector2 &position) : AGL::GameObject(drawer, image, position)
{
	mass = PhysicalEnvironment::defaultObjectMass;
	solid = true;
	physicalSize = new IntVector2(image->size->x, image->size->y);
	isPassable = false;
}

AGL::IPhysicalObject::IPhysicalObject(Vector2 &position, IntVector2 &physicalSize) : AGL::GameObject(position)
{
	mass = PhysicalEnvironment::defaultObjectMass;
	solid = true;
	this->physicalSize = new IntVector2(physicalSize);
	isPassable = false;
}

AGL::IPhysicalObject::IPhysicalObject(Image* image, Vector2 &position, IntVector2 &physicalSize) : AGL::GameObject(image, position)
{
	mass = PhysicalEnvironment::defaultObjectMass;
	solid = true;
	this->physicalSize = new IntVector2(physicalSize);
	isPassable = false;
}

AGL::IPhysicalObject::IPhysicalObject(Drawer* drawer, Image* image, Vector2 &position, IntVector2 &physicalSize) : AGL::GameObject(drawer, image, position)
{
	mass = PhysicalEnvironment::defaultObjectMass;
	solid = true;
	this->physicalSize = new IntVector2(physicalSize);
	isPassable = false;
}

AGL::FloatRectangle AGL::IPhysicalObject::getPhysicalBounds()
{
	FloatRectangle fr(position->x, position->y, physicalSize->x, physicalSize->y);	
	return fr;
}

