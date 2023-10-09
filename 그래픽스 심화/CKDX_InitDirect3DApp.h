#pragma once

#include "d3dApp.h"

class CKDX_InitDirect3DApp : public D3DApp
{
public:
	CKDX_InitDirect3DApp(HINSTANCE hInstance);
	~CKDX_InitDirect3DApp();

	bool Init();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene();
};