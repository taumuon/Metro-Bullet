#pragma once

#include <wrl.h>
#include <memory>

#include "Direct3DBase.h"
#include <DirectXMath.h>

#include "Cube.h"

using namespace std;

struct ModelViewProjectionConstantBuffer
{
    DirectX::XMMATRIX model;
    DirectX::XMMATRIX view;
    DirectX::XMMATRIX projection;
};

ref class CubeRenderer : public Direct3DBase
{
internal:
	CubeRenderer();
	~CubeRenderer();
	virtual void CreateDeviceResources() override;
	virtual void CreateWindowSizeDependentResources() override;
	virtual void Render() override;
	Cube^ CreateCube();
	void Update(float timeTotal, float timeDelta);

private:
	bool m_loadingComplete;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	ModelViewProjectionConstantBuffer m_constantBufferData;
	vector<Cube^> m_cubes;
};
