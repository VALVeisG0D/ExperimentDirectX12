#include "pch.h"
#include "MoveLookController.h"	// Putting definitions in a different .cpp file allows it to be compiled and linked SEPERATELY,
								// thus preventing any conflicts due to violation of the ONE DEFINITION RULE

void MoveLookController::OnPointerPressed(CoreWindow ^ sender, PointerEventArgs ^ args)
{
	// Get the current pointer position.
	unsigned pointerID = args->CurrentPoint->PointerId;
	DirectX::XMFLOAT2 position = DirectX::XMFLOAT2(args->CurrentPoint->Position.X, args->CurrentPoint->Position.Y);

	auto device = args->CurrentPoint->PointerDevice;
	auto deviceType = device->PointerDeviceType;

	if (deviceType == PointerDeviceType::Mouse);
		// Action, Jump, or Fire;

	// Check if this pointer is in the move control.
	// Change the values to percentages of the preferred screen resolution
	// You can set the x value to the <preferred resolution> * <percentage width>
	// for example, (position.x < (screenResolution.x * 0.15)).

	if ((position.x < 300 && position.y > 380) && (deviceType != PointerDeviceType::Mouse))
	{
		if (!m_moveInUse) // if no pointer is in this control yet
		{
			// Process a DPad touch down event.
			m_moveFirstDown = position;		// Save the location of the initial contact.
			m_movePointerPosition = position;
			m_movePointerID = pointerID;	// Store the id of the pointer using this control.
			m_moveInUse = true;
		}
	}
	else // This pointer must be in the look control
	{
		if (!m_lookInUse) // If no pointer is in this control yet...
		{
			m_lookLastPoint = position;		// save the point for later move
			m_lookPointerID = args->CurrentPoint->PointerId;	// store the id of pointer using this control
			m_lookLastDelta.x = m_lookLastDelta.y = 0;			// these are for smoothing
			m_lookInUse = true;
		}
	}
}

void MoveLookController::OnPointerMoved(CoreWindow ^ sender, PointerEventArgs ^ args)
{
	unsigned pointerID = args->CurrentPoint->PointerId;
	DirectX::XMFLOAT2 position = DirectX::XMFLOAT2(args->CurrentPoint->Position.X, args->CurrentPoint->Position.Y);

	// Decide which control this pointer is operating.
	if (pointerID == m_movePointerID)		// This is the move pointer.
		// Move control
		m_movePointerPosition = position;	// Save the current position.
	else if (pointerID == m_lookPointerID)	// This is the look pointer.
	{
		// Look control
		DirectX::XMFLOAT2 pointerDelta;
		pointerDelta.x = position.x - m_lookLastPoint.x;	// How far did pointer move
		pointerDelta.y = position.y - m_lookLastPoint.y;

		DirectX::XMFLOAT2 rotationDelta;
		rotationDelta.x = pointerDelta.x * ROTATION_GAIN;	// Scale for control sensitivity.
		rotationDelta.y = pointerDelta.y * ROTATION_GAIN;

		m_lookLastPoint = position;							// Save for the next time through.

		m_pitch -= rotationDelta.y;			// Update our orientation based on the command.
		m_yaw -= rotationDelta.x;			// Mouse y increases down, but pitch increases up.
											// Yaw is defined as CCW around the y-axis.

		// Limit the pitch to straight up or straight down.
		m_pitch = (float)__max(-DirectX::XM_PI / 2.0f, m_pitch);
		m_pitch = (float)__min(+DirectX::XM_PI / 2.0f, m_pitch);
	}
}

void MoveLookController::OnPointerReleased(CoreWindow ^ sender, PointerEventArgs ^ args)
{
	unsigned pointerID = args->CurrentPoint->PointerId;
	DirectX::XMFLOAT2 position = DirectX::XMFLOAT2(args->CurrentPoint->Position.X, args->CurrentPoint->Position.Y);

	if (pointerID == m_movePointerID)	// This was the move pointer.
	{
		m_moveInUse = false;
		m_movePointerID = 0;
	}
	else if (pointerID == m_lookPointerID)	// This was the look pointer.
	{
		m_lookInUse = false;
		m_lookPointerID = 0;
	}
}

void MoveLookController::OnKeyDown(CoreWindow ^ sender, KeyEventArgs ^ args)
{
	Windows::System::VirtualKey Key;
	Key = args->VirtualKey;

	// Figure out the command from the keyboard.
	if (Key == VirtualKey::W)	// Forward
		m_forward = true;
	if (Key == VirtualKey::S)	// Back
		m_back = true;
	if (Key == VirtualKey::A)	// Left
		m_left = true;
	if (Key == VirtualKey::D)	// Right
		m_right = true;
}

void MoveLookController::OnKeyUp(CoreWindow ^ sender, KeyEventArgs ^ args)
{
	Windows::System::VirtualKey Key;
	Key = args->VirtualKey;

	// Figure out the command from the keyboard.
	if (Key == VirtualKey::W)	// Forward
		m_forward = false;
	if (Key == VirtualKey::S)	// Back
		m_back = false;
	if (Key == VirtualKey::A)	// Left
		m_left = false;
	if (Key == VirtualKey::D)	// Right
		m_right = false;
}
