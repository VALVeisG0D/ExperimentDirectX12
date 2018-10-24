// Speed of light exists because the computer simulating our reality is not powerful enough to perform computation beyond that limit.
#pragma once
class Field
{
	int (*field);
	const size_t DEFAULT_DIMENSION = 512;

	struct Particle
	{
		int xCoordinate;
		int xInertia;
	};

	const size_t DEFAULT_NUMBER_OF_PARTICLES = 3;
	Particle* particleList;

public:
	Field();
	~Field();

	void AddParticle(int);
	void RemoveParticle(int);
	void UpdateParticlePosition();
	float fieldIndexToCoordinate(int);
	size_t coordinateToFieldIndex(int);
};

Field::Field()
{
	// Create field array and particles
	field = new int[DEFAULT_DIMENSION]();
	particleList = new Particle[DEFAULT_NUMBER_OF_PARTICLES]();

	// Create barrier along edge of field
	// Have to be big enough so particle cannot overcome
	// the barrier
	field[0] = 4096;
	field[DEFAULT_DIMENSION - 1] = 4096;

	
	// Add particles
	AddParticle(particleList[0].xCoordinate = coordinateToFieldIndex(-2));
	AddParticle(particleList[1].xCoordinate = coordinateToFieldIndex(0));
	AddParticle(particleList[2].xCoordinate = coordinateToFieldIndex(2));
}

Field::~Field()
{
	delete[] field;
	delete[] particleList;
}

inline void Field::AddParticle(int coordinate)
{
	//convert coordinate value to index value
	//what the hell value to give to that field coordinate
	field[coordinate - 1] += 1;
	field[coordinate] += 64;
	field[coordinate + 1] += 1;
}

inline void Field::RemoveParticle(int coordinate)
{
	field[coordinate - 1] -= 1;
	field[coordinate] -= 64;
	field[coordinate + 1] -= 1;
}

inline void Field::UpdateParticlePosition()
{
	// 3 steps: calculate inertia, delete old position, add new position
	for (size_t i = 0; i < DEFAULT_NUMBER_OF_PARTICLES; ++i)
		particleList[i].xInertia += field[particleList[i].xCoordinate - 1] - field[particleList[i].xCoordinate + 1];

	// Apply the new particle coordinate to the field
	// What if they are at the same position? Then try not to put particles in the same position
	for (size_t i = 0; i < DEFAULT_NUMBER_OF_PARTICLES; ++i)
	{
		RemoveParticle(particleList[i].xCoordinate);
		AddParticle(particleList[i].xCoordinate += particleList[i].xInertia);
	}
}

//	Convert from index to coordinate
inline float Field::fieldIndexToCoordinate(int particleListNumber)
{
	return (particleList[particleListNumber].xCoordinate - ((float)DEFAULT_DIMENSION / 2.0f)) * 0.01f;
}

//	Convert from coordinate to index
inline size_t Field::coordinateToFieldIndex(int coordinate)
{
	return size_t(coordinate) + (DEFAULT_DIMENSION / 2);
}


