#ifndef _AGL_IPHYSICALOBJECT_H
#define _AGL_IPHYSICALOBJECT_H

#include <vector>
#include "agl/gameobject.h"
#include "agl/floatrectangle.h"
#include "agl/motion/physicalenvironment.h"

namespace AGL
{
	/// Interface that represents physical objects
	class IPhysicalObject : public GameObject
	{
		public:
			/// Mass of the MovingObject
			float mass;
			
			/// Physical size of the MovingObject
			IntVector2* physicalSize;
			
			/// Whether this MovingObject is an elevator, i.e., it can carry other objects
			bool isElevator;
			
			/// Whether a MovingObject can pass through this MovingObject, unless from above (recommended for elevators, 
        	/// otherwise some bugs may occur)
			bool isPassable;
			
			/// Whether this MovingObject represents an solid object, i.e., it can not be crossed
			bool solid;
			
			/// A FloatRectangle object that represents the position and physical size of the MovingObject
			FloatRectangle getPhysicalBounds();
			
			/// Creates a new instance of the IPhysicalObject class
			IPhysicalObject();
			
			/// Creates a new instance of the IPhysicalObject class
			///
			/// @param position position of the IPhysicalObject
			IPhysicalObject(Vector2 &position);
			
			/// Creates a new instance of the IPhysicalObject class
			///
			/// @param image image of the IPhysicalObject
			/// @param position position of the IPhysicalObject
			IPhysicalObject(Image* image, Vector2 &position);
			
			/// Creates a new instance of the IPhysicalObject class
			///
			/// @param drawer drawer to which this object is associated
			/// @param image image of the IPhysicalObject
			/// @param position position of the IPhysicalObject
			IPhysicalObject(Drawer* drawer, Image* image, Vector2 &position);
			
			/// Creates a new instance of the IPhysicalObject class
			///
			/// @param position position of the IPhysicalObject
			/// @param physicalSize physical size of the IPhysicalObject
			IPhysicalObject(Vector2 &position, IntVector2 &physicalSize);
			
			/// Creates a new instance of the IPhysicalObject class
			///
			/// @param image image of the IPhysicalObject
			/// @param position position of the IPhysicalObject
			/// @param physicalSize physical size of the IPhysicalObject
			IPhysicalObject(Image* image, Vector2 &position, IntVector2 &physicalSize);
			
			/// Creates a new instance of the IPhysicalObject class
			///
			/// @param drawer drawer to which this object is associated
			/// @param image image of the IPhysicalObject
			/// @param position position of the IPhysicalObject
			/// @param physicalSize physical size of the IPhysicalObject
			IPhysicalObject(Drawer* drawer, Image* image, Vector2 &position, IntVector2 &physicalSize);
	};
}

#endif

