// Speed of light exists because the computer simulating our reality is not powerful enough to perform computation beyond that limit.
#pragma once
constexpr auto DEFAULT_DIMENSION = 256;
constexpr auto DEFAULT_NUMBER_OF_PARTICLES = 3;

class Field
{
	int (*field)[DEFAULT_DIMENSION];

	struct Particle
	{
		int xCoordinate;
		int xInertia;
		int yCoordinate;
		int yInertia;
	};

	Particle* particleList;

public:
	Field();
	~Field();

	void AddParticle(int, int);
	void RemoveParticle(int, int);
	void UpdateParticlePosition();
	float xFieldIndexToCoordinate(int);
	float yFieldIndexToCoordinate(int);
	size_t coordinateToFieldIndex(int);
};

Field::Field()
{
	// Create field array and particles
	field = new int[DEFAULT_DIMENSION][DEFAULT_DIMENSION]();
	particleList = new Particle[DEFAULT_NUMBER_OF_PARTICLES]();

	// Create barrier along edge of field so that particles don't
	// go out of bound

	//	Top and bottom edge
	for (int x = 0; x < DEFAULT_DIMENSION; ++x)
		field[0][x] = field[DEFAULT_DIMENSION - 1][x] = 1;

	//	Left and right edge
	for (int y = 1; y < DEFAULT_DIMENSION - 1; ++y)
		field[y][0] = field[y][DEFAULT_DIMENSION - 1] = 1;
	
	// Add particles
	AddParticle(particleList[0].yCoordinate = coordinateToFieldIndex(0), particleList[0].xCoordinate = coordinateToFieldIndex(-2));
	AddParticle(particleList[1].yCoordinate = coordinateToFieldIndex(0), particleList[1].xCoordinate = coordinateToFieldIndex(0));
	AddParticle(particleList[2].yCoordinate = coordinateToFieldIndex(0), particleList[2].xCoordinate = coordinateToFieldIndex(2));
}

Field::~Field()
{
	delete[] field;
	delete[] particleList;
}

inline void Field::AddParticle(int yCoordinate, int xCoordinate)
{
	//convert coordinate value to index value
	//what the hell value to give to that field coordinate
	field[yCoordinate + 1][xCoordinate - 1] += 1;
	field[yCoordinate + 1][xCoordinate] += 1;
	field[yCoordinate + 1][xCoordinate + 1] += 1;

	field[yCoordinate][xCoordinate - 1] += 1;
	field[yCoordinate][xCoordinate] += 64;
	field[yCoordinate][xCoordinate + 1] += 1;

	field[yCoordinate - 1][xCoordinate - 1] += 1;
	field[yCoordinate - 1][xCoordinate] += 1;
	field[yCoordinate - 1][xCoordinate + 1] += 1;
}

inline void Field::RemoveParticle(int yCoordinate, int xCoordinate)
{
	field[yCoordinate + 1][xCoordinate - 1] -= 1;
	field[yCoordinate + 1][xCoordinate] -= 1;
	field[yCoordinate + 1][xCoordinate + 1] -= 1;

	field[yCoordinate][xCoordinate - 1] -= 1;
	field[yCoordinate][xCoordinate] -= 64;
	field[yCoordinate][xCoordinate + 1] -= 1;

	field[yCoordinate - 1][xCoordinate - 1] -= 1;
	field[yCoordinate - 1][xCoordinate] -= 1;
	field[yCoordinate - 1][xCoordinate + 1] -= 1;
}

inline void Field::UpdateParticlePosition()
{
	// 3 steps: calculate inertia, delete old position, add new position
	for (size_t i = 0; i < DEFAULT_NUMBER_OF_PARTICLES; ++i)
	{
		//inertia calculations becomes more complicated for 2 dimensionals
		// require 4 lines of calculations

		particleList[i].xInertia += field[particleList[i].xCoordinate - 1] - field[particleList[i].xCoordinate + 1];
	}

	// Move the particle by removing from its old position and placing it at the new one
	// What if they are at the same position? Then try not to put particles in the same position
	for (size_t i = 0; i < DEFAULT_NUMBER_OF_PARTICLES; ++i)
	{
		RemoveParticle(particleList[i].yCoordinate, particleList[i].xCoordinate);
		AddParticle(particleList[i].yCoordinate += particleList[i].yInertia, particleList[i].xCoordinate += particleList[i].xInertia);
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

//	Convert from coordinate to index
inline size_t Field::coordinateToFieldIndex(int coordinate)
{
	return size_t(coordinate) + (DEFAULT_DIMENSION / 2);
}
