#pragma once
//�� �״�� ������Ʈ�� ���� �̸� ����غ��� Scene

class ObjectTrialScene : public Scene
{
private:
	Triangle* t;
	Star* s;

public:
	ObjectTrialScene();
	~ObjectTrialScene();


	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;

};