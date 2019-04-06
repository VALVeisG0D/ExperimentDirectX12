struct Particle
{
	float Position;
	float Velocity;
};

ConsumeStructuredBuffer<Particle> gInput;
AppendStructuredBuffer<Particle> gOutput;

[numthreads(32, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
	Particle p = gInput.Consume();

	p.Position += 1.0f;
	p.Velocity += 2.0f;

	gOutput.Append(p);
}