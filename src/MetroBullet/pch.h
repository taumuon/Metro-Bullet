#pragma once

#include <wrl.h>
#include <d3d11_1.h>
#include <d2d1_1.h>
#include <d2d1effects.h>
#include <dwrite_1.h>
#include <wincodec.h>
#include <DirectXMath.h>

#include <xaudio2.h>
#include <xaudio2fx.h>

#include <mmreg.h>
#include <mfidl.h>
#include <mfapi.h>
#include <mfreadwrite.h>

#include <XInput.h>

#include <stdio.h>
#include <vector>
#include <memory>
#include <agile.h>

//template<typename T, typename... Args>
//std::unique_ptr<T> make_unique(Args&&... args)
//{
//	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
//}

template<class T>
std::unique_ptr<T> make_unique()
{
	// naive implementation
	return std::unique_ptr<T>(new T());
}