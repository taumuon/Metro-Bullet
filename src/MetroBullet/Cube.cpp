#include "pch.h"
#include "Cube.h"
#include <DirectXMath.h>

#include "DirectXHelper.h"

using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace DirectX;

Cube::Cube()
	: m_indexCount(0)
{
}

Cube::~Cube()
{
}

void Cube::Create(Microsoft::WRL::ComPtr<ID3D11Device1> &d3dDevice)
{
    VertexPositionColor cubeVertices[] = 
    {
        {XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f)},
        {XMFLOAT3(-0.5f, -0.5f,  0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f)},
        {XMFLOAT3(-0.5f,  0.5f, -0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f)},
        {XMFLOAT3(-0.5f,  0.5f,  0.5f), XMFLOAT3(0.0f, 1.0f, 1.0f)},
        {XMFLOAT3( 0.5f, -0.5f, -0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f)},
        {XMFLOAT3( 0.5f, -0.5f,  0.5f), XMFLOAT3(1.0f, 0.0f, 1.0f)},
        {XMFLOAT3( 0.5f,  0.5f, -0.5f), XMFLOAT3(1.0f, 1.0f, 0.0f)},
        {XMFLOAT3( 0.5f,  0.5f,  0.5f), XMFLOAT3(1.0f, 1.0f, 1.0f)},
    };

    D3D11_SUBRESOURCE_DATA vertexBufferData = {0};
    vertexBufferData.pSysMem = cubeVertices;
    vertexBufferData.SysMemPitch = 0;
    vertexBufferData.SysMemSlicePitch = 0;
    DX::ThrowIfFailed(
        d3dDevice->CreateBuffer(
            &CD3D11_BUFFER_DESC(sizeof(cubeVertices), D3D11_BIND_VERTEX_BUFFER),
            &vertexBufferData,
            &m_vertexBuffer
            )
        );

    unsigned short cubeIndices[] = 
    {
        0,2,1, // -x
        1,2,3,

        4,5,6, // +x
        5,7,6,

        0,1,5, // -y
        0,5,4,

        2,6,7, // +y
        2,7,3,

        0,4,6, // -z
        0,6,2,

        1,3,7, // +z
        1,7,5,
    };

	m_indexCount = ARRAYSIZE(cubeIndices);

    D3D11_SUBRESOURCE_DATA indexBufferData = {0};
    indexBufferData.pSysMem = cubeIndices;
    indexBufferData.SysMemPitch = 0;
    indexBufferData.SysMemSlicePitch = 0;
    DX::ThrowIfFailed(
        d3dDevice->CreateBuffer(
            &CD3D11_BUFFER_DESC(sizeof(cubeVertices), D3D11_BIND_INDEX_BUFFER),
            &indexBufferData,
            &m_indexBuffer
            )
        );
}

void Cube::RenderBuffers(Microsoft::WRL::ComPtr<ID3D11DeviceContext1> &d3dContext)
{
    UINT stride = sizeof(VertexPositionColor);
    UINT offset = 0;
    d3dContext->IASetVertexBuffers(
        0,
        1,
		m_vertexBuffer.GetAddressOf(),
        &stride,
        &offset
        );

    d3dContext->IASetIndexBuffer(
		m_indexBuffer.Get(),
        DXGI_FORMAT_R16_UINT,
        0
        );

    d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

uint32 Cube::GetIndexCount()
{
	return m_indexCount;
}

void Cube::SetTransform(const Transform^ transform)
{
	XMVECTOR data;
	XMVECTORF32 floatingVector = { transform->quatX, transform->quatY, transform->quatZ, transform->quatW };
	data = floatingVector;

	auto rotationMatrix = XMMatrixRotationQuaternion(data);
	auto translationMatrix = XMMatrixTranslation(transform->locX, transform->locY, transform->locZ);
	m_modelMatrix = XMMatrixTranspose(rotationMatrix * translationMatrix);
}