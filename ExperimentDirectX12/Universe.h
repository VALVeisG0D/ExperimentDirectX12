// Speed of light exists because the computer simulating our reality is not powerful enough to perform computation beyond that limit.
// Three places to change in Sample3DSceneRenderer.cpp and 2 in this file to change 
//	number of particles
#pragma once
constexpr auto DEFAULT_DIMENSION = 512;

class Universe
{
	int DEFAULT_NUMBER_OF_PARTICLES;
	int (*cellArray)[DEFAULT_DIMENSION][DEFAULT_DIMENSION];

	struct Particle
	{
		int xCoordinate;
		int xInertia;
		int xPositionChange;
		int yCoordinate;
		int yInertia;
		int yPositionChange;
		int zCoordinate;
		int zInertia;
		int zPositionChange;
	};

	Particle* particleList;

public:
	Universe(int numOfParticles);
	~Universe();

	void AddParticle(int, int, int);
	void RemoveParticle(int, int, int);
	void UpdateParticlePosition();
	float xFieldIndexToCoordinate(int);
	float yFieldIndexToCoordinate(int);
	float zFieldIndexToCoordinate(int);
	int coordinateToFieldIndex(int);
};

Universe::Universe(int numOfParticles)
{
	DEFAULT_NUMBER_OF_PARTICLES = numOfParticles;

	// Create cellArray array and particles
	cellArray = new int[DEFAULT_DIMENSION][DEFAULT_DIMENSION][DEFAULT_DIMENSION]();
	particleList = new Particle[DEFAULT_NUMBER_OF_PARTICLES]();

	// Create barrier along edge plane of cellArray so that particles don't
	// go out of bound
	// NOT OPTIMIZED YET

	//	Top and bottom plane
	for (int x = 0; x < DEFAULT_DIMENSION; ++x)
		for (int z = 0; z < DEFAULT_DIMENSION; ++z)
			cellArray[DEFAULT_DIMENSION - 1][x][z] = cellArray[0][x][z] = 1;

	//	Left and Right plane
	for (int y = 0; y < DEFAULT_DIMENSION; ++y)
		for (int z = 0; z < DEFAULT_DIMENSION; ++z)
			cellArray[y][0][z] = cellArray[y][DEFAULT_DIMENSION - 1][z] = 1;

	//	Front and Back plane
	for (int x = 0; x < DEFAULT_DIMENSION; ++x)
		for (int y = 0; y < DEFAULT_DIMENSION; ++y)
			cellArray[y][x][DEFAULT_DIMENSION - 1] = cellArray[y][x][0] = 1;

	// Loop to add particles in a linear, predictable fashion.
	for (int i = 0; i < DEFAULT_NUMBER_OF_PARTICLES; ++i)
		AddParticle
		(
			particleList[i].yCoordinate = coordinateToFieldIndex(0),
			particleList[i].xCoordinate = coordinateToFieldIndex(i + i),
			particleList[i].zCoordinate = coordinateToFieldIndex(0)
		);
}

Universe::~Universe()
{
	delete[] cellArray;
	delete[] particleList;
}

inline void Universe::AddParticle(int yCoordinate, int xCoordinate, int zCoordinate)
{
	//	Top plane
	cellArray[yCoordinate + 1][xCoordinate - 1][zCoordinate + 1] += 1;
	cellArray[yCoordinate + 1][xCoordinate][zCoordinate + 1] += 1;
	cellArray[yCoordinate + 1][xCoordinate + 1][zCoordinate + 1] += 1;

	cellArray[yCoordinate][xCoordinate - 1][zCoordinate + 1] += 1;
	cellArray[yCoordinate][xCoordinate][zCoordinate + 1] += 1;
	cellArray[yCoordinate][xCoordinate + 1][zCoordinate + 1] += 1;

	cellArray[yCoordinate - 1][xCoordinate - 1][zCoordinate + 1] += 1;
	cellArray[yCoordinate - 1][xCoordinate][zCoordinate + 1] += 1;
	cellArray[yCoordinate - 1][xCoordinate + 1][zCoordinate + 1] += 1;

	//	Middle plane
	cellArray[yCoordinate + 1][xCoordinate - 1][zCoordinate] += 1;
	cellArray[yCoordinate + 1][xCoordinate][zCoordinate] += 1;
	cellArray[yCoordinate + 1][xCoordinate + 1][zCoordinate] += 1;

	cellArray[yCoordinate][xCoordinate - 1][zCoordinate] += 1;
	cellArray[yCoordinate][xCoordinate][zCoordinate] += 1;	
	cellArray[yCoordinate][xCoordinate + 1][zCoordinate] += 1;

	cellArray[yCoordinate - 1][xCoordinate - 1][zCoordinate] += 1;
	cellArray[yCoordinate - 1][xCoordinate][zCoordinate] += 1;
	cellArray[yCoordinate - 1][xCoordinate + 1][zCoordinate] += 1;

	//	Bottom plane
	cellArray[yCoordinate + 1][xCoordinate - 1][zCoordinate - 1] += 1;
	cellArray[yCoordinate + 1][xCoordinate][zCoordinate - 1] += 1;
	cellArray[yCoordinate + 1][xCoordinate + 1][zCoordinate - 1] += 1;

	cellArray[yCoordinate][xCoordinate - 1][zCoordinate - 1] += 1;
	cellArray[yCoordinate][xCoordinate][zCoordinate - 1] += 1;
	cellArray[yCoordinate][xCoordinate + 1][zCoordinate - 1] += 1;

	cellArray[yCoordinate - 1][xCoordinate - 1][zCoordinate - 1] += 1;
	cellArray[yCoordinate - 1][xCoordinate][zCoordinate - 1] += 1;
	cellArray[yCoordinate - 1][xCoordinate + 1][zCoordinate - 1] += 1;
}

inline void Universe::RemoveParticle(int yCoordinate, int xCoordinate, int zCoordinate)
{
	//	Top plane
	cellArray[yCoordinate + 1][xCoordinate - 1][zCoordinate + 1] -= 1;
	cellArray[yCoordinate + 1][xCoordinate][zCoordinate + 1] -= 1;
	cellArray[yCoordinate + 1][xCoordinate + 1][zCoordinate + 1] -= 1;

	cellArray[yCoordinate][xCoordinate - 1][zCoordinate + 1] -= 1;
	cellArray[yCoordinate][xCoordinate][zCoordinate + 1] -= 1;
	cellArray[yCoordinate][xCoordinate + 1][zCoordinate + 1] -= 1;

	cellArray[yCoordinate - 1][xCoordinate - 1][zCoordinate + 1] -= 1;
	cellArray[yCoordinate - 1][xCoordinate][zCoordinate + 1] -= 1;
	cellArray[yCoordinate - 1][xCoordinate + 1][zCoordinate + 1] -= 1;

	//	Middle plane
	cellArray[yCoordinate + 1][xCoordinate - 1][zCoordinate] -= 1;
	cellArray[yCoordinate + 1][xCoordinate][zCoordinate] -= 1;
	cellArray[yCoordinate + 1][xCoordinate + 1][zCoordinate] -= 1;

	cellArray[yCoordinate][xCoordinate - 1][zCoordinate] -= 1;
	cellArray[yCoordinate][xCoordinate][zCoordinate] -= 1;
	cellArray[yCoordinate][xCoordinate + 1][zCoordinate] -= 1;

	cellArray[yCoordinate - 1][xCoordinate - 1][zCoordinate] -= 1;
	cellArray[yCoordinate - 1][xCoordinate][zCoordinate] -= 1;
	cellArray[yCoordinate - 1][xCoordinate + 1][zCoordinate] -= 1;

	//	Bottom plane
	cellArray[yCoordinate + 1][xCoordinate - 1][zCoordinate - 1] -= 1;
	cellArray[yCoordinate + 1][xCoordinate][zCoordinate - 1] -= 1;
	cellArray[yCoordinate + 1][xCoordinate + 1][zCoordinate - 1] -= 1;

	cellArray[yCoordinate][xCoordinate - 1][zCoordinate - 1] -= 1;
	cellArray[yCoordinate][xCoordinate][zCoordinate - 1] -= 1;
	cellArray[yCoordinate][xCoordinate + 1][zCoordinate - 1] -= 1;

	cellArray[yCoordinate - 1][xCoordinate - 1][zCoordinate - 1] -= 1;
	cellArray[yCoordinate - 1][xCoordinate][zCoordinate - 1] -= 1;
	cellArray[yCoordinate - 1][xCoordinate + 1][zCoordinate - 1] -= 1;
}

inline void Universe::UpdateParticlePosition()
{
	// Stores the difference in inertia between opposing points on the particle
	int inertiaDiff = 0;

	// 3 steps: calculate inertia, delete old position, add new position
	for (size_t i = 0; i < DEFAULT_NUMBER_OF_PARTICLES; ++i)
	{
		//	Calculating the inertias on the corners
		//	x-o-o
		//	o-o-o
		//	o-o-x
		inertiaDiff = 
			cellArray[particleList[i].yCoordinate + 1][particleList[i].xCoordinate - 1][particleList[i].zCoordinate - 1] - 
			cellArray[particleList[i].yCoordinate - 1][particleList[i].xCoordinate + 1][particleList[i].zCoordinate + 1];

		particleList[i].xInertia += inertiaDiff;
		particleList[i].yInertia -= inertiaDiff;
		particleList[i].zInertia += inertiaDiff;

		//	x-o-o
		//	o-o-o
		//	o-o-x
		inertiaDiff =
			cellArray[particleList[i].yCoordinate + 1][particleList[i].xCoordinate - 1][particleList[i].zCoordinate + 1] -
			cellArray[particleList[i].yCoordinate - 1][particleList[i].xCoordinate + 1][particleList[i].zCoordinate - 1];

		particleList[i].xInertia += inertiaDiff;
		particleList[i].yInertia -= inertiaDiff;
		particleList[i].zInertia -= inertiaDiff;

		//	o-o-x
		//	o-o-o
		//	x-o-o
		inertiaDiff =
			cellArray[particleList[i].yCoordinate - 1][particleList[i].xCoordinate - 1][particleList[i].zCoordinate + 1] -
			cellArray[particleList[i].yCoordinate + 1][particleList[i].xCoordinate + 1][particleList[i].zCoordinate - 1];

		particleList[i].xInertia += inertiaDiff;
		particleList[i].yInertia += inertiaDiff;
		particleList[i].zInertia -= inertiaDiff;

		//	o-o-x
		//	o-o-o
		//	x-o-o
		inertiaDiff =
			cellArray[particleList[i].yCoordinate - 1][particleList[i].xCoordinate - 1][particleList[i].zCoordinate - 1] -
			cellArray[particleList[i].yCoordinate + 1][particleList[i].xCoordinate + 1][particleList[i].zCoordinate + 1];

		particleList[i].xInertia += inertiaDiff;
		particleList[i].yInertia += inertiaDiff;
		particleList[i].zInertia += inertiaDiff;

		//	Calculating the inertia on the edge of the particle on the XZ plane
		//	o-o-o
		//	x-o-x
		//	o-o-o
		inertiaDiff =
			cellArray[particleList[i].yCoordinate][particleList[i].xCoordinate - 1][particleList[i].zCoordinate - 1] -
			cellArray[particleList[i].yCoordinate][particleList[i].xCoordinate + 1][particleList[i].zCoordinate + 1];

		particleList[i].xInertia += inertiaDiff;
		particleList[i].zInertia += inertiaDiff;

		//	o-o-o
		//	x-o-x
		//	o-o-o
		inertiaDiff =
			cellArray[particleList[i].yCoordinate][particleList[i].xCoordinate - 1][particleList[i].zCoordinate + 1] -
			cellArray[particleList[i].yCoordinate][particleList[i].xCoordinate + 1][particleList[i].zCoordinate - 1];

		particleList[i].xInertia += inertiaDiff;
		particleList[i].zInertia -= inertiaDiff;

		//	Calculating inertia on the edge of the particle on the YZ plane
		//	o-x-o
		//	o-o-o
		//	o-x-o
		inertiaDiff =
			cellArray[particleList[i].yCoordinate - 1][particleList[i].xCoordinate][particleList[i].zCoordinate + 1] -
			cellArray[particleList[i].yCoordinate + 1][particleList[i].xCoordinate][particleList[i].zCoordinate - 1];

		particleList[i].yInertia += inertiaDiff;
		particleList[i].zInertia -= inertiaDiff;

		//	o-x-o
		//	o-o-o
		//	o-x-o
		inertiaDiff =
			cellArray[particleList[i].yCoordinate - 1][particleList[i].xCoordinate][particleList[i].zCoordinate - 1] -
			cellArray[particleList[i].yCoordinate + 1][particleList[i].xCoordinate][particleList[i].zCoordinate + 1];

		particleList[i].yInertia += inertiaDiff;
		particleList[i].zInertia += inertiaDiff;

		//	Calculating the inertias on the edge of the particle on the XY plane
		//	x-o-o
		//	o-o-o
		//	o-o-x
		inertiaDiff =
			cellArray[particleList[i].yCoordinate + 1][particleList[i].xCoordinate - 1][particleList[i].zCoordinate] -
			cellArray[particleList[i].yCoordinate - 1][particleList[i].xCoordinate + 1][particleList[i].zCoordinate];

		particleList[i].xInertia += inertiaDiff;
		particleList[i].yInertia -= inertiaDiff;

		//	o-o-x
		//	o-o-o
		//	x-o-o
		inertiaDiff =
			cellArray[particleList[i].yCoordinate - 1][particleList[i].xCoordinate - 1][particleList[i].zCoordinate] -
			cellArray[particleList[i].yCoordinate + 1][particleList[i].xCoordinate + 1][particleList[i].zCoordinate];

		particleList[i].xInertia += inertiaDiff;
		particleList[i].yInertia += inertiaDiff;	

		//	Calculating the center x-inertia
		//	o-o-o
		//	x-o-x
		//	o-o-o
		particleList[i].xInertia +=
			cellArray[particleList[i].yCoordinate][particleList[i].xCoordinate - 1][particleList[i].zCoordinate] - 
			cellArray[particleList[i].yCoordinate][particleList[i].xCoordinate + 1][particleList[i].zCoordinate];
		
		//	Calculating the center y-inertia
		//	o-x-o
		//	o-o-o
		//	o-x-o
		particleList[i].yInertia += 
			cellArray[particleList[i].yCoordinate - 1][particleList[i].xCoordinate][particleList[i].zCoordinate] - 
			cellArray[particleList[i].yCoordinate + 1][particleList[i].xCoordinate][particleList[i].zCoordinate];

		//	Calculating the center z-inertia
		//	o-o-o
		//	o-x-o
		//	o-o-o
		particleList[i].zInertia +=
			cellArray[particleList[i].yCoordinate][particleList[i].xCoordinate][particleList[i].zCoordinate - 1] -
			cellArray[particleList[i].yCoordinate][particleList[i].xCoordinate][particleList[i].zCoordinate + 1];

		//	Clamp the inertia between -9 and 9
		//	(9 & ((x < 9) - 1)) <- Clamp to 9 units of inertia if x is more than 9
		//	+ (x & (((x > 8) || (x < -9)) - 1)) <- inertia will be between -9 and 9
		//	- (9 & ((x > -10) - 1)); <- Clamp to -9 units of inertia if x is less than -9
		particleList[i].xInertia = (9 & ((particleList[i].xInertia < 9) - 1)) 
			+ (particleList[i].xInertia & (((particleList[i].xInertia > 8) || (particleList[i].xInertia < -9)) - 1)) 
			- (9 & ((particleList[i].xInertia > -10) - 1));
		particleList[i].yInertia = (9 & ((particleList[i].yInertia < 9) - 1))
			+ (particleList[i].yInertia & (((particleList[i].yInertia > 8) || (particleList[i].yInertia < -9)) - 1))
			- (9 & ((particleList[i].yInertia > -10) - 1));
		particleList[i].zInertia = (9 & ((particleList[i].zInertia < 9) - 1))
			+ (particleList[i].zInertia & (((particleList[i].zInertia > 8) || (particleList[i].zInertia < -9)) - 1))
			- (9 & ((particleList[i].zInertia > -10) - 1));

		//	Calculating the magnitude of the change in position due to inertia
		//	Will be used to determine if particle moves by 1 unit
		particleList[i].xPositionChange += particleList[i].xInertia;
		particleList[i].yPositionChange += particleList[i].yInertia;
		particleList[i].zPositionChange += particleList[i].zInertia;
	}

	int negativePart = 0;
	int positivePart = 0;

	// Move the particle by removing from its old position and placing it at the new one
	// What if they are at the same position? Then try not to put particles in the same position
	for (size_t i = 0; i < DEFAULT_NUMBER_OF_PARTICLES; ++i)
	{
		RemoveParticle(particleList[i].yCoordinate, particleList[i].xCoordinate, particleList[i].zCoordinate);

		//	Logic for moving the particle by 1 unit only if the magnitude of the change in position
		//	is large enough
		//	If positivePart is 1, move in positive direction by 1 unit
		//	If negativePart is 1, move in negative direction by 1 unit
		//	Coordinate will be incremented by 1 or decremented by -1 if movement threshold is exceeded
		//		(thereby moving the particle)
		//	Reset positionChange to below movement threshold if threshold is exceeded
		//	DEPRECATED: REMEMBER! Bit shifting is different for 32 bit numbers vs 64 bit numbers due to alignment issues

		positivePart = particleList[i].xPositionChange > 8;
		negativePart = particleList[i].xPositionChange < -8;
		particleList[i].xCoordinate += positivePart - negativePart;
		particleList[i].xPositionChange -=
			-(negativePart + positivePart) & particleList[i].xPositionChange;

		positivePart = particleList[i].yPositionChange > 8;
		negativePart = particleList[i].yPositionChange < -8;
		particleList[i].yCoordinate += positivePart - negativePart;
		particleList[i].yPositionChange -=
			-(negativePart + positivePart) & particleList[i].yPositionChange;

		positivePart = particleList[i].zPositionChange > 8;
		negativePart = particleList[i].zPositionChange < -8;
		particleList[i].zCoordinate += positivePart - negativePart;
		particleList[i].zPositionChange -=
			-(negativePart + positivePart) & particleList[i].zPositionChange;

		AddParticle(particleList[i].yCoordinate, particleList[i].xCoordinate, particleList[i].zCoordinate);
	}
}

//	Convert from index to coordinate
inline float Universe::xFieldIndexToCoordinate(int particleListNumber)
{
	return (particleList[particleListNumber].xCoordinate - ((float)DEFAULT_DIMENSION / 2.0f)) * 0.01f;
}

inline float Universe::yFieldIndexToCoordinate(int particleListNumber)
{
	return (particleList[particleListNumber].yCoordinate - ((float)DEFAULT_DIMENSION / 2.0f)) * 0.01f;
}

inline float Universe::zFieldIndexToCoordinate(int particleListNumber)
{
	return (particleList[particleListNumber].zCoordinate - ((float)DEFAULT_DIMENSION / 2.0f)) * 0.01f;
}

//	Convert from coordinate to index
inline int Universe::coordinateToFieldIndex(int coordinate)
{
	return coordinate + (DEFAULT_DIMENSION / 2);
}
