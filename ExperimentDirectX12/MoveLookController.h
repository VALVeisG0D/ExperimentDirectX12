//Use XMVECTOR for global variables and XMFLOAT2, XMFLOAT3, XMFLOAT4 for class members
//	Difference between these two are that XMVECTOR needs to be 16-byte aligned for local
//	and global variables. XMVECTORS also use SIMD hardware, so more performant.

#pragma once
#include <DirectXMath.h>

using namespace DirectX;
using namespace Windows::UI::Core;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Devices::Input;

constexpr auto ROTATION_GAIN = 0.004f;		// Sensitivity adjustment for the look controller
constexpr auto MOVEMENT_GAIN = 0.1f;		// Sensitivity adjustment for the move controller

ref class MoveLookController
{
	// Properties of the controller object
	XMFLOAT3 m_position;		// The position of the controller
	float m_pitch, m_yaw;				// Orientation euler angles in radians

	// Properties of the move controller
	bool m_moveInUse;					// Specifies whether the move control is in use
	unsigned m_movePointerID;			// ID of pointer in this control
	XMFLOAT2 m_moveFirstDown;	// Point where initial contact occured
	XMFLOAT2 m_movePointerPosition;	// Point where the move pointer is currently located
	XMFLOAT3 m_moveCommand;	// The net command from the move control

	// Properties of the move control
	bool m_lookInUse;					// Specifies whether the look control is in use
	unsigned m_lookPointerID;			// ID of the pointer in this control
	XMFLOAT2 m_lookLastPoint;	// Last point (from last frame)

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
	void SetPosition(XMFLOAT3 pos);

	// Accessor to set orientation of controller
	void SetOrientation(float pitch, float yaw);

	// Returns the position of the controller object
	XMFLOAT3 get_Position();

	// Returns the point which the controller is facing
	XMFLOAT3 get_LookPoint();
};