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

RWStructuredBuffer<Particlef> gInput;
RWStructuredBuffer<Particlef> gOutput;

[numthreads(256, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
	gOutput[DTid.x].Position = gInput[DTid.x].Position + 1.0f;
	gOutput[DTid.x].Velocity = gInput[DTid.x].Velocity + 2.0f;
}