// Speed of light exists because the computer simulating our reality is not powerful enough to perform computation beyond that limit.
#pragma once
constexpr auto DEFAULT_DIMENSION = 256;
constexpr auto DEFAULT_NUMBER_OF_PARTICLES = 6;	//	Three places to change in Sample3DSceneRenderer.cpp and 2 in this file to change 
												//		number of particles

class Field
{
	int (*field)[DEFAULT_DIMENSION][DEFAULT_DIMENSION];

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
	Field();
	~Field();

	void AddParticle(int, int, int);
	void RemoveParticle(int, int, int);
	void UpdateParticlePosition();
	float xFieldIndexToCoordinate(int);
	float yFieldIndexToCoordinate(int);
	float zFieldIndexToCoordinate(int);
	size_t coordinateToFieldIndex(int);
};

Field::Field()
{
	// Create field array and particles
	field = new int[DEFAULT_DIMENSION][DEFAULT_DIMENSION][DEFAULT_DIMENSION]();
	particleList = new Particle[DEFAULT_NUMBER_OF_PARTICLES]();

	// Create barrier along edge plane of field so that particles don't
	// go out of bound

	//	Top and bottom plane
	for (int x = 0; x < DEFAULT_DIMENSION; ++x)
		for (int z = 0; z < DEFAULT_DIMENSION; ++z)
			field[DEFAULT_DIMENSION - 1][x][z] = field[0][x][z] = 1;

	//	Left and Right plane
	for (int y = 0; y < DEFAULT_DIMENSION; ++y)
		for (int z = 0; z < DEFAULT_DIMENSION; ++z)
			field[y][0][z] = field[y][DEFAULT_DIMENSION - 1][z] = 1;

	//	Front and Back plane
	for (int x = 0; x < DEFAULT_DIMENSION; ++x)
		for (int y = 0; y < DEFAULT_DIMENSION; ++y)
			field[y][x][DEFAULT_DIMENSION - 1] = field[y][x][0] = 1;

	//for (int x = 0; x < DEFAULT_DIMENSION; ++x)
	//	field[0][x] = field[DEFAULT_DIMENSION - 1][x] = 1;

	//for (int y = 1; y < DEFAULT_DIMENSION - 1; ++y)
	//	field[y][0] = field[y][DEFAULT_DIMENSION - 1] = 1;
	
	// Add particles
	AddParticle(particleList[0].yCoordinate = coordinateToFieldIndex(0), 
		particleList[0].xCoordinate = coordinateToFieldIndex(-2),
		particleList[0].zCoordinate = coordinateToFieldIndex(0));
	AddParticle(particleList[1].yCoordinate = coordinateToFieldIndex(0), 
		particleList[1].xCoordinate = coordinateToFieldIndex(0),
		particleList[1].zCoordinate = coordinateToFieldIndex(0));
	AddParticle(particleList[2].yCoordinate = coordinateToFieldIndex(0), 
		particleList[2].xCoordinate = coordinateToFieldIndex(2),
		particleList[2].zCoordinate = coordinateToFieldIndex(0));
	AddParticle(particleList[3].yCoordinate = coordinateToFieldIndex(2),
		particleList[3].xCoordinate = coordinateToFieldIndex(-2),
		particleList[3].zCoordinate = coordinateToFieldIndex(0));
	AddParticle(particleList[4].yCoordinate = coordinateToFieldIndex(2),
		particleList[4].xCoordinate = coordinateToFieldIndex(0),
		particleList[4].zCoordinate = coordinateToFieldIndex(0));
	AddParticle(particleList[5].yCoordinate = coordinateToFieldIndex(2),
		particleList[5].xCoordinate = coordinateToFieldIndex(2),
		particleList[5].zCoordinate = coordinateToFieldIndex(0));
}

Field::~Field()
{
	delete[] field;
	delete[] particleList;
}

inline void Field::AddParticle(int yCoordinate, int xCoordinate, int zCoordinate)
{
	//	Top plane
	field[yCoordinate + 1][xCoordinate - 1][zCoordinate + 1] += 1;
	field[yCoordinate + 1][xCoordinate][zCoordinate + 1] += 1;
	field[yCoordinate + 1][xCoordinate + 1][zCoordinate + 1] += 1;

	field[yCoordinate][xCoordinate - 1][zCoordinate + 1] += 1;
	field[yCoordinate][xCoordinate][zCoordinate + 1] += 1;
	field[yCoordinate][xCoordinate + 1][zCoordinate + 1] += 1;

	field[yCoordinate - 1][xCoordinate - 1][zCoordinate + 1] += 1;
	field[yCoordinate - 1][xCoordinate][zCoordinate + 1] += 1;
	field[yCoordinate - 1][xCoordinate + 1][zCoordinate + 1] += 1;

	//	Middle plane
	field[yCoordinate + 1][xCoordinate - 1][zCoordinate] += 1;
	field[yCoordinate + 1][xCoordinate][zCoordinate] += 1;
	field[yCoordinate + 1][xCoordinate + 1][zCoordinate] += 1;

	field[yCoordinate][xCoordinate - 1][zCoordinate] += 1;
	field[yCoordinate][xCoordinate][zCoordinate] += 1;	
	field[yCoordinate][xCoordinate + 1][zCoordinate] += 1;

	field[yCoordinate - 1][xCoordinate - 1][zCoordinate] += 1;
	field[yCoordinate - 1][xCoordinate][zCoordinate] += 1;
	field[yCoordinate - 1][xCoordinate + 1][zCoordinate] += 1;

	//	Bottom plane
	field[yCoordinate + 1][xCoordinate - 1][zCoordinate - 1] += 1;
	field[yCoordinate + 1][xCoordinate][zCoordinate - 1] += 1;
	field[yCoordinate + 1][xCoordinate + 1][zCoordinate - 1] += 1;

	field[yCoordinate][xCoordinate - 1][zCoordinate - 1] += 1;
	field[yCoordinate][xCoordinate][zCoordinate - 1] += 1;
	field[yCoordinate][xCoordinate + 1][zCoordinate - 1] += 1;

	field[yCoordinate - 1][xCoordinate - 1][zCoordinate - 1] += 1;
	field[yCoordinate - 1][xCoordinate][zCoordinate - 1] += 1;
	field[yCoordinate - 1][xCoordinate + 1][zCoordinate - 1] += 1;
}

inline void Field::RemoveParticle(int yCoordinate, int xCoordinate, int zCoordinate)
{
	//	Top plane
	field[yCoordinate + 1][xCoordinate - 1][zCoordinate + 1] -= 1;
	field[yCoordinate + 1][xCoordinate][zCoordinate + 1] -= 1;
	field[yCoordinate + 1][xCoordinate + 1][zCoordinate + 1] -= 1;

	field[yCoordinate][xCoordinate - 1][zCoordinate + 1] -= 1;
	field[yCoordinate][xCoordinate][zCoordinate + 1] -= 1;
	field[yCoordinate][xCoordinate + 1][zCoordinate + 1] -= 1;

	field[yCoordinate - 1][xCoordinate - 1][zCoordinate + 1] -= 1;
	field[yCoordinate - 1][xCoordinate][zCoordinate + 1] -= 1;
	field[yCoordinate - 1][xCoordinate + 1][zCoordinate + 1] -= 1;

	//	Middle plane
	field[yCoordinate + 1][xCoordinate - 1][zCoordinate] -= 1;
	field[yCoordinate + 1][xCoordinate][zCoordinate] -= 1;
	field[yCoordinate + 1][xCoordinate + 1][zCoordinate] -= 1;

	field[yCoordinate][xCoordinate - 1][zCoordinate] -= 1;
	field[yCoordinate][xCoordinate][zCoordinate] -= 1;
	field[yCoordinate][xCoordinate + 1][zCoordinate] -= 1;

	field[yCoordinate - 1][xCoordinate - 1][zCoordinate] -= 1;
	field[yCoordinate - 1][xCoordinate][zCoordinate] -= 1;
	field[yCoordinate - 1][xCoordinate + 1][zCoordinate] -= 1;

	//	Bottom plane
	field[yCoordinate + 1][xCoordinate - 1][zCoordinate - 1] -= 1;
	field[yCoordinate + 1][xCoordinate][zCoordinate - 1] -= 1;
	field[yCoordinate + 1][xCoordinate + 1][zCoordinate - 1] -= 1;

	field[yCoordinate][xCoordinate - 1][zCoordinate - 1] -= 1;
	field[yCoordinate][xCoordinate][zCoordinate - 1] -= 1;
	field[yCoordinate][xCoordinate + 1][zCoordinate - 1] -= 1;

	field[yCoordinate - 1][xCoordinate - 1][zCoordinate - 1] -= 1;
	field[yCoordinate - 1][xCoordinate][zCoordinate - 1] -= 1;
	field[yCoordinate - 1][xCoordinate + 1][zCoordinate - 1] -= 1;
}

inline void Field::UpdateParticlePosition()
{
	// 3 steps: calculate inertia, delete old position, add new position
	for (size_t i = 0; i < DEFAULT_NUMBER_OF_PARTICLES; ++i)
	{
		//	Calculating the inertias on the corners
		//	x-o-o
		//	o-o-o
		//	o-o-x
		int tempInertiaDiag = 
			field[particleList[i].yCoordinate + 1][particleList[i].xCoordinate - 1][particleList[i].zCoordinate - 1] - 
			field[particleList[i].yCoordinate - 1][particleList[i].xCoordinate + 1][particleList[i].zCoordinate + 1];

		particleList[i].xInertia += tempInertiaDiag;
		particleList[i].yInertia -= tempInertiaDiag;
		particleList[i].zInertia += tempInertiaDiag;

		//	x-o-o
		//	o-o-o
		//	o-o-x
		tempInertiaDiag =
			field[particleList[i].yCoordinate + 1][particleList[i].xCoordinate - 1][particleList[i].zCoordinate + 1] -
			field[particleList[i].yCoordinate - 1][particleList[i].xCoordinate + 1][particleList[i].zCoordinate - 1];

		particleList[i].xInertia += tempInertiaDiag;
		particleList[i].yInertia -= tempInertiaDiag;
		particleList[i].zInertia -= tempInertiaDiag;

		//	o-o-x
		//	o-o-o
		//	x-o-o
		tempInertiaDiag =
			field[particleList[i].yCoordinate - 1][particleList[i].xCoordinate - 1][particleList[i].zCoordinate + 1] -
			field[particleList[i].yCoordinate + 1][particleList[i].xCoordinate + 1][particleList[i].zCoordinate - 1];

		particleList[i].xInertia += tempInertiaDiag;
		particleList[i].yInertia += tempInertiaDiag;
		particleList[i].zInertia -= tempInertiaDiag;

		//	o-o-x
		//	o-o-o
		//	x-o-o
		tempInertiaDiag =
			field[particleList[i].yCoordinate - 1][particleList[i].xCoordinate - 1][particleList[i].zCoordinate - 1] -
			field[particleList[i].yCoordinate + 1][particleList[i].xCoordinate + 1][particleList[i].zCoordinate + 1];

		particleList[i].xInertia += tempInertiaDiag;
		particleList[i].yInertia += tempInertiaDiag;
		particleList[i].zInertia += tempInertiaDiag;

		//	Calculating the inertia on the edge of the particle on the XZ plane
		//	o-o-o
		//	x-o-x
		//	o-o-o
		tempInertiaDiag =
			field[particleList[i].yCoordinate][particleList[i].xCoordinate - 1][particleList[i].zCoordinate - 1] -
			field[particleList[i].yCoordinate][particleList[i].xCoordinate + 1][particleList[i].zCoordinate + 1];

		particleList[i].xInertia += tempInertiaDiag;
		particleList[i].zInertia += tempInertiaDiag;

		//	o-o-o
		//	x-o-x
		//	o-o-o
		tempInertiaDiag =
			field[particleList[i].yCoordinate][particleList[i].xCoordinate - 1][particleList[i].zCoordinate + 1] -
			field[particleList[i].yCoordinate][particleList[i].xCoordinate + 1][particleList[i].zCoordinate - 1];

		particleList[i].xInertia += tempInertiaDiag;
		particleList[i].zInertia -= tempInertiaDiag;

		//	Calculating inertia on the edge of the particle on the YZ plane
		//	o-x-o
		//	o-o-o
		//	o-x-o
		tempInertiaDiag =
			field[particleList[i].yCoordinate - 1][particleList[i].xCoordinate][particleList[i].zCoordinate + 1] -
			field[particleList[i].yCoordinate + 1][particleList[i].xCoordinate][particleList[i].zCoordinate - 1];

		particleList[i].yInertia += tempInertiaDiag;
		particleList[i].zInertia -= tempInertiaDiag;

		//	o-x-o
		//	o-o-o
		//	o-x-o
		tempInertiaDiag =
			field[particleList[i].yCoordinate - 1][particleList[i].xCoordinate][particleList[i].zCoordinate - 1] -
			field[particleList[i].yCoordinate + 1][particleList[i].xCoordinate][particleList[i].zCoordinate + 1];

		particleList[i].yInertia += tempInertiaDiag;
		particleList[i].zInertia += tempInertiaDiag;

		//	Calculating the inertias on the edge of the particle on the XY plane
		//	x-o-o
		//	o-o-o
		//	o-o-x
		tempInertiaDiag =
			field[particleList[i].yCoordinate + 1][particleList[i].xCoordinate - 1][particleList[i].zCoordinate] -
			field[particleList[i].yCoordinate - 1][particleList[i].xCoordinate + 1][particleList[i].zCoordinate];

		particleList[i].xInertia += tempInertiaDiag;
		particleList[i].yInertia -= tempInertiaDiag;

		//	o-o-x
		//	o-o-o
		//	x-o-o
		tempInertiaDiag =
			field[particleList[i].yCoordinate - 1][particleList[i].xCoordinate - 1][particleList[i].zCoordinate] -
			field[particleList[i].yCoordinate + 1][particleList[i].xCoordinate + 1][particleList[i].zCoordinate];

		particleList[i].xInertia += tempInertiaDiag;
		particleList[i].yInertia += tempInertiaDiag;	

		//	Calculating the center x-inertia
		//	o-o-o
		//	x-o-x
		//	o-o-o
		particleList[i].xInertia +=
			field[particleList[i].yCoordinate][particleList[i].xCoordinate - 1][particleList[i].zCoordinate] - 
			field[particleList[i].yCoordinate][particleList[i].xCoordinate + 1][particleList[i].zCoordinate];
		
		//	Calculating the center y-inertia
		//	o-x-o
		//	o-o-o
		//	o-x-o
		particleList[i].yInertia += 
			field[particleList[i].yCoordinate - 1][particleList[i].xCoordinate][particleList[i].zCoordinate] - 
			field[particleList[i].yCoordinate + 1][particleList[i].xCoordinate][particleList[i].zCoordinate];

		//	Calculating the center z-inertia
		//	o-o-o
		//	o-x-o
		//	o-o-o
		particleList[i].zInertia +=
			field[particleList[i].yCoordinate][particleList[i].xCoordinate][particleList[i].zCoordinate - 1] -
			field[particleList[i].yCoordinate][particleList[i].xCoordinate][particleList[i].zCoordinate + 1];

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

		//offset = particleList[i].xPositionChange + 6;
		//positivePart = (0xfe00 >> offset) & 1;		
		//negativePart = (0x000f >> offset) & 1;		
		//particleList[i].xCoordinate += positivePart - negativePart;
		//particleList[i].xPositionChange += 
		//	(negativePart + positivePart) * -particleList[i].xPositionChange;	

		AddParticle(particleList[i].yCoordinate, particleList[i].xCoordinate, particleList[i].zCoordinate);
	}
}

//	Convert from index to coordinate
inline float Field::xFieldIndexToCoordinate(int particleListNumber)
{
	return (particleList[particleListNumber].xCoordinate - ((float)DEFAULT_DIMENSION / 2.0f)) * 0.01f;
}

inline float Field::yFieldIndexToCoordinate(int particleListNumber)
{
	return (particleList[particleListNumber].yCoordinate - ((float)DEFAULT_DIMENSION / 2.0f)) * 0.01f;
}

inline float Field::zFieldIndexToCoordinate(int particleListNumber)
{
	return (particleList[particleListNumber].zCoordinate - ((float)DEFAULT_DIMENSION / 2.0f)) * 0.01f;
}

//	Convert from coordinate to index
inline size_t Field::coordinateToFieldIndex(int coordinate)
{
	return size_t(coordinate) + (DEFAULT_DIMENSION / 2);
}
