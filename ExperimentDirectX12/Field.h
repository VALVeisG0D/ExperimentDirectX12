// Speed of light exists because the computer simulating our reality is not powerful enough to perform computation beyond that limit.
#pragma once
class Field
{
	int (*field);
	const size_t DEFAULT_DIMENSION = 512;

	struct Particle
	{
		int xCoordinate;
		int xPreviousCoordinate;
	};

	const size_t DEFAULT_NUMBER_OF_PARTICLES = 3;
	Particle* particleList;

public:
	Field();
	~Field();

	void AddParticle(int);
	void RemoveParticle(int);
	void UpdateParticlePosition();
	float GetParticlePosition(int);
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
	// 3 steps: calculate, move, delete
	// Calculate difference between front and back (the sign (-/+) indicates the direction)
	// Use result to calculate new coordinate of particle
	for (size_t i = 0; i < DEFAULT_NUMBER_OF_PARTICLES; ++i)
	{
		particleList[i].xPreviousCoordinate = particleList[i].xCoordinate;
		particleList[i].xCoordinate += field[particleList[i].xCoordinate - 1] - field[particleList[i].xCoordinate + 1];
	}
	//std::cout << particleList[0].xCoordinate << " " << particleList[1].xCoordinate << " " << particleList[2].xCoordinate << std::endl;

	// Apply the new particle coordinate to the field
	// What if they are at the same position?
	for (size_t i = 0; i < DEFAULT_NUMBER_OF_PARTICLES; ++i)
	{
		RemoveParticle(particleList[i].xPreviousCoordinate);
		AddParticle(particleList[i].xCoordinate);
	}
}

inline float Field::GetParticlePosition(int particleListNumber)
{
	return (particleList[particleListNumber].xCoordinate - ((float)DEFAULT_DIMENSION / 2.0f)) * 0.01f;
}

inline size_t Field::coordinateToFieldIndex(int coordinate)
{
	return size_t(coordinate) + (DEFAULT_DIMENSION / 2);
}


