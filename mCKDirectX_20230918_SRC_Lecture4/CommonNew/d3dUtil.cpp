//***************************************************************************************
// d3dUtil.cpp by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************

#include "d3dUtil.h"

void ExtractFrustumPlanes(XMFLOAT4 planes[6], CXMMATRIX M)
{	
	// Left
	//
	planes[0].x = M.r[0].m128_f32[3] + M.r[0].m128_f32[0];
	planes[0].y = M.r[1].m128_f32[3] + M.r[1].m128_f32[0];
	planes[0].z = M.r[2].m128_f32[3] + M.r[2].m128_f32[0];
	planes[0].w = M.r[3].m128_f32[3] + M.r[3].m128_f32[0];

	//
	// Right
	//
	planes[1].x = M.r[0].m128_f32[3] - M.r[0].m128_f32[0];
	planes[1].y = M.r[1].m128_f32[3] - M.r[1].m128_f32[0];
	planes[1].z = M.r[2].m128_f32[3] - M.r[2].m128_f32[0];
	planes[1].w = M.r[3].m128_f32[3] - M.r[3].m128_f32[0];

	//
	// Bottom
	//
	planes[2].x = M.r[0].m128_f32[3] + M.r[0].m128_f32[1];
	planes[2].y = M.r[1].m128_f32[3] + M.r[1].m128_f32[1];
	planes[2].z = M.r[2].m128_f32[3] + M.r[2].m128_f32[1];
	planes[2].w = M.r[3].m128_f32[3] + M.r[3].m128_f32[1];

	//
	// Top
	//
	planes[3].x = M.r[0].m128_f32[3] - M.r[0].m128_f32[1];
	planes[3].y = M.r[1].m128_f32[3] - M.r[1].m128_f32[1];
	planes[3].z = M.r[2].m128_f32[3] - M.r[2].m128_f32[1];
	planes[3].w = M.r[3].m128_f32[3] - M.r[3].m128_f32[1];

	//
	// Near
	//
	planes[4].x = M.r[0].m128_f32[2];
	planes[4].y = M.r[1].m128_f32[2];
	planes[4].z = M.r[2].m128_f32[2];
	planes[4].w = M.r[3].m128_f32[2];

	//
	// Far
	//
	planes[5].x = M.r[0].m128_f32[3] - M.r[0].m128_f32[2];
	planes[5].y = M.r[1].m128_f32[3] - M.r[1].m128_f32[2];
	planes[5].z = M.r[2].m128_f32[3] - M.r[2].m128_f32[2];
	planes[5].w = M.r[3].m128_f32[3] - M.r[3].m128_f32[2];

	// Normalize the plane equations.
	for (int i = 0; i < 6; ++i)
	{
		XMVECTOR v = XMPlaneNormalize(XMLoadFloat4(&planes[i]));
		XMStoreFloat4(&planes[i], v);
	}
}
