#pragma once

#include "..\Common\DeviceResources.h"
#include "MoveLookController.h"
#include "ShaderStructures.h"
#include "..\Common\StepTimer.h"

namespace ExperimentDirectX12
{
	// This sample renderer instantiates a basic rendering pipeline.
	class Sample3DSceneRenderer
	{
	public:
		Sample3DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		~Sample3DSceneRenderer();
		void CreateDeviceDependentResources();
		void CreateWindowSizeDependentResources();
		void Compute(Platform::String^& resultData);
		void Update(DX::StepTimer const& timer, MoveLookController^ moveLookController);
		void UpdateVertexBuffer(UINT dataBufferSize, VertexPositionColor *data, Microsoft::WRL::ComPtr<ID3D12Resource> &dataBufferUpload);
		bool Render();	

	private:
		// Constant buffers must be 256-byte aligned.
		static const UINT c_alignedConstantBufferSize = (sizeof(ModelViewProjectionConstantBuffer) + 255) & ~255;

		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// Direct3D resources for cube geometry.
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>	m_commandList;
		Microsoft::WRL::ComPtr<ID3D12RootSignature>			m_rootSignature;
		Microsoft::WRL::ComPtr<ID3D12RootSignature>			m_computeRootSignature;
		Microsoft::WRL::ComPtr<ID3D12PipelineState>			m_pipelineState;
		Microsoft::WRL::ComPtr<ID3D12PipelineState>			m_computePipelineState;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>		m_cbvHeap;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>		m_uavHeap;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_vertexBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_instanceBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_instanceBufferUpload;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_constantBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_uavUploadBufferA;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_uavInputBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_readBackBuffer;
		ModelViewProjectionConstantBuffer					m_constantBufferData;
		UINT8*												m_mappedConstantBuffer;
		UINT												m_cbvDescriptorSize;
		D3D12_RECT											m_scissorRect;
		std::vector<byte>									m_vertexShader;
		std::vector<byte>									m_pixelShader;
		std::vector<byte>									m_computeShader;
		D3D12_VERTEX_BUFFER_VIEW							m_vertexBufferView;
		D3D12_VERTEX_BUFFER_VIEW							m_instanceBufferView;

		// Variables used with the rendering loop.
		bool	m_loadingComplete;	
	};
}

