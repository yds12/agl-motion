#ifndef _AGL_PHYSICALENVIRONMENT_H
#define _AGL_PHYSICALENVIRONMENT_H

/// @mainpage AGL - Aleva Game Library
/// @section Libraries
/// AGL Libraries
/// - <a href="../../index.html">agl: main AGL Library.</a>
/// - <a href="../../agl-graphics/html/index.html">agl-graphics: AGL Graphics Library.</a>
/// - <a href="../../agl-mapping/html/index.html">agl-mapping: AGL Mapping Library.</a>
/// - agl-motion: AGL Motion Library.

namespace AGL
{
	/// Physical environment, where all physical events occurs.
	class PhysicalEnvironment
	{
		public:
			/// Ramp adherence (do not modify)
			static float rampAdherence;
			
			/// Ramp adjustment (do not modify)
			static float rampAdjustment;
			
			/// Tangent of the ramp inclination that causes the MovingObject to slip
			static float rampSlipTangent;
			
			/// Force that causes the MovingObject to slip
			static float rampSlipForce;
		
			/// Gravity value, that pulls the MovingObjects down
			static float gravity;

			/// Maximum speed acquired by an object in free fall
			static float maxFallSpeed;

			/// Default mass of MovingObjects
			static float defaultObjectMass;

			/// Sets the properties to their default values:
			/// rampAdherence = 3
			/// rampAdjustment = 0.5
			/// rampSlipTangent = 1
			/// rampSlipForce = 0.7f
			/// gravity = 0.4
			/// maxFallSpeed = 10
			/// defaultObjectMass = 10
			static void setDefaults();
	};
}

#endif

