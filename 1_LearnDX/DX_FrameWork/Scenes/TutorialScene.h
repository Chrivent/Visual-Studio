#pragma once
// Scene을 상속받아 만든 클래스
// 이렇게 상속받은 클래스들이 실제 게임 화면을 구성하는 데 사용되는 것

class TutorialScene : public Scene
{
private:
	/*
		원래는 여기에 이 씬을 구성하는 오브젝트들을 만들어뒀어야 함
		그러나 지금 코드는 단순히 화면에 뭔가를 출력하는 것만 집중했다보니
		현 시점에서는 오브젝트가 존재하지 않음
	*/
	
public:
	TutorialScene();
	~TutorialScene();


	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	// override: 함수 오버라이딩을 했을때 
	// 부모 클래스에 있는 함수를 오버라이딩 했다고 컴파일러 측에 확실히 알리는 역활
	// 이 키워드를 등록해놓으면 추후 부모 클래스 쪽을 수정해서
	// 이 함수의 원본이 되는 함수가 이름이 바뀌거나 하는 등으로 인해
	// 자식 클래스 쪽에서 접근할 수 없게 되면 컴파일 에러를 발생함

	// 상속받는 클래스를 자동완성시킬 때 기본적으로 붙어서 나옴
	virtual void Render() override;

};