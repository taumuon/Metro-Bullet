#pragma once

#include <wrl.h>
#include <memory>

#include <DirectXMath.h>

// TODO: this is used by Cube and CubeRenderer.
//  should move somewhere else so both can access
struct VertexPositionColor
{
    DirectX::XMFLOAT3 pos;
    DirectX::XMFLOAT3 color;
};

ref class Transform
{
internal:
	Transform(float locX,
			  float locY,
			  float locZ,
			  float quatX,
			  float quatY,
			  float quatZ,
			  float quatW)
		:
		locX(locX),
		locY(locY),
		locZ(locZ),
		quatX(quatX),
		quatY(quatY),
		quatZ(quatZ),
		quatW(quatW)
	{
	}

	float locX;
	float locY;
	float locZ;
	float quatX;
	float quatY;
	float quatZ;
	float quatW;
};

ref class Cube
{
private:
	~Cube();
internal:
	Cube();

	void SetTransform(const Transform^ transform);

	DirectX::XMMATRIX m_modelMatrix;
private:
};
