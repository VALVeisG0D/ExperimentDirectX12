cbuffer ParticleInteractionConstantBuffer : register(b0)
{
	float f = 0.0f;
};

[numthreads(1, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
	//f = f + 1.0f;
}