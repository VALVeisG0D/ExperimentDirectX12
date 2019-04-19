struct Particle
{
	float Position;
	float Velocity;
};

ConsumeStructuredBuffer<Particle> gInput;
AppendStructuredBuffer<Particle> gOutput;

[numthreads(256, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
	Particle p = gInput.Consume();

	p.Position += p.Position;
	p.Velocity += 2.0f;

	gOutput.Append(p);
}