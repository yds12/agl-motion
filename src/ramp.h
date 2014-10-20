#ifndef _AGL_RAMP_H
#define _AGL_RAMP_H

#include "agl/drawer.h"
#include "agl/vector2.h"
#include "agl/intvector2.h"
#include "agl/image.h"
#include "agl/gameobject.h"
#include "agl/motion/iphysicalobject.h"

namespace AGL
{
	/// Represents a ramp.
	class Ramp : public IPhysicalObject
	{
		private:
			bool leftToRight;
			
		public:			
			/// Creates a new instance of the Ramp class
			///
			/// @param position position of the Ramp
			/// @param image image of the Ramp
			/// @param size size of the object
			/// @param leftToRight whether the ramp grows from the left to the right
			Ramp(Vector2 &position, Image* image, IntVector2 &size, bool leftToRight);
			
			/// Creates a new instance of the Ramp class
			///
			/// @param drawer drawer to which this Ramp is associated
			/// @param position position of the Ramp
			/// @param image image of the Ramp
			/// @param size size of the object
			/// @param leftToRight whether the ramp grows from the left to the right
			Ramp(Drawer* drawer, Vector2 &position, Image* image, IntVector2 &size, bool leftToRight);
			
			/// Creates a new instance of the Ramp class
			///
			/// @param drawer drawer to which this Ramp is associated
			/// @param position position of the Ramp
			/// @param image image of the Ramp
			/// @param leftToRight whether the ramp grows from the left to the right
			Ramp(Drawer* drawer, Vector2 &position, Image* image, bool leftToRight);
			
			/// Returns whether the ramp grows from left to right
			bool isLeftToRight();
			
			/// Gets the Y coordinate of the ramp surface at a specified X
			///
			/// @param x X coordinate
			/// @return the Y coordinate
			float getY(float x);
	};
}

#endif

