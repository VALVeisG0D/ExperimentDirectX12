#pragma once

#include "Common\StepTimer.h"
#include "Common\DeviceResources.h"
#include "MoveLookController.h"
#include "Content\Sample3DSceneRenderer.h"

// Renders Direct3D content on the screen.
namespace ExperimentDirectX12
{
	class ExperimentDirectX12Main
	{
	public:
		ExperimentDirectX12Main();
		void CreateRenderers(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void Update();
		bool Render();

		void OnWindowSizeChanged();
		void OnSuspending();
		void OnResuming();
		void OnDeviceRemoved();

	private:
		// TODO: Replace with your own content renderers.
		std::unique_ptr<Sample3DSceneRenderer> m_sceneRenderer;

		// Controller for moving and rotating the camera
		std::unique_ptr<MoveLookController> m_moveLookController;

		// Rendering loop timer.
		DX::StepTimer m_timer;
	};
}