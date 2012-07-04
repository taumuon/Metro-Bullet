#pragma once

#include "pch.h"
#include <wrl.h>
#include "CubeRenderer.h"

#include <btBulletDynamicsCommon.h>

class Level;

ref class MetroBullet : public Windows::ApplicationModel::Core::IFrameworkView
{
internal:
    MetroBullet();
public:
    
    // IFrameworkView Methods
    virtual void Initialize(Windows::ApplicationModel::Core::CoreApplicationView^ applicationView);
    virtual void SetWindow(Windows::UI::Core::CoreWindow^ window);
    virtual void Load(Platform::String^ entryPoint);
    virtual void Run();
    virtual void Uninitialize();
protected:
    // Event Handlers
    void OnWindowSizeChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::WindowSizeChangedEventArgs^ args);
    void OnLogicalDpiChanged(Platform::Object^ sender);
    void OnActivated(Windows::ApplicationModel::Core::CoreApplicationView^ applicationView, Windows::ApplicationModel::Activation::IActivatedEventArgs^ args);
    void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ args);
    void OnResuming(Platform::Object^ sender, Platform::Object^ args);
    void OnWindowClosed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::CoreWindowEventArgs^ args);

private:
	std::unique_ptr<Level> m_level;
    CubeRenderer^ m_renderer;
	vector<Cube^> m_cubes;
    Windows::ApplicationModel::Core::CoreApplicationView^ m_applicationView;
    bool m_windowClosed;
};

ref class Direct3DApplicationSource : Windows::ApplicationModel::Core::IFrameworkViewSource
{
public:
    virtual Windows::ApplicationModel::Core::IFrameworkView^ CreateView();
};
