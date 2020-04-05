// camera.h: Stores position, directions for camera.
// Methods for moving, strafing and pitching the camera object.

#pragma once

#include "common.h"
#include "global_device_info.h"
#include <DirectXMath.h>

using namespace DirectX;

enum CAMERA_PROJECTION_TYPE
{
	CAM_ORTHOGRAPHIC,
	CAM_PERSPECTIVE
};

class camera
{
	private:

	CAMERA_PROJECTION_TYPE CameraType;

	XMMATRIX View;
	XMMATRIX Projection;

	XMFLOAT3 Position;
	XMFLOAT3 ViewDirection;
	XMFLOAT3 UpDirection;
	XMFLOAT3 SideDirection;

	real32 FieldOfView;
	real32 AspectRatio;
	real32 DrawStartZ;
	real32 DrawDistanceZ;

	protected:

	void Update();

	public:

	camera();
	~camera() = default;

	void SetPosition(real32 X, real32 Y, real32 Z);

	void MoveForward(real32 Value);
	void MoveBackward(real32 Value);
	void StrafeLeft(real32 Value);
	void StrafeRight(real32 Value);
	void MoveUp(real32 Value);
	void MoveDown(real32 Value);

	void LookY(real32 Value);
	void LookX(real32 Value);

	real32 GetPositionX() const;
	real32 GetPositionY() const;
	real32 GetPositionZ() const;

	const XMMATRIX &GetViewMatrix();
	const XMMATRIX &GetProjectionMatrix();
};