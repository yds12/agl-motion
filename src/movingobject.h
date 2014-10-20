#ifndef _AGL_MOVINGOBJECT_H
#define _AGL_MOVINGOBJECT_H

#include <vector>
#include "agl/gameobject.h"
#include "agl/floatrectangle.h"
#include "agl/motion/ramp.h"
#include "agl/motion/physicalenvironment.h"

/// @mainpage AGL - Aleva Game Library
/// @section Libraries
/// AGL Libraries
/// - <a href="../../index.html">agl: main AGL Library.</a>
/// - <a href="../../agl-graphics/html/index.html">agl-graphics: AGL Graphics Library.</a>
/// - <a href="../../agl-mapping/html/index.html">agl-mapping: AGL Mapping Library.</a>
/// - agl-motion: AGL Motion Library.

namespace AGL
{
	/// Represents a GameObject that exists physically in the game map, interacting with other MovingObjects. This class can be used
   /// to represent sprites, blocks, elevators, ramps, and platforms, among other things
	class MovingObject : public IPhysicalObject
	{
		private:
			bool reversePath;
			unsigned short goingToPath;
			vector<Vector2>* path;
			Vector2* acceleration;
			Vector2* speed;
			IPhysicalObject *top, *right, *bottom, *left;
			
			void move(Vector2 &constantSpeed, vector<IPhysicalObject*> &obstacles, bool modifySpeed);
		
		public:			
			/// Force stored in the MovingObject, which will be applied in the next "update"
			Vector2* storedForce;
					
			/// Acceleration of the MovingObject
			Vector2 getAcceleration();
			
			/// Speed of the MovingObject
			Vector2 getSpeed();
			
			/// Whether the MovingObject collides with another on top
			bool collidesOnTop();
			
			/// Whether the MovingObject collides with another on right
			bool collidesOnRight();
			
			/// Whether the MovingObject collides with another on bottom
			bool collidesOnBottom();
			
			/// Whether the MovingObject collides with another on left
			bool collidesOnLeft();
			
			/// MovingObject that collides with this on top
			IPhysicalObject* getObjectOnTop();
			
			/// MovingObject that collides with this on right
			IPhysicalObject* getObjectOnRight();
			
			/// MovingObject that collides with this on bottom
			IPhysicalObject* getObjectOnBottom();
			
			/// MovingObject that collides with this on left
			IPhysicalObject* getObjectOnLeft();
			
			/// Creates a new instance of the MovingObject class
			MovingObject();

			/// Creates a new instance of the MovingObject class
			///
			/// @param position Position of the MovingObject
			MovingObject(Vector2 &position);

			/// Creates a new instance of the MovingObject class
			///
			/// @param position Position of the MovingObject
			/// @param physicalSize Physical size of the MovingObject
			MovingObject(Vector2 &position, IntVector2 &physicalSize);

			/// Creates a new instance of the MovingObject class
			///
			/// @param position Position of the MovingObject
			/// @param image Image of the MovingObject
			MovingObject(Vector2 &position, Image* image);

			/// Creates a new instance of the MovingObject class
			///
			/// @param drawer drawer to which this MovingObject is associated
			/// @param position Position of the MovingObject
			/// @param image Image of the MovingObject
			MovingObject(Drawer* drawer, Vector2 &position, Image* image);
			
			/// Moves the MovingObject considering the physics (including gravity) and obstacles, checking collisions and calculating 
			/// the acceleration, speed and final position of the object. If some obstacle collide with this, it will be saved in 
			/// the "ObjectOn..." properties. The collision verification considers a rectangle that contains the old and the new rectangular 
			/// bounds of this MovingObject.
			/// 
			/// @param forces Resulting force applied on the object
			/// @param obstacles Obstacles that can collide with this MovingObject
			void move(Vector2 &forces, vector<IPhysicalObject*> &obstacles);
			
			/// Moves the MovingObject considering the physics (including gravity) and obstacles, checking collisions and calculating 
			/// the acceleration, speed and final position of the object. If some obstacle collide with this, it will be saved in 
			/// the "ObjectOn..." properties. The collision verification considers a rectangle that contains the old and the new rectangular 
			/// bounds of this MovingObject.
			/// 
			/// @param forces Resulting force applied on the object
			/// @param obstacles Obstacles that can collide with this MovingObject
			/// @param ramps Ramps that can collide with this MovingObject
			void move(Vector2 &forces, vector<IPhysicalObject*> &obstacles, vector<Ramp*> &ramps);

			/// Sets the MovingObject to move in a fixed direction, with a constant speed.
			///
			/// @param rotation Indicates the direction. E.g.: 0 is right, pi is left.
			/// @param speed The speed of movement
			void moveFixed(float rotation, float speed);

			/// Sets the MovingObject to move in a fixed direction, with a constant speed, considering collisions.
			/// 
			/// @param rotation Indicates the direction. E.g.: 0 is right, pi is left.
			/// @param speed The speed of movement
			/// @param obstacles Obstacles that can collide with this MovingObject
			/// @param ramps Ramps that can collide with this MovingObject
			void moveFixed(float rotation, float speed, vector<IPhysicalObject*> &obstacles, vector<Ramp*> &ramps);

			/// Moves the MovingObject towards a specified aim, with a specified constant speed
			///
			/// @param aim Aim of the MovingObject
			/// @param absoluteSpeed Constant speed of the movement
			void moveTowards(Vector2 &aim, float absoluteSpeed);

			/// Move the MovingObject constantly between two points
			///
			/// @param aim Second point of the path (the first is the initial position)
			/// @param absoluteSpeed Constant speed of the movement
			void patrol(Vector2 &aim, float absoluteSpeed);

			/// Makes the MovingObject follow a closed path
			///
			/// @param points Points of the path
			/// @param absoluteSpeed Constant speed of the movement
			void followClosedPath(vector<Vector2> &points, float absoluteSpeed);

			/// Makes the MovingObject follow an open path
			/// 
			/// @param points Points of the path
			/// @param absoluteSpeed Constant speed of the movement
			void followOpenPath(vector<Vector2> &points, float absoluteSpeed);

			/// Stops immediately the MovingObject
			void stop();

			/// Moves an elevator MovingObject towards a specified aim, with a specified constant speed, considering the collisions between
			/// the elevator and other objects, and between the possible passengers of the elevator and other objects
			///
			/// @param aim Aim of the MovingObject
			/// @param absoluteSpeed Constant speed of the movement
			/// @param sprites MovingObject that can be carried by this elevator
			/// @param obstacles MovingObject that can collide with the possible passengers of the elevator
			void moveElevatorTowards(Vector2 &aim, float absoluteSpeed, vector<MovingObject*> &sprites, vector<IPhysicalObject*> &obstacles);

			/// Moves an elevator MovingObject between two points constantly, with a specified constant speed, considering the 
			/// collisions between the elevator and other objects, and between the possible passengers of the elevator and other objects
			/// 
			/// @param aim Aim of the MovingObject
			/// @param absoluteSpeed Constant speed of the movement
			/// @param sprites MovingObject that can be carried by this elevator
			/// @param obstacles MovingObject that can collide with the possible passengers of the elevator
			void patrolElevator(Vector2 &aim, float absoluteSpeed, vector<MovingObject*> &sprites, vector<IPhysicalObject*> &obstacles);

			/// Moves an elevator MovingObject through a closed path, with a specified constant speed, considering the 
			/// collisions between the elevator and other objects, and between the possible passengers of the elevator and other objects
			/// 
			/// @param points Path of the MovingObject
			/// @param absoluteSpeed Constant speed of the movement
			/// @param sprites MovingObjects that can be carried by this elevator
			/// @param obstacles MovingObjects that can collide with the possible passengers of the elevator
			void followElevatorClosedPath(vector<Vector2> &points, float absoluteSpeed, vector<MovingObject*> &sprites, vector<IPhysicalObject*> &obstacles);

			/// Moves an elevator MovingObject through an open path, with a specified constant speed, considering the 
			/// collisions between the elevator and other objects, and between the possible passengers of the elevator and other objects
			/// 
			/// @param points Path of the MovingObject
			/// @param absoluteSpeed Constant speed of the movement
			/// @param sprites MovingObjects that can be carried by this elevator
			/// @param obstacles MovingObjects that can collide with the possible passengers of the elevator
			void followElevatorOpenPath(vector<Vector2> &points, float absoluteSpeed, vector<MovingObject*> &sprites, vector<IPhysicalObject*> &obstacles);	
	};
}

#endif

