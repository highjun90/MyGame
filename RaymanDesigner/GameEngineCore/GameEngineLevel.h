#pragma once
#include "GameEngineObject.h"
#include "GameEngineActor.h"
#include <list>
#include <string>
#include <map>

// 설명 : 화면혹은 장면을 표현합니다.
// 타이틀 장면
// 플레이 장면
// 엔딩 장면
class GameEngineCamera;
class GameEngineLevel : public GameEngineObject
{
	friend class GameEngineActor;
	friend class GameEngineCore;

public:
	// constrcuter destructer
	GameEngineLevel();
	~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;


	template<typename ActorType, typename EnumType>
	ActorType* CreateActor(EnumType _Order)
	{
		return CreateActor<ActorType>(static_cast<int>(_Order));
	}


	template<typename ActorType>
	ActorType* CreateActor(int _Order = 0)
	{
		std::list<GameEngineActor*>& GroupList = AllActors[_Order];
		GameEngineActor* NewActor = new ActorType();
		ActorInit(NewActor, _Order);
		GroupList.push_back(NewActor);

		return dynamic_cast<ActorType*>(NewActor);
	}

	GameEngineCamera* GetMainCamera()
	{
		return MainCamera;
	}

protected:
	virtual void LevelStart(GameEngineLevel* _PrevLevel) {}
	virtual void LevelEnd(GameEngineLevel* _NextLevel) {}

private:
	GameEngineCamera* MainCamera;
	GameEngineCamera* UICamera;

	// 맵
	// 플레이어
	// 몬스터

	// -10번 std::list<> 액터 액터 액터 액터 
	// 0번 std::list<> 액터 액터 액터 액터
	// 1번 std::list<> 액터 액터 액터 액터

	std::map<int, std::list<GameEngineActor*>> AllActors;

	void ActorInit(GameEngineActor* _Actor, int _Order);

	void ActorUpdate(float _Delta);
	void ActorRender();
	void ActorRelease();
};






// ============= 최종 삭제 주석 =============

// Level은 플레이단계라는 듯. 각 Level는 화면에 보여질 Actor를 가짐. Camera도 가짐

// CreateActor() - 새 Actor 만들고 Actor 초반작업을 시켜준후, 자료구조에 push_back. 리턴은 만든 Actor의 포인터

// 밑에 두 함수는 각 Level 시작, 끝일때 처리할 일을 자식함수들이 쓰라고 미리만든 비어있는 함수. 인자는 선생님은 사용하지않지만 쓸 사람 있을지도 몰라서 넣어줬다고함
// virtual void LevelStart(GameEngineLevel* _PrevLevel) {}
// virtual void LevelEnd(GameEngineLevel* _NextLevel) {}