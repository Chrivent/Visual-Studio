#pragma once

// framework.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN				// 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

// Windows 헤더 파일
#include <windows.h>

// 주로 사용할 상수들을 지정하는 매크로문
#define WIN_START_X 100
#define WIN_START_Y 100		// 창이 처음 만들어질 위치를 지정

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720		// 창의 크기로 삼을 값을 지정

#define WIN_CENTER_X (WIN_WIDTH * 0.5f)
#define WIN_CENTER_Y (WIN_HEIGHT * 0.5f)	// 화면 중앙의 좌표를 매크로로서 손쉽게 사용하도록 매크로 상수 선언

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#define _USE_MATH_DEFINES	// math.h에 정의된 몇몇 상수를 이용하기 위해 
							// 반드시 math.h를 포함라기 전에 선언 해둬야하는 키워드
#include <math.h>

// DirectX 11을 이용하기 위한 라이브러리
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace std;
using namespace DirectX;		// DX 쪽의 클래스들은 상당수 DirectX라는 네임스페이스 안에 있음
								// 따라서 이것들을 항상 사용할 예정이니 아예 해당 네임스페이스를 상시 사용

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;		// XMFLOAT 시리즈 : DX에서 지원하는, 실수 X개 저장하는 구조체
								// 이 형식을 이용하는 DX 쪽의 함수가 많기 때문에,
								// 이를 편하게 이용하기 위해 typedef를 이용하여 축약

typedef XMMATRIX Matrix;		// XMMATRIX : DX에서 지원하는, 행렬을 저장한느 용도의 유니온(구조체)

// 이 아래의 내용들은 우리가 직접 만들어낸 프레임워크의 헤더들
// 프레임워크를 새로이 구성할 때마다 추가될 예정
// 이 아래에 추가되는 헤더들은 반드시 올바른 순서대로 추가되어야 함

// Framework Header
#include "Framework/System/Device.h"
#include "Framework/Shader/VertexShader.h"
#include "Framework/Shader/PixelShader.h"

// Object Header - 앞으로 이 프로그램에서 오브젝트 만들 일 있으면 그때그때 추가
#include "Object/Shape/Vertex.h"

// Scenes Header
#include "Scenes/Scene.h"
#include "Scenes/TutorialScene.h"

// Program Header
#include "Program/Program.h"

extern HWND hWnd;

#endif //PCH_H