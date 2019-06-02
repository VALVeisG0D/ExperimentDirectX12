#define FIELD_DIMENSION 512

struct Field
{
	int field[FIELD_DIMENSION][FIELD_DIMENSION][FIELD_DIMENSION];
};

struct Particle
{
	int3 Coordinate;
	int3 Inertia;
	int3 PositionChange;
};

struct Particlef
{
	float Position;
	float Velocity;
};

RWStructuredBuffer<Particlef> gInputOutput;

[numthreads(256, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
	gInputOutput[DTid.x].Position += 3.0f;
	gInputOutput[DTid.x].Velocity += 7.0f;
}