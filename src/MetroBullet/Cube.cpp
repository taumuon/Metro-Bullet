#include "pch.h"
#include "Cube.h"
#include <DirectXMath.h>

#include "DirectXHelper.h"

using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace DirectX;

Cube::Cube()
{
}

Cube::~Cube()
{
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