#pragma once

#include "DirectXHelper.h"

// Helper class that initializes DirectX APIs
ref class Direct3DBase abstract
{
internal:
    Direct3DBase();

    virtual void Initialize(Windows::UI::Core::CoreWindow^ window);
    virtual void CreateDeviceResources();
    virtual void CreateWindowSizeDependentResources();
    virtual void UpdateForWindowSizeChange();
    virtual void Render() = 0;
    virtual void Present();

internal:

    // Direct3D Objects
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext;
    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;

    D3D_FEATURE_LEVEL                               m_featureLevel;
    Windows::Foundation::Size                       m_renderTargetSize;
    Windows::Foundation::Rect                       m_windowBounds;
    Windows::UI::Core::CoreWindow^                  m_window;
};
