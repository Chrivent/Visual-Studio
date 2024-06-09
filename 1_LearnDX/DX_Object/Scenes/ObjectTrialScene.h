#pragma once
//말 그대로 오브젝트를 만들어서 이를 출력해보는 Scene

class ObjectTrialScene : public Scene
{
private:
	Triangle* t;
	Star* s;

public:
	ObjectTrialScene();
	~ObjectTrialScene();


	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;

};