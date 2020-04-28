/*
==========================================================
	Camera class that stores transformed view and projection 
	matrices. Override virtual functions for different
	camera functionality.
==========================================================
*/

#pragma once

#include "common.h"
#include "d3d_api.h"

class camera
{
	protected:

	XMMATRIX View;
	XMMATRIX Projection;
	XMMATRIX Orthographic;

	XMFLOAT3 Position;
	XMFLOAT3 ViewDirection;
	XMFLOAT3 UpDirection;
	XMFLOAT3 SideDirection;

	real32 FieldOfView;
	real32 AspectRatio;
	real32 NearZ;
	real32 FarZ;

	void Update();

	public:

	virtual void Init();

	void SetPosition(real32 X, real32 Y, real32 Z);

	virtual void MoveForward(real32 Value);
	virtual void MoveBackward(real32 Value);
	virtual void MoveLeft(real32 Value);
	virtual void MoveRight(real32 Value);
	virtual void MoveUp(real32 Value);
	virtual void MoveDown(real32 Value);

	virtual void LookY(real32 Value);
	virtual void LookX(real32 Value);

	vec3 GetPosition();

	const XMMATRIX &GetViewMatrix();
	const XMMATRIX &GetProjectionMatrix();
	const XMMATRIX &GetOrthographicMatrix();
};

typedef camera camera_free;

class camera_pan : public camera
{
	void MoveForward(real32 Value) override;
	void MoveBackward(real32 Value) override;
	void MoveLeft(real32 Value) override;
	void MoveRight(real32 Value) override;
};

extern camera_free	DebugCamera;
extern camera_pan	LockedCamera;
extern camera		*ActiveCamera;

void R_SetActiveCamera(camera &Camera);