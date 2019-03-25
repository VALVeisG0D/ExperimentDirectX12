#pragma once
#include <DirectXMath.h>

using namespace Windows::UI::Core;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Devices::Input;

constexpr auto ROTATION_GAIN = 0.004f;		// Sensitivity adjustment for the look controller
constexpr auto MOVEMENT_GAIN = 0.1f;		// Sensitivity adjustment for the move controller

ref class MoveLookController
{
	// Properties of the controller object
	DirectX::XMFLOAT3 m_position;		// The position of the controller
	float m_pitch, m_yaw;				// Orientation euler angles in radians

	// Properties of the move controller
	bool m_moveInUse;					// Specifies whether the move control is in use
	unsigned m_movePointerID;			// ID of pointer in this control
	DirectX::XMFLOAT2 m_moveFirstDown;	// Point where initial contact occured
	DirectX::XMFLOAT2 m_movePointerPosition;	// Point where the move pointer is currently located
	DirectX::XMFLOAT3 m_moveCommand;	// The net command from the move control

	// Properties of the move control
	bool m_lookInUse;					// Specifies whether the look control is in use
	unsigned m_lookPointerID;			// ID of the pointer in this control
	DirectX::XMFLOAT2 m_lookLastPoint;	// Last point (from last frame)
	DirectX::XMFLOAT2 m_lookLastDelta;	// For smoothing

	bool m_forward, m_back;				// States for movement
	bool m_left, m_right;
	bool m_up, m_down;

public:
	// Methods to get input from the UI pointer
	void OnPointerPressed(CoreWindow^ sender, PointerEventArgs^ args);
	void OnPointerMoved(CoreWindow^ sender, PointerEventArgs^ args);
	void OnPointerReleased(CoreWindow^ sender, PointerEventArgs^ args);
	void OnKeyDown(CoreWindow^ sender, KeyEventArgs^ args);
	void OnKeyUp(CoreWindow^ sender, KeyEventArgs^ args);
	void OnMouseMoved(MouseDevice^ mouseDevice, MouseEventArgs^ args);

	// Set up the Controls that this controller supports
	void Initialize(CoreWindow^ window);
	void Update(CoreWindow^ window);

internal:
	// Accessor to set position of controller
	void SetPosition(DirectX::XMFLOAT3 pos);

	// Accessor to set orientation of controller
	void SetOrientation(float pitch, float yaw);

	// Returns the position of the controller object
	DirectX::XMFLOAT3 get_Position();

	// Returns the point which the controller is facing
	DirectX::XMFLOAT3 get_LookPoint();
};