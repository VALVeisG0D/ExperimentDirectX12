// Speed of light exists because the computer simulating our reality is not powerful enough to perform computation beyond that limit.
#pragma once
constexpr auto DEFAULT_DIMENSION = 256;
constexpr auto DEFAULT_NUMBER_OF_PARTICLES = 6;

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
		//	Top plane
		//	Calculating the inertias on tbe diagonals
		//	x-o-o
		//	o-o-o
		//	o-o-x
		int tempInertiaDiag = 
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

		//	Middle plane
		//	Calculating the inertias on the diagonals
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

		//	Calculating the inertia directly above, below, and to the side of the particle
		//	o-o-o
		//	x-o-x
		//	o-o-o
		particleList[i].xInertia +=
			field[particleList[i].yCoordinate][particleList[i].xCoordinate - 1][particleList[i].zCoordinate] - 
			field[particleList[i].yCoordinate][particleList[i].xCoordinate + 1][particleList[i].zCoordinate];
		
		//	o-x-o
		//	o-o-o
		//	o-x-o
		particleList[i].yInertia += 
			field[particleList[i].yCoordinate - 1][particleList[i].xCoordinate][particleList[i].zCoordinate] - 
			field[particleList[i].yCoordinate + 1][particleList[i].xCoordinate][particleList[i].zCoordinate];

		//	Bottom plane
		//	Calculating the inertias on the diagonals
		//	x-o-o
		//	o-o-o
		//	o-o-x


		//	Clamp the inertia between -3 and 3
		particleList[i].xInertia = (3 * ((0xffe000 >> (particleList[i].xInertia + 10)) & 1))
			+ (particleList[i].xInertia * ((0x01f80 >> (particleList[i].xInertia + 10)) & 1))
			+ (-3 * ((0x0007f >> (particleList[i].xInertia + 10)) & 1));
		particleList[i].yInertia = (3 * ((0xffe000 >> (particleList[i].yInertia + 10)) & 1))
			+ (particleList[i].yInertia * ((0x01f80 >> (particleList[i].yInertia + 10)) & 1))
			+ (-3 * ((0x0007f >> (particleList[i].yInertia + 10)) & 1));

		//	Calculating the magnitude of the change in position due to inertia
		//	Will be used to determine if particle moves by 1 unit
		particleList[i].xPositionChange += particleList[i].xInertia;
		particleList[i].yPositionChange += particleList[i].yInertia;
	}

	int negativePart = 0;
	int positivePart = 0;
	int offset = 0;

	// Move the particle by removing from its old position and placing it at the new one
	// What if they are at the same position? Then try not to put particles in the same position
	for (size_t i = 0; i < DEFAULT_NUMBER_OF_PARTICLES; ++i)
	{
		RemoveParticle(particleList[i].yCoordinate, particleList[i].xCoordinate, particleList[i].zCoordinate);

		//	Logic for moving the particle by 1 unit only if the magnitude of the change in position
		//	is large enough
		//	Range of the offset is from 3 to 9 to prevent having a negative offset for bit shifting
		//	1111 1110 0000 0000 & 0000 0000 0000 0001 = 1 if offset is 9 or more (move in positive
		//		direction by 1 unit
		//	0000 0000 0000 1111 & 0000 0000 0000 0001 = 1 if offset is 3 or less (move in negative
		//		direction by 1 unit
		offset = particleList[i].xPositionChange + 6;
		positivePart = (0xfe00 >> offset) & 1;		
		negativePart = (0x000f >> offset) & 1;		
		particleList[i].xCoordinate += positivePart - negativePart;
		particleList[i].xPositionChange += 
			(negativePart + positivePart) * -particleList[i].xPositionChange;

		offset = particleList[i].yPositionChange + 6;
		positivePart = (0xfe00 >> offset) & 1;
		negativePart = (0x000f >> offset) & 1;
		particleList[i].yCoordinate += positivePart - negativePart;
		particleList[i].yPositionChange += 
			(negativePart + positivePart) * -particleList[i].yPositionChange;

		offset = particleList[i].zPositionChange + 6;
		positivePart = (0xfe00 >> offset) & 1;
		negativePart = (0x000f >> offset) & 1;
		particleList[i].zCoordinate += positivePart - negativePart;
		particleList[i].zPositionChange +=
			(negativePart + positivePart) * -particleList[i].zPositionChange;

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
