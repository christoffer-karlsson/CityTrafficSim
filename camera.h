// camera.h: Stores position, directions for camera.
// Methods for moving, strafing and pitching the camera object.

#pragma once

#include "common.h"
#include "direct3d.h"

class camera
{
	private:

	static XMMATRIX View;
	static XMMATRIX Projection;
	static XMMATRIX Ortho;

	static XMFLOAT3 Position;
	static XMFLOAT3 ViewDirection;
	static XMFLOAT3 UpDirection;
	static XMFLOAT3 SideDirection;

	static real32 FieldOfView;
	static real32 AspectRatio;
	static real32 NearZ;
	static real32 FarZ;

	protected:

	static void Update();

	public:

	static void Init();

	static void SetPosition(real32 X, real32 Y, real32 Z);

	static void MoveForward(real32 Value);
	static void MoveBackward(real32 Value);
	static void StrafeLeft(real32 Value);
	static void StrafeRight(real32 Value);
	static void MoveUp(real32 Value);
	static void MoveDown(real32 Value);

	static void LookY(real32 Value);
	static void LookX(real32 Value);

	static real32 GetPositionX();
	static real32 GetPositionY();
	static real32 GetPositionZ();

	static const XMMATRIX &GetViewMatrix();
	static const XMMATRIX &GetProjectionMatrix();
	static const XMMATRIX &GetOrthographicMatrix();
};