#pragma once
#include <Windows.h>
#include <map>
#include <string>

// 설명 :
class GameEngineInput
{
private:
	class GameEngineKey
	{
		friend GameEngineInput;

		bool Down = false;
		bool Press = false;
		bool Up = false;
		bool Free = true;

		// 의미가 없다고 봐요.
		float PressTime = 0.0f;

		int Key = -1;

		bool KeyCheck()
		{
			return 0 != GetAsyncKeyState(Key);
		}

		void Reset()
		{
			if (true == Press)
			{
				Down = false;
				Press = false;
				Up = true;
				Free = true;
			}
			else if (true == Up)
			{
				Down = false;
				Press = false;
				Up = false;
				Free = true;
			}
		}

		void Update(float _DeltaTime);

	public:
		GameEngineKey()
			: Key(-1)
		{

		}

		GameEngineKey(int _Key)
			: Key(_Key)
		{

		}
	};

public:
	// constrcuter destructer
	GameEngineInput();
	~GameEngineInput();

	// delete Function
	GameEngineInput(const GameEngineInput& _Other) = delete;
	GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(GameEngineInput&& _Other) noexcept = delete;

	static void InputInit();
	static void Update(float _DeltaTime);
	static void Reset();

	static bool IsDown(int _Key);
	static bool IsUp(int _Key);
	static bool IsPress(int _Key);
	static bool IsFree(int _Key);

protected:

private:
	static std::map<int, GameEngineKey> AllKeys;
};




// ========= 최종 삭제 주석 ===========

//SHORT GetAsyncKeyState( //키가 눌러진 순간(Down) 또는 떨어지는 순간(UP) 호출
//	[in] int vKey       // 총 4가지 상태를 반환함. 기준은 이 함수가 마지막으로 호출된 이후를 기준으로 다시 호출됬을때의 키상태임.
//);                      // 1. 이전에도 눌린상태가 아니었고 지금 호출된 순간에도 안눌렸음. (Free) 반환값 0 (0x0000) 
//                        // 2. 이전에는 눌린상태가 아니었지만 지금 막 눌림 (Down) 반환값 0x8000 
//                        // 3. 이전에도 눌린상태였고 지금도 눌린상태임 (Press) 반환값 0x8001
//                        // 4. 이전에는 눌린상태지만 지금은 막 떼졌음 (Up) 반환값 1 (0x0001)

//KeyCheck() - 0이다 == 지금 Free 상태임. false 리턴. 0 아니다 == 지금 Down, Press, Up 중 하나의 상태라는거임. true 리턴

//Reset() - Press상태였으면  Up 상태로, Up상태 였으면 Free상태로 바꿔준다. GameEngineInput과 그 내부클래스인 GameEngineKey의 Reset()은 이름도 같고 하는일도 결국 같은거임