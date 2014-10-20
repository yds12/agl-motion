#include <stdlib.h>
#include "agl/game.h"
#include "agl/drawer.h"

// ------------ Includes here ---------------
#include <iostream>
#include "agl/vector2.h"
#include "agl/intvector2.h"
#include "agl/gameobject.h"
#include "agl/support.h"
#include "agl/color.h"
#include "agl/motion/movingobject.h"
#include "agl/motion/physicalenvironment.h"
#include "agl/motion/iphysicalobject.h"
// ------------------------------------------

// ------------ Defines here ----------------
// ------------------------------------------

//const string fontPath = "/usr/share/fonts/dejavu/DejaVuSans.ttf";
const string contentPath = "/home/USER/aleva/misc/";
//const string fontPath = "/usr/share/fonts/truetype/freefont/FreeMono.ttf";
//const string contentPath = "/home/USER/test/";

AGL::Game* game = NULL;
AGL::Drawer* drawer = NULL;

// ------------ Declare variables here ------
AGL::Keyboard* kb = NULL;
AGL::Mouse* ms = NULL;
//AGL::Font* font = NULL;
AGL::GameObject* go = NULL;
//AGL::Image* moverImage = NULL;
AGL::Image* blockImage = NULL;

AGL::MovingObject* mover = NULL;
AGL::MovingObject* elevator = NULL;
vector<AGL::IPhysicalObject*>* obstacles = NULL;
vector<AGL::Ramp*>* ramps = NULL;
// ------------------------------------------


void initialize()
{
	game = new AGL::Game;
	drawer = new AGL::Drawer;

	game->showMouse(true);

	kb = new AGL::Keyboard(false, false, true, true, false, false);
	ms = new AGL::Mouse;
	
	obstacles = new vector<AGL::IPhysicalObject*>;
	ramps = new vector<AGL::Ramp*>;
	
	AGL::PhysicalEnvironment::setDefaults();
	AGL::PhysicalEnvironment::rampSlipTangent = 0.3f;
	AGL::PhysicalEnvironment::rampSlipForce = 5;
}

void loadContent()
{
	//font = new AGL::Font(AGL::Format::stringToChar(&(fontPath + "")), 60);
	//moverImage = new AGL::Image(AGL::Format::stringToChar(&(contentPath + "thief.png")));
	blockImage = new AGL::Image(AGL_AGR, AGL::Format::stringToChar(&(contentPath + "block.agr")));
	
	AGL::Vector2 p1(0, 400);
	obstacles->push_back(new AGL::IPhysicalObject(drawer, blockImage, p1));	
	AGL::Vector2 p2(25, 400);
	obstacles->push_back(new AGL::IPhysicalObject(drawer, blockImage, p2));	
	AGL::Vector2 p3(50, 400);
	obstacles->push_back(new AGL::IPhysicalObject(drawer, blockImage, p3));	
	AGL::Vector2 p4(75, 400);
	obstacles->push_back(new AGL::IPhysicalObject(drawer, blockImage, p4));	
	AGL::Vector2 p5(100, 400);
	obstacles->push_back(new AGL::IPhysicalObject(drawer, blockImage, p5));
	AGL::Vector2 p11(125, 400);
	obstacles->push_back(new AGL::IPhysicalObject(drawer, blockImage, p11));
	AGL::Vector2 p12(150, 400);
	obstacles->push_back(new AGL::IPhysicalObject(drawer, blockImage, p12));
	AGL::Vector2 p13(175, 400);
	obstacles->push_back(new AGL::IPhysicalObject(drawer, blockImage, p13));
	AGL::Vector2 p14(200, 400);
	obstacles->push_back(new AGL::IPhysicalObject(drawer, blockImage, p14));		
	AGL::Vector2 p16(75, 383);
	//obstacles->push_back(new AGL::IPhysicalObject(drawer, blockImage, p16));
	
	AGL::Vector2 p7(125, 300);
	obstacles->push_back(new AGL::IPhysicalObject(drawer, blockImage, p7));
	AGL::Vector2 p8(150, 350);
	obstacles->push_back(new AGL::IPhysicalObject(drawer, blockImage, p8));
	AGL::Vector2 p9(175, 350);
	obstacles->push_back(new AGL::IPhysicalObject(drawer, blockImage, p9));
	
	AGL::Vector2 p20(230, 520);
	obstacles->push_back(new AGL::IPhysicalObject(drawer, blockImage, p20));
	AGL::Vector2 p17(255, 520);
	obstacles->push_back(new AGL::IPhysicalObject(drawer, blockImage, p17));
	AGL::Vector2 p18(280, 520);
	obstacles->push_back(new AGL::IPhysicalObject(drawer, blockImage, p18));
	AGL::Vector2 p19(305, 520);
	obstacles->push_back(new AGL::IPhysicalObject(drawer, blockImage, p19));
		
	AGL::Vector2 p15(100, 383);
	ramps->push_back(new AGL::Ramp(drawer, p15, blockImage, true));
	
	AGL::Vector2 p6(100, 100);
	mover = new AGL::MovingObject(drawer, p6, blockImage);
	
	AGL::Vector2 p10(230, 470);
	elevator = new AGL::MovingObject(drawer, p10, blockImage);
	elevator->isPassable = true;
	elevator->isElevator = true;
	
	obstacles->push_back(elevator);
}

void update()
{
	game->update(kb, ms, true);
	
	AGL::Vector2 forces(0, 0);
	
	if(kb->isKeyDown(kb->getIndex(AGL::KEY_ENTER))) cout << "teste ###########" << endl << endl << endl;
	if(kb->isKeyDown(kb->getIndex(AGL::KEY_RIGHT))) forces.x += 3;
	if(kb->isKeyDown(kb->getIndex(AGL::KEY_LEFT))) forces.x += -3;
	if(kb->isKeyDown(kb->getIndex(AGL::KEY_UP)) && mover->collidesOnBottom()) forces.y += -50;
	
	if(mover->getSpeed().x > 0 && !kb->isKeyDown(kb->getIndex(AGL::KEY_RIGHT))) forces.x += -1;
	if(mover->getSpeed().x < 0 && !kb->isKeyDown(kb->getIndex(AGL::KEY_LEFT))) forces.x += 1;
	
	mover->move(forces, *obstacles, *ramps);
	
	AGL::Vector2 aim(260, 300);
	
	vector<AGL::MovingObject*> sprites;
	sprites.push_back(mover);

	elevator->patrolElevator(aim, 1, sprites, *obstacles);
}

void draw()
{
	drawer->clearScreen(AGL_COLOR_WHITE);
	
	for(int i = 0; i < obstacles->size(); i++)
		(*obstacles)[i]->draw();
	
	for(int i = 0; i < ramps->size(); i++)
		(*ramps)[i]->draw();
	
	mover->draw();
	elevator->draw();
	
	drawer->updateScreen();
}

void unloadContent()
{
	game->end();
}

/// Main method, initializes the program
int main(int argc, char *argv[])
{
	initialize();
	loadContent();

	game->runFixedFps(update, draw, 60);

	unloadContent();

	return 0;
}
