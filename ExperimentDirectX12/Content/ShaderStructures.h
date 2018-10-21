#pragma once

namespace ExperimentDirectX12
{
	// Constant buffer used to send MVP matrices to the vertex shader.
	struct ModelViewProjectionConstantBuffer
	{
		DirectX::XMFLOAT4X4 model;	// Where and how the model looks
		DirectX::XMFLOAT4X4 view;	// Where the camera is pointing
		DirectX::XMFLOAT4X4 projection;	// How the camera views the world
	};

	// Used to send per-vertex data to the vertex shader.
	struct VertexPositionColor
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 color;
	};
}