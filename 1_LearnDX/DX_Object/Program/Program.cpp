#include "framework.h"

Program::Program()
{
	Create();
	scene = new ObjectTrialScene();
	// 바로 이 부분을 통해 프로그램이 어떤 Scene을 사용할 것인지를 설정
	// DX를 다루는 초반 구간에서는 Scene을 많아봐야 하나만 사용할 것이므로
	// 그 Scene을 여기서 설정하고, 나중에 필요하면 기존 Scene은 놔둔 채
	// 새로운 Scene을 여기에 등록해서 사용하는 식으로 프로그램을 구성할 예정
}

Program::~Program()
{
	delete scene;
}

void Program::Update()
{
	scene->Update();
}

void Program::Render()
{
	Device::Get()->Clear();
	// 원래는 프로그램에서 Render 함수가 호출되었을 때 이뤄져야 하지만
	// 지금 당장은 Scene을 한 번에 하나만 다루기 때문에
	// 그리고 Scene 내부에서 또 화면 초기화를 하기 때문에 여기서는 생략
	scene->Render();
	Device::Get()->Present();

}

void Program::Create()
{
	Device::Get(); // 싱글톤을 여기서 생성
}

void Program::Delete()
{
	Device::Delete();
}
