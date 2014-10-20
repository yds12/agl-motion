#include "agl/motion/movingobject.h"

void AGL::MovingObject::move(AGL::Vector2 &constantSpeed, vector<AGL::IPhysicalObject*> &obstacles, bool modifySpeed)
{
	// calcula posição final
	Vector2 finalPosition = *position + constantSpeed;

	float xVar = finalPosition.x - position->x;
	float yVar = finalPosition.y - position->y;

	// PARA MOVER PRECISA CHECAR COLISÃO

	for (int i = 0; i < obstacles.size(); i++)
	{
		if (!obstacles[i]->solid) continue;
		
		IPhysicalObject* obstacle = obstacles[i];
		FloatRectangle obstacleBounds = obstacle->getPhysicalBounds();
		
		if (constantSpeed.x == 0) // X NULO
		{
			if (constantSpeed.y == 0) // X NULO E Y NULO
				break;
			else if (constantSpeed.y > 0) // X NULO E Y POSITIVO
			{
				FloatRectangle moveRec(position->x, position->y, physicalSize->x, physicalSize->y + yVar);

				if (obstacleBounds.intersects(moveRec) && position->y + physicalSize->y <= obstacle->position->y)
				{
					// vai limitar Y
					constantSpeed.y = 0;
					position->y = obstacle->position->y - physicalSize->y;
					bottom = obstacle;
				}
			}
			else // X NULO E Y NEGATIVO
			{
				FloatRectangle moveRec(position->x, position->y + yVar, physicalSize->x, physicalSize->y - yVar);

				if (obstacleBounds.intersects(moveRec) && !obstacle->isPassable)
				{
					// vai limitar Y
					constantSpeed.y = 0;
					position->y = obstacle->position->y + obstacle->physicalSize->y;
					top = obstacle;
				}
			}
		}
		else if (constantSpeed.x > 0) // X POSITIVO
		{
			if (constantSpeed.y == 0) // X POSITIVO E Y NULO
			{
				FloatRectangle moveRec(position->x, position->y, physicalSize->x + xVar, physicalSize->y);

				if (obstacleBounds.intersects(moveRec) && !obstacle->isPassable)
				{
					// vai limitar X
					constantSpeed.x = 0;
					position->x = obstacle->position->x - physicalSize->x;
					right = obstacle;
				}
			}
			else if (constantSpeed.y > 0) // X POSITIVO E Y POSITIVO
			{
				FloatRectangle moveRec(position->x, position->y, physicalSize->x + xVar, physicalSize->y + yVar);

				if (obstacleBounds.intersects(moveRec))
				{
					if (obstacle->position->x >= position->x + physicalSize->x)
					{
						// possivel limitar X
						if (obstacle->position->y >= position->y + physicalSize->y)
						{
							// possivel limitar Y também, verificar qual limita
							float timeX = (obstacle->position->x - position->x + physicalSize->x) / constantSpeed.x;
							float timeY = (obstacle->position->y - position->y + physicalSize->y) / constantSpeed.y;

							if (timeX >= timeY && !obstacle->isPassable)
							{
								// vai limitar X
								constantSpeed.x = 0;
								position->x = obstacle->position->x - physicalSize->x;
								right = obstacle;
							}
							else if (position->y + physicalSize->y <= obstacle->position->y)
							{
								// vai limitar Y
								constantSpeed.y = 0;
								position->y = obstacle->position->y - physicalSize->y;
								bottom = obstacle;
							}
						}
						else if (!obstacle->isPassable)
						{
							// vai limitar X
							constantSpeed.x = 0;
							position->x = obstacle->position->x - physicalSize->x;
							right = obstacle;
						}
					}
					else if (position->y + physicalSize->y <= obstacle->position->y)
					{
						// vai limitar Y
						constantSpeed.y = 0;
						position->y = obstacle->position->y - physicalSize->y;
						bottom = obstacle;
					}
				}
			}
			else // X POSITIVO E Y NEGATIVO
			{
				FloatRectangle moveRec(position->x, position->y + yVar, physicalSize->x + xVar, physicalSize->y - yVar);

				if (obstacleBounds.intersects(moveRec) && !obstacle->isPassable)
				{
					if (obstacle->position->x >= position->x + physicalSize->x)
					{
						// possivel limitar X
						if (obstacle->position->y + obstacle->physicalSize->y <= position->y)
						{
							// possivel limitar Y também, verificar qual limita
							float timeX = (obstacle->position->x - position->x + physicalSize->x) / constantSpeed.x;
							float timeY = (obstacle->position->y + obstacle->physicalSize->y - position->y) / constantSpeed.y;

							if (timeX >= timeY)
							{
								// vai limitar X
								constantSpeed.x = 0;
								position->x = obstacle->position->x - physicalSize->x;
								right = obstacle;
							}
							else
							{
								// vai limitar Y
								constantSpeed.y = 0;
								position->y = obstacle->position->y + obstacle->physicalSize->y;
								top = obstacle;
							}
						}
						else if (!obstacle->isPassable)
						{
							// vai limitar X
							constantSpeed.x = 0;
							position->x = obstacle->position->x - physicalSize->x;
							right = obstacle;
						}
					}
					else
					{
						// vai limitar Y
						constantSpeed.y = 0;
						position->y = obstacle->position->y + obstacle->physicalSize->y;
						top = obstacle;
					}
				}
			}
		}
		else // X NEGATIVO
		{
			if (constantSpeed.y == 0) // X NEGATIVO E Y NULO
			{
				FloatRectangle moveRec(position->x + xVar, position->y, physicalSize->x - xVar, physicalSize->y);

				if (obstacleBounds.intersects(moveRec) && !obstacle->isPassable)
				{
					// vai limitar X
					constantSpeed.x = 0;
					position->x = obstacle->position->x + obstacle->physicalSize->x;
					left = obstacle;
				}
			}
			else if (constantSpeed.y > 0) // X NEGATIVO E Y POSITIVO
			{
				FloatRectangle moveRec(position->x + xVar, position->y, physicalSize->x - xVar, physicalSize->y + yVar);

				if (obstacleBounds.intersects(moveRec))
				{
					if (obstacle->position->x + obstacle->physicalSize->x <= position->x)
					{
						// possivel limitar X
						if (obstacle->position->y >= position->y + physicalSize->y)
						{
							// possivel limitar Y também, verificar qual limita
							float timeX = (obstacle->position->x + obstacle->physicalSize->x - position->x) / constantSpeed.x;
							float timeY = (obstacle->position->y - position->y + physicalSize->y) / constantSpeed.y;

							if (timeX >= timeY && !obstacle->isPassable)
							{
								// vai limitar X
								constantSpeed.x = 0;
								position->x = obstacle->position->x + obstacle->physicalSize->x;
								left = obstacle;
							}
							else if (position->y + physicalSize->y <= obstacle->position->y)
							{
								// vai limitar Y
								constantSpeed.y = 0;
								position->y = obstacle->position->y - physicalSize->y;
								bottom = obstacle;
							}
						}
						else if (!obstacle->isPassable)
						{
							// vai limitar X
							constantSpeed.x = 0;
							position->x = obstacle->position->x + obstacle->physicalSize->x;
							left = obstacle;
						}
					}
					else if (position->y + physicalSize->y <= obstacle->position->y)
					{
						// vai limitar Y
						constantSpeed.y = 0;
						position->y = obstacle->position->y - physicalSize->y;
						bottom = obstacle;
					}
				}
			}
			else // X NEGATIVO E Y NEGATIVO
			{
				FloatRectangle moveRec(position->x + xVar, position->y + yVar, physicalSize->x - xVar, physicalSize->y - yVar);

				if (obstacleBounds.intersects(moveRec) && !obstacle->isPassable)
				{
					if (obstacle->position->x + obstacle->physicalSize->x <= position->x)
					{
						// possivel limitar X
						if (obstacle->position->y + obstacle->physicalSize->y <= position->y)
						{
							// possivel limitar Y também, verificar qual limita
							float timeX = (obstacle->position->x + obstacle->physicalSize->x - position->x) / constantSpeed.x;
							float timeY = (obstacle->position->y + obstacle->physicalSize->y - position->y) / constantSpeed.y;

							if (timeX >= timeY)
							{
								// vai limitar X
								constantSpeed.x = 0;
								position->x = obstacle->position->x + obstacle->physicalSize->x;
								left = obstacle;
							}
							else
							{
								// vai limitar Y
								constantSpeed.y = 0;
								position->y = obstacle->position->y + obstacle->physicalSize->y;
								top = obstacle;
							}
						}
						else if (!obstacle->isPassable)
						{
							// vai limitar X
							constantSpeed.x = 0;
							position->x = obstacle->position->x + obstacle->physicalSize->x;
							left = obstacle;
						}
					}
					else
					{
						// vai limitar Y
						constantSpeed.y = 0;
						position->y = obstacle->position->y + obstacle->physicalSize->y;
						top = obstacle;
					}
				}
			}
		}
	}

	// nenhuma colisão, seta posição final
	Vector2 newPos(position->x + constantSpeed.x, position->y + constantSpeed.y);
	*position = newPos;

	if (modifySpeed)
		*speed = constantSpeed;

 	Vector2 zero(0, 0);
	*storedForce = zero;
}

AGL::Vector2 AGL::MovingObject::getAcceleration()
{
	return *acceleration;
}

AGL::Vector2 AGL::MovingObject::getSpeed()
{
	return *speed;
}

bool AGL::MovingObject::collidesOnTop()
{
	return top != NULL;
}

bool AGL::MovingObject::collidesOnRight()
{
	return right != NULL;
}

bool AGL::MovingObject::collidesOnBottom()
{
	return bottom != NULL;
}

bool AGL::MovingObject::collidesOnLeft()
{
	return left != NULL;
}

AGL::IPhysicalObject* AGL::MovingObject::getObjectOnTop()
{
	return top;
}

AGL::IPhysicalObject* AGL::MovingObject::getObjectOnRight()
{
	return right;
}

AGL::IPhysicalObject* AGL::MovingObject::getObjectOnBottom()
{
	return bottom;
}

AGL::IPhysicalObject* AGL::MovingObject::getObjectOnLeft()
{
	return left;
}

AGL::MovingObject::MovingObject() : AGL::IPhysicalObject()
{
	top = NULL;	
	right = NULL; 
	bottom = NULL; 
	left = NULL;
	path = NULL;
	storedForce = new Vector2(0, 0);
	speed = new Vector2(0, 0);
	acceleration = new Vector2(0, 0);	
}

AGL::MovingObject::MovingObject(AGL::Vector2 &position) : AGL::IPhysicalObject(position)
{
	top = NULL;	
	right = NULL; 
	bottom = NULL; 
	left = NULL;
	path = NULL;
	storedForce = new Vector2(0, 0);
	speed = new Vector2(0, 0);
	acceleration = new Vector2(0, 0);
}

AGL::MovingObject::MovingObject(AGL::Vector2 &position, AGL::IntVector2 &physicalSize) : AGL::IPhysicalObject(position, physicalSize)
{
	top = NULL;	
	right = NULL; 
	bottom = NULL; 
	left = NULL;
	path = NULL;
	storedForce = new Vector2(0, 0);
	speed = new Vector2(0, 0);
	acceleration = new Vector2(0, 0);
}

AGL::MovingObject::MovingObject(AGL::Vector2 &position, AGL::Image* image) : AGL::IPhysicalObject(image, position)
{
	top = NULL;	
	right = NULL; 
	bottom = NULL; 
	left = NULL;
	path = NULL;
	storedForce = new Vector2(0, 0);
	speed = new Vector2(0, 0);
	acceleration = new Vector2(0, 0);
}

AGL::MovingObject::MovingObject(Drawer* drawer, AGL::Vector2 &position, AGL::Image* image) : AGL::IPhysicalObject(drawer, image, position)
{
	top = NULL;	
	right = NULL; 
	bottom = NULL; 
	left = NULL;
	path = NULL;
	storedForce = new Vector2(0, 0);
	speed = new Vector2(0, 0);
	acceleration = new Vector2(0, 0);
}

void AGL::MovingObject::move(AGL::Vector2 &forces, vector<AGL::IPhysicalObject*> &obstacles)
{
	vector<AGL::Ramp*> ramps;
	move(forces, obstacles, ramps);
}

void AGL::MovingObject::move(AGL::Vector2 &forces, vector<AGL::IPhysicalObject*> &obstacles, vector<AGL::Ramp*> &ramps)
{
	forces += *storedForce;

	// Inicialmente já checa colisões existentes
	top = NULL;
	right = NULL;
	bottom = NULL;
	left = NULL;

	for (int i = 0; i < obstacles.size(); i++)
	{
		if (!obstacles[i]->solid) continue;

		IPhysicalObject* obstacle = obstacles[i];

		// acima
		if ((obstacle->position->y + obstacle->physicalSize->y == position->y) &&
			(position->x + physicalSize->x > obstacle->position->x && obstacle->position->x + obstacle->physicalSize->x > position->x) && 
			!obstacle->isPassable)
			top = obstacle;

		// direita
		if ((obstacle->position->x == position->x + physicalSize->x) &&
			(position->y + physicalSize->y > obstacle->position->y && obstacle->position->y + obstacle->physicalSize->y > position->y))
			right = obstacle;

		// abaixo
		if ((obstacle->position->y == position->y + physicalSize->y) &&
			(position->x + physicalSize->x > obstacle->position->x && obstacle->position->x + obstacle->physicalSize->x > position->x))
			bottom = obstacle;

		// esquerda
		if ((obstacle->position->x + obstacle->physicalSize->x == position->x) &&
			(position->y + physicalSize->y > obstacle->position->y && obstacle->position->y + obstacle->physicalSize->y > position->y))
			left = obstacle;
	}
	
	// abaixo (rampa)
	Vector2 feet(position->x + (float)physicalSize->x / 2, position->y + physicalSize->y);
	
	for (int i = 0; i < ramps.size(); i++)
	{
		Ramp* ramp = ramps[i];
		
		if (feet.x > ramp->position->x && feet.x < ramp->position->x + ramp->physicalSize->x && 
			feet.y > ramp->position->y && feet.y <= ramp->position->y + ramp->physicalSize->y) // tá dentro
		{
			float feetY = ramp->getY(feet.x);
			if (feet.y == feetY)
			{
				bottom = ramp;
				speed->y = 0;
				break;
			}
		}
	}

	// Caso haja colisões iniciais, não permite a existência de forças
	if (forces.x < 0 && collidesOnLeft())
		forces.x = 0;
	else if (forces.x > 0 && collidesOnRight())
		forces.x = 0;

	if (forces.y < 0 && collidesOnTop())
		forces.y = 0;
	else if (forces.y > 0 && collidesOnBottom())
		forces.y = 0;
		
	// Calcula aceleração
	acceleration->x = forces.x / mass;

	acceleration->y = (speed->y > PhysicalEnvironment::maxFallSpeed || collidesOnBottom() ? 
								0 : PhysicalEnvironment::gravity) + (forces.y / mass);

	// Calcula velocidade
	if ((acceleration->x > 0 && speed->x < 0 && acceleration->x > -speed->x) || (acceleration->x < 0 && speed->x > 0 && -acceleration->x > speed->x))
		speed->x = 0;
	else
		speed->x += acceleration->x;

	if ((acceleration->y > 0 && speed->y < 0 && acceleration->y > -speed->y) || (acceleration->y < 0 && speed->y > 0 && -acceleration->y > speed->y))
		speed->y = 0;
	else
		speed->y += acceleration->y;
		
	move(*speed, obstacles, true);

	Vector2 feet2(position->x + (float)physicalSize->x / 2, position->y + physicalSize->y);

	for (int i = 0; i < ramps.size(); i++)
	{
		Ramp* ramp = ramps[i];
		
		if (feet2.x > ramp->position->x && feet2.x < ramp->position->x + ramp->physicalSize->x &&
			feet2.y > ramp->position->y && feet2.y <= ramp->position->y + ramp->physicalSize->y) // tá dentro
		{
			float feetY = ramp->getY(feet2.x);
			
			if (feet2.y > feetY - PhysicalEnvironment::rampAdherence && speed->y >= 0)
			{
				if (ramp->isLeftToRight() && feet2.x >= ramp->position->x + ramp->physicalSize->x - speed->x - PhysicalEnvironment::rampAdjustment) 
					position->y = ramp->position->y - physicalSize->y;
				else if (!ramp->isLeftToRight() && feet2.x <= ramp->position->x - speed->x + PhysicalEnvironment::rampAdjustment) 
					position->y = ramp->position->y - physicalSize->y;
				else 
					position->y = feetY - physicalSize->y;
				
				float ratio = (float)ramp->physicalSize->y / (float)ramp->physicalSize->x;
				
				if (ratio > PhysicalEnvironment::rampSlipTangent) // quando a rampa é inclinada demais, o cara tende a escorregar
				{
					Vector2 ff(ratio * ratio * (ramp->isLeftToRight() ? -PhysicalEnvironment::rampSlipForce : PhysicalEnvironment::rampSlipForce), 0);
					storedForce->x += ff.x;
					storedForce->y += ff.y;					
				}
				
				break;
			}
		}
	}
}

void AGL::MovingObject::moveFixed(float rotation, float speed)
{
	float xVar = (float)(speed * cos(rotation));
	float yVar = (float)(speed * sin(rotation));
	position->x += xVar;
	position->y += yVar;
}

void AGL::MovingObject::moveFixed(float rotation, float speed, vector<AGL::IPhysicalObject*> &obstacles, vector<AGL::Ramp*> &ramps)
{
	float xVar = (float)(speed * cos(rotation));
	float yVar = (float)(speed * sin(rotation));
	
	Vector2 constSpeed(xVar, yVar);
	move(constSpeed, obstacles, false);
	
	Vector2 center(position->x + (float)physicalSize->x / 2, position->y + (float)physicalSize->y / 2);
	for (int i = 0; i < ramps.size(); i++)
	{
		Ramp* ramp = ramps[i];
		
		if (center.x > ramp->position->x && center.x < ramp->position->x + ramp->physicalSize->x &&
			center.y > ramp->position->y && center.y <= ramp->position->y + ramp->physicalSize->y) // tá dentro
		{
			if (center.y >= ramp->getY(center.x))
				bottom = ramp;
		}
	}
}

void AGL::MovingObject::moveTowards(AGL::Vector2 &aim, float absoluteSpeed)
{
	Vector2 zero(0, 0);
	if (*speed != zero) // já está em movimento
	{
		if ((speed->x < 0 && position->x + speed->x <= aim.x) || (speed->x >= 0 && position->x + speed->x >= aim.x))
			position->x = aim.x;
		else
			position->x = position->x + speed->x;

		if ((speed->y < 0 && position->y + speed->y <= aim.y) || (speed->y >= 0 && position->y + speed->y >= aim.y))
			position->y = aim.y;
		else
			position->y += speed->y;

		if (position->x == aim.x && position->y == aim.y)
			*speed = zero;
	}
	else // iniciou o movimento agora
	{
		float xD = aim.x - position->x;
		float yD = aim.y - position->y;
		double distance = sqrt(xD * xD + yD * yD);
		
		speed->x = xD / (float)(distance / absoluteSpeed);
		speed->y = yD / (float)(distance / absoluteSpeed);
	}
}

void AGL::MovingObject::patrol(AGL::Vector2 &aim, float absoluteSpeed)
{
	Vector2 zero(0, 0);
	if (*speed == zero)
	{
		if (path == NULL)
		{
			path = new vector<Vector2>;
			path->push_back(*position);
			path->push_back(aim);
			goingToPath = 0;
		}

		if (goingToPath == 0)
			goingToPath = 1;
		else
			goingToPath = 0;
	}
	
	moveTowards((*path)[goingToPath], absoluteSpeed);
}

void AGL::MovingObject::followClosedPath(vector<AGL::Vector2> &points, float absoluteSpeed)
{
	Vector2 zero(0, 0);
	if (*speed == zero)
	{
		if (path == NULL)
		{
			path = new vector<Vector2>;
			
			for(int i = 0; i < points.size(); i++)
				path->push_back(points[i]);
			
			goingToPath = 0;
		}

		if (goingToPath < path->size() - 1)
			goingToPath++;
		else
			goingToPath = 0;
	}

	moveTowards((*path)[goingToPath], absoluteSpeed);
}

void AGL::MovingObject::followOpenPath(vector<AGL::Vector2> &points, float absoluteSpeed)
{
	Vector2 zero(0, 0);
	if (*speed == zero)
	{
		if (path == NULL)
		{
			path = new vector<Vector2>;
			
			for(int i = 0; i < points.size(); i++)
				path->push_back(points[i]);
				
			goingToPath = 0;
		}

		if (reversePath)
		{
			if (goingToPath != 0)
				goingToPath--;
			else 
			{
				reversePath = false;
				goingToPath++;
			}
		}
		else 
		{
			if (goingToPath < path->size() - 1)
				goingToPath++;
			else 
			{
				reversePath = true;
				goingToPath--;
			}
		}
	}

	moveTowards((*path)[goingToPath], absoluteSpeed);
}

void AGL::MovingObject::stop()
{
	Vector2 zero(0, 0);
	*acceleration = zero;
	*speed = zero;
	
	delete path;
	path = NULL;
}

void AGL::MovingObject::moveElevatorTowards(AGL::Vector2 &aim, float absoluteSpeed, vector<AGL::MovingObject*> &sprites, vector<AGL::IPhysicalObject*> &obstacles)
{
	Vector2 zero(0, 0);
	if (*speed != zero) // já está em movimento
	{
		vector<MovingObject*> passengers;

		if (isElevator)
		{
			for (int i = 0; i < sprites.size(); i++)
			{
				MovingObject* passenger = sprites[i];
				
				if (position->x + physicalSize->x > passenger->position->x && passenger->position->x + passenger->physicalSize->x > position->x)
				{
					float feet = passenger->position->y + passenger->physicalSize->y;
										
					if (feet == position->y) // está exatamente sobre o elevador
						passengers.push_back(passenger);
					else if (position->y > feet && position->y + speed->y < feet) // o elevador vai pegá-lo com o movimento do elevador
					{
						passenger->position->y = position->y - passenger->physicalSize->y;
						passengers.push_back(passenger);
					}
				}
			}
		}

		if ((speed->x < 0 && position->x + speed->x <= aim.x) || (speed->x > 0 && position->x + speed->x >= aim.x))
		{
			float prevX = position->x;
			position->x = aim.x;
		
			if ((speed->y < 0 && position->y + speed->y <= aim.y) || (speed->y > 0 && position->y + speed->y >= aim.y))
			{
				float prevY = position->y;
				position->y = aim.y;				
				Vector2 cs(aim.x - prevX, aim.y - prevY);
				
				for (int i = 0; i < passengers.size(); i++)
					passengers[i]->move(cs, obstacles, false);
			}
			else if (speed->y != 0)
			{
				position->y += speed->y;
				Vector2 cs(aim.x - prevX, speed->y);

				for (int i = 0; i < passengers.size(); i++)
					passengers[i]->move(cs, obstacles, false);
			}
			else
			{
				Vector2 cs(aim.x - prevX, 0);
				
				for (int i = 0; i < passengers.size(); i++)
					passengers[i]->move(cs, obstacles, false);
			}
		}
		else if (speed->x != 0)
		{
			if ((speed->y < 0 && position->y + speed->y <= aim.y) || (speed->y > 0 && position->y + speed->y >= aim.y))
			{
				float prevY = position->y;
				position->y = aim.y;				
				Vector2 cs(speed->x, aim.y - prevY);
				
				for (int i = 0; i < passengers.size(); i++)
					passengers[i]->move(cs, obstacles, false);
			}
			else if (speed->y != 0)
			{
				position->y += speed->y;
				Vector2 cs(speed->x, speed->y);

				for (int i = 0; i < passengers.size(); i++)
					passengers[i]->move(cs, obstacles, false);
			}
			else
			{
				Vector2 cs(speed->x, 0);
			
				for (int i = 0; i < passengers.size(); i++)
					passengers[i]->move(cs, obstacles, false);
			}

			position->x += speed->x;
		}
		else
		{
			if ((speed->y < 0 && position->y + speed->y <= aim.y) || (speed->y > 0 && position->y + speed->y >= aim.y))
			{
				float prevY = position->y;
				position->y = aim.y;				
				Vector2 cs(0, aim.y - prevY);
				
				for (int i = 0; i < passengers.size(); i++)
					passengers[i]->move(cs, obstacles, false);
			}
			else if (speed->y != 0)
			{
				position->y += speed->y;
				Vector2 cs(0, speed->y);

				for (int i = 0; i < passengers.size(); i++)
					passengers[i]->move(cs, obstacles, false);
			}
		}

		if (position->x == aim.x && position->y == aim.y)
			*speed = zero;
	}
	else // iniciou o movimento agora
	{
		float xD = aim.x - position->x; 
		float yD = aim.y - position->y;
		double distance = sqrt(xD * xD + yD * yD);
		speed->x = (float)(xD / distance * absoluteSpeed);
		speed->y = (float)(yD / distance * absoluteSpeed);
	}
}

void AGL::MovingObject::patrolElevator(AGL::Vector2 &aim, float absoluteSpeed, vector<AGL::MovingObject*> &sprites, vector<AGL::IPhysicalObject*> &obstacles)
{
	Vector2 zero(0, 0);
	if (*speed == zero)
	{
		if (path == NULL)
		{
			path = new vector<Vector2>;
			path->push_back(*position);
			path->push_back(aim);
			goingToPath = 0;
		}

		if (goingToPath == 0)
			goingToPath = 1;
		else
			goingToPath = 0;
	}

	moveElevatorTowards((*path)[goingToPath], absoluteSpeed, sprites, obstacles);
}

void AGL::MovingObject::followElevatorClosedPath(vector<AGL::Vector2> &points, float absoluteSpeed, vector<AGL::MovingObject*> &sprites, vector<AGL::IPhysicalObject*> &obstacles)
{
	Vector2 zero(0, 0);
	if (*speed == zero)
	{
		if (path == NULL)
		{
			path = new vector<Vector2>;
			
			for(int i = 0; i < points.size(); i++)
				path->push_back(points[i]);
				
			goingToPath = 0;
		}

		if (goingToPath < path->size() - 1)
			goingToPath++;
		else
			goingToPath = 0;
	}

	moveElevatorTowards((*path)[goingToPath], absoluteSpeed, sprites, obstacles);
}

void AGL::MovingObject::followElevatorOpenPath(vector<AGL::Vector2> &points, float absoluteSpeed, vector<AGL::MovingObject*> &sprites, vector<AGL::IPhysicalObject*> &obstacles)
{
	Vector2 zero(0, 0);
	if (*speed == zero)
	{
		if (path == NULL)
		{
			path = new vector<Vector2>;
			
			for(int i = 0; i < points.size(); i++)
				path->push_back(points[i]);
				
			goingToPath = 0;
		}

		if (reversePath)
		{
			if (goingToPath != 0)
				goingToPath--;
			else
			{
				reversePath = false;
				goingToPath++;
			}
		}
		else
		{
			if (goingToPath < path->size() - 1)
				goingToPath++;
			else
			{
				reversePath = true;
				goingToPath--;
			}
		}
	}

	moveElevatorTowards((*path)[goingToPath], absoluteSpeed, sprites, obstacles);
}

