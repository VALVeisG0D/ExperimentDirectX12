struct Particle
{
	float Position;
	float Velocity;
};

RWStructuredBuffer<Particle> gInput : register(u0);
RWStructuredBuffer<Particle> gOutput : register(u1);

[numthreads(256, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
	gOutput[DTid.x].Position = gInput[DTid.x].Position + 1.0f;
	gOutput[DTid.x].Velocity = gInput[DTid.x].Velocity + 2.0f;
}