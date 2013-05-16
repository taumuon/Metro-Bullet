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

	uint32 GetIndexCount();

	void Create(Microsoft::WRL::ComPtr<ID3D11Device1> &d3dDevice);

	void RenderBuffers(Microsoft::WRL::ComPtr<ID3D11DeviceContext1> &d3dContext);

	void SetTransform(const Transform^ transform);

	DirectX::XMMATRIX m_modelMatrix;
private:
	uint32 m_indexCount;

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
};
