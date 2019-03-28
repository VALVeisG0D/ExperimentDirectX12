#include "pch.h"
#include "MoveLookController.h"	// Putting definitions in a different .cpp file allows it to be compiled and linked SEPERATELY,
								// thus preventing any conflicts due to violation of the ONE DEFINITION RULE

void MoveLookController::OnPointerPressed(CoreWindow ^ sender, PointerEventArgs ^ args)
{
	// Get the current pointer position.
	unsigned pointerID = args->CurrentPoint->PointerId;
	XMFLOAT2 position = XMFLOAT2(args->CurrentPoint->Position.X, args->CurrentPoint->Position.Y);

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
			m_lookInUse = true;
			sender->PointerCursor = nullptr;	// Hide the cursor
		}
		else
		{
			m_lookPointerID = 0;
			m_lookInUse = false;
			sender->PointerCursor = ref new CoreCursor(CoreCursorType::Arrow, 0);	// Show the cursor
		}
	}
}

void MoveLookController::OnPointerMoved(CoreWindow ^ sender, PointerEventArgs ^ args)
{
	unsigned pointerID = args->CurrentPoint->PointerId;
	XMFLOAT2 position = XMFLOAT2(args->CurrentPoint->Position.X, args->CurrentPoint->Position.Y);

	// Decide which control this pointer is operating.
	if (pointerID == m_movePointerID)		// This is the move pointer.
		// Move control
		m_movePointerPosition = position;	// Save the current position.
	else if (pointerID == m_lookPointerID)	// This is the look pointer.
	{
		//	Look control
		//	Update our orientation based on the commandd.
		//	Mouse y increases down, but pitch increases up.
		//	Yaw is defined as CCW around the y-axis.
		m_pitch -= (position.y - m_lookLastPoint.y) * ROTATION_GAIN;	// How far did pointer move and scaling for control sensitivity
		m_yaw -= (position.x - m_lookLastPoint.x) * ROTATION_GAIN;

		m_lookLastPoint = position;	// Save for the next time through

		// Limit the pitch to straight up or straight down.
		m_pitch = (float)__max(-XM_PI / 2.0f, m_pitch);
		m_pitch = (float)__min(+XM_PI / 2.0f, m_pitch);
	}
}

void MoveLookController::OnPointerReleased(CoreWindow ^ sender, PointerEventArgs ^ args)
{
	//unsigned pointerID = args->CurrentPoint->PointerId;
	//DirectX::XMFLOAT2 position = DirectX::XMFLOAT2(args->CurrentPoint->Position.X, args->CurrentPoint->Position.Y);

	//if (pointerID == m_movePointerID)	// This was the move pointer.
	//{
	//	m_moveInUse = false;
	//	m_movePointerID = 0;
	//}
	//else if (pointerID == m_lookPointerID)	// This was the look pointer.
	//{
	//	m_lookInUse = false;
	//	m_lookPointerID = 0;
	//}
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
	if (Key == VirtualKey::Space)	// Up
		m_up = true;
	if (Key == VirtualKey::Control)	// Down
		m_down = true;
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
	if (Key == VirtualKey::Space)	// Up
		m_up = false;
	if (Key == VirtualKey::Control)	// Down
		m_down = false;
}

void MoveLookController::OnMouseMoved(MouseDevice ^ mouseDevice, MouseEventArgs ^ args)
{
	if (m_lookInUse)
	{
		// Scale for control sensitivity and update our orientation based on the command
		m_pitch -= static_cast<float>(args->MouseDelta.Y) * ROTATION_GAIN;	// Mouse y increases down, but pitch increases up
		m_yaw -= static_cast<float>(args->MouseDelta.X) * ROTATION_GAIN;	// Yaw defined as CCW around y-axis

		// Limit pitch to straight up or straight down
		float limit = (float)(XM_PI / 2) - 0.01f;
		m_pitch = (float)__max(-limit, m_pitch);
		m_pitch = (float)__min(+limit, m_pitch);

		// Keep longitudinal in useful range by wrapping
		if (m_yaw > XM_PI)
			m_yaw -= (float)DirectX::XM_PI * 2;
		else if (m_yaw < -XM_PI)
			m_yaw += (float)XM_PI * 2;
	}
}

void MoveLookController::Initialize(CoreWindow ^ window)
{
	// Opt in to receive touch/mouse events.
	window->PointerPressed +=
		ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &MoveLookController::OnPointerPressed);

	window->PointerMoved +=
		ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &MoveLookController::OnPointerMoved);

	window->PointerReleased +=
		ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &MoveLookController::OnPointerReleased);

	window->KeyDown +=
		ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &MoveLookController::OnKeyDown);

	window->KeyUp +=
		ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &MoveLookController::OnKeyUp);

	MouseDevice::GetForCurrentView()->MouseMoved +=
		ref new TypedEventHandler<MouseDevice^, MouseEventArgs^>(this, &MoveLookController::OnMouseMoved);

	// Initialize the state of the controller
	m_moveInUse = false;			// No pointer is in the Move control.
	m_movePointerID = 0;

	m_lookInUse = false;			// No pointer is in the Look control.
	m_lookPointerID = 0;

	// Need to init this as it is reset every frame.
	m_moveCommand = XMFLOAT3(0.0f, 0.0f, 0.0f);

	SetOrientation(0, 0);			// Look straight ahead when the app starts.
}

void MoveLookController::Update(CoreWindow ^ window)
{
	// Check for input from the Move control.
	if (m_moveInUse)
	{
		DirectX::XMFLOAT2 pointerDelta(m_movePointerPosition);
		pointerDelta.x -= m_moveFirstDown.x;
		pointerDelta.y -= m_moveFirstDown.y;

		// Figure out the command from the touch-based virtual joystick.
		if (pointerDelta.x > 16.0f)		// Leave 32 pixel-wide dead spot for being still.
			m_moveCommand.x = 1.0f;
		else
			if (pointerDelta.x < -16.0f)
				m_moveCommand.x = -1.0f;

		if (pointerDelta.y > 16.0f)		// Joystick y is up, so change sign.
			m_moveCommand.y = -1.0f;
		else
			if (pointerDelta.y < -16.0f)
				m_moveCommand.y = 1.0f;
	}

	XMFLOAT3 tempLookAt = get_LookPoint();
	XMVECTOR vectorPosition = XMLoadFloat3(&m_position);
	XMVECTOR vectorLookAt = XMLoadFloat3(&tempLookAt);
	
	XMVECTOR w = XMVector3Normalize(vectorLookAt - vectorPosition);
	XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };
	XMVECTOR u = XMVector3Normalize(XMVector3Cross(up, w));
	XMVECTOR v = XMVector3Cross(w, u);

	// Pole our state bits that are set by the keyboard input events.
	if (m_forward)
		vectorPosition += w * MOVEMENT_GAIN;
	if (m_back)
		vectorPosition += w * -MOVEMENT_GAIN;

	if (m_left)
		vectorPosition += u * MOVEMENT_GAIN;
	if (m_right)
		vectorPosition += u * -MOVEMENT_GAIN;

	if (m_up)
		vectorPosition += v * MOVEMENT_GAIN;
	if (m_down)
		vectorPosition += v * -MOVEMENT_GAIN;

	XMStoreFloat3(&m_position, vectorPosition);
	
	// Clear movement input accumulator for use during the next frame.
	m_moveCommand = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

void MoveLookController::SetPosition(XMFLOAT3 pos)
{
	m_position = pos;
}

// Accessor to set the position of the controller.
void MoveLookController::SetOrientation(float pitch, float yaw)
{
	m_pitch = pitch;
	m_yaw = yaw;
}

// Returns the position of the controller object.
DirectX::XMFLOAT3 MoveLookController::get_Position()
{
	return m_position;
}

DirectX::XMFLOAT3 MoveLookController::get_LookPoint()
{
	float y = sinf(m_pitch);			// Vertical
	float r = cosf(m_pitch);			// In the plane
	float z = r * cosf(m_yaw);			// Fwd-back
	float x = r * sinf(m_yaw);			// Left-right
	XMFLOAT3 result(x, y, z);
	result.x += m_position.x;
	result.y += m_position.y;
	result.z += m_position.z;

	// Return m_position + DirectX::XMFLOAT3(x, y, z);
	return result;
}
