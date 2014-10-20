#include "agl/motion/physicalenvironment.h"

// Ramp adherence
float AGL::PhysicalEnvironment::rampAdherence;

// Ramp adjustment
float AGL::PhysicalEnvironment::rampAdjustment;

// Tangent of the ramp inclination that causes the MovingObject to slip
float AGL::PhysicalEnvironment::rampSlipTangent;
			
/// Force that causes the MovingObject to slip
float AGL::PhysicalEnvironment::rampSlipForce;

// Gravity value, that pulls the MovingObjects down
float AGL::PhysicalEnvironment::gravity;

// Maximum speed acquired by an object in free fall
float AGL::PhysicalEnvironment::maxFallSpeed;

// Default mass of MovingObjects
float AGL::PhysicalEnvironment::defaultObjectMass;
			
void AGL::PhysicalEnvironment::setDefaults()
{
	rampAdherence = 3;
	rampAdjustment = 0.5f;
	rampSlipTangent = 1;
	rampSlipForce = 0.7f;
	gravity = 0.4f;
	maxFallSpeed = 10;
	defaultObjectMass = 10;
}

