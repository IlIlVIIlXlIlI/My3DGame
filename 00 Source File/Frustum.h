#pragma once
#include "BASE.h"
#include "CD3DXMESH.h"
#include "CD3DXSKINMESH.h"
#include "CAMERA.h"

class Frustum
{
private:


public:
	bool VFCulling(CD3DXMESH*, D3DXMATRIX*, float, float, float, float);
	bool VFCulling(CD3DXSKINMESH*, D3DXMATRIX*, float, float, float, float);
	bool VFCulling(CAMERA*, D3DXMATRIX*, float, float, float, float);
};
