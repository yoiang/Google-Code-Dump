#ifndef __PARTICLE_SOURCE__
#define __PARTICLE_SOURCE__

#include <windows.h>
#include <GL\GL.h>
#include <GL\glu.h>
#include <gl\glaux.h>
#include <stdlib.h>

#include "Point.h"
#include "Model.h"
#include "LinkedList.h"

class ParticleSource ;

class Spawner
{
public:
	virtual void Spawn(int iNumSpawn, ParticleSource *pSource) = 0 ; 
} ;

class Particle	// particle class
{
public:
	Point ptPreviousLocation,	// previous location
		  ptLocation,			// current location
		  ptVelocity ;			// velocity

	double dLifeIncrimenter ;	// life incrimenter
	double dLife ;				// current life

	Point ptColorIncrimenter ;	// color incrimenter
	Point ptColor ;				// current color

	Particle() ;
	~Particle() ;
} ;

class ParticleSource
{
public:
	bool bRespawn,	// respawn dead particles
		 bLines,	// connect particles
		 bTexture,	// apply texture to particles
		 bWind,		// apply wind acceleration
		 bGravity,	// apply gravitational acceleration
		 bFade,		// fade particle based on life (1-0 life = 1-0 alpha)
		 bWrongAcceleration ;

	// particle texture
	GLuint iTextureName ;	
	AUX_RGBImageRec *pTextureImage ;

	Spawner *pSpawner ;

	Point ptInitialLocation,	// initial particle location
		  ptLocationDeviation ;	// initial particle location deviation

	Point ptInitialVelocity,	// initial particle velocity
		  ptVelocityDeviation ;	// initial particle velocity deviation

	Point ptWindAcceleration ;	// wind acceleration
	Point ptGravityAcceleration ;	// gravitational acceleration

	Point ptInitialColor,		// initial particle color 
		  ptColorDeviation ;	// initial particle color deviation
	Point ptColorIncrimenter ;	// particle color incrimenter

	double dInitialLife,	// initial particle life
		   dLifeDeviation ;	// initial particle life deviation
	double dLifeIncrimenter ;	// particle life incrimenter

	Point ptScale ;	// particle scale

	LinkedList<Particle> Particles ;	// all particles

private:
	void CheckCollision(Particle *pCheck, LinkedList<Model> *pModels) ; // check collision of particle with models, handle accordingly
	void DisplayParticleTextured(Particle *pParticle, Point ptCameraLocation) ;	// display particle textured
	bool MoveParticle(Particle *pParticle, float fTime, LinkedList<Model> *pCollisionModel) ; // update position of the particle and check for collisions

public:
	ParticleSource() ;
	~ParticleSource() ;

	void SetSpawner(Spawner *pSetSpawner) ;	// set spawner class
	void SpawnParticles(int iNumSpawn) ;	// spawn specified number of particles
	void SetTexture(const char *szFilename) ;		// set texture to apply to particles
	void DisplayParticles(Point ptCameraLocation) ;	// display all particles to face the camera
	void MoveParticles(float fTime, LinkedList<Model> *pCollisionModel) ; // update positions of all particles and check for collisions
	void MoveDisplayParticles(float fTime, LinkedList<Model> *pCollisionModel, Point ptCameraLocation) ; // update positions and display for all particles
} ;

#endif