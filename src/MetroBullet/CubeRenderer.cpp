#include "pch.h"
#include "CubeRenderer.h"
#include <DirectXMath.h>
#include "BasicLoader.h"

using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace DirectX;

using namespace std;

CubeRenderer::CubeRenderer() :
    m_loadingComplete(false)
{
}

CubeRenderer::~CubeRenderer()
{
}

void CubeRenderer::CreateDeviceResources()
{
    Direct3DBase::CreateDeviceResources();

	BasicLoader^ loader = ref new BasicLoader(m_d3dDevice.Get());

    D3D11_INPUT_ELEMENT_DESC vertexDesc[] = 
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
	unsigned int numElements = ARRAYSIZE(vertexDesc);

#ifdef USE_ASYNC_LOADING
    loader->LoadShaderAsync("SimpleVertexShader.cso", layout, numElements, &m_vertexShader, &m_vertexLayout);
    loader->LoadShaderAsync("SimplePixelShader.cso", &m_pixelShader);
#else
    loader->LoadShader("SimpleVertexShader.cso", vertexDesc, numElements, &m_vertexShader, &m_inputLayout);
    loader->LoadShader("SimplePixelShader.cso", &m_pixelShader);
#endif

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	// Create the constant buffers
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.ByteWidth = (sizeof(ModelViewProjectionConstantBuffer) + 15) / 16 * 16;
	DX::ThrowIfFailed(
		m_d3dDevice->CreateBuffer(&bd, nullptr, &m_constantBuffer)
		);

	m_loadingComplete = true;
}

Cube^ CubeRenderer::CreateCube()
{
	auto cube = ref new Cube();
	m_cubes.push_back(cube);
	cube->Create(m_d3dDevice);
	return cube;
}

void CubeRenderer::CreateWindowSizeDependentResources()
{
    Direct3DBase::CreateWindowSizeDependentResources();

    float aspectRatio = m_windowBounds.Width / m_windowBounds.Height;
    float fovAngleY = 70.0f * XM_PI / 180.0f;
    if (aspectRatio < 1.0f)
    {
        fovAngleY /= aspectRatio;
    }

    m_constantBufferData.projection = XMMatrixTranspose(XMMatrixPerspectiveFovRH(
        fovAngleY,
        aspectRatio,
        0.01f,
        100.0f
        ));
}

void CubeRenderer::Update(float timeTotal, float timeDelta)
{
    XMVECTOR eye = XMVectorSet(-10.0f, 0.7f, -8.0f, 0.0f);
    XMVECTOR at = XMVectorSet(0.0f, 8.0f, 0.0f, 0.0f);
    XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    m_constantBufferData.view = XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up));
}

void CubeRenderer::Render()
{
    // clear
    m_d3dContext->OMSetRenderTargets(
        1,
        m_renderTargetView.GetAddressOf(),
        m_depthStencilView.Get()
        );

    const float midnightBlue[] = { 0.098f, 0.098f, 0.439f, 1.000f };
    m_d3dContext->ClearRenderTargetView(
        m_renderTargetView.Get(),
        midnightBlue
        );

    m_d3dContext->ClearDepthStencilView(
        m_depthStencilView.Get(),
        D3D11_CLEAR_DEPTH,
        1.0f,
        0
        );

    // only draw the cube once it's loaded (this is async)
    if (!m_loadingComplete)
        return;

	for(auto& cube : m_cubes)
	{
		m_constantBufferData.model = cube->m_modelMatrix;
 
		m_d3dContext->UpdateSubresource(
			m_constantBuffer.Get(),
			0,
			NULL,
			&m_constantBufferData,
			0,
			0
			);

		cube->RenderBuffers(m_d3dContext);

		m_d3dContext->IASetInputLayout(m_inputLayout.Get());

		m_d3dContext->VSSetShader(
			m_vertexShader.Get(),
			nullptr,
			0
			);

		m_d3dContext->VSSetConstantBuffers(
			0,
			1,
			m_constantBuffer.GetAddressOf()
			);

		m_d3dContext->PSSetShader(
			m_pixelShader.Get(),
			nullptr,
			0
			);

		m_d3dContext->DrawIndexed(
			cube->GetIndexCount(),
			0,
			0
			);
	}
}
