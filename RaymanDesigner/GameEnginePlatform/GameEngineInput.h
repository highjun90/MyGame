#pragma once
#include <Windows.h>
#include <map>
#include <string>

// ���� :
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

		// �ǹ̰� ���ٰ� ����.
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




// ========= ���� ���� �ּ� ===========

//SHORT GetAsyncKeyState( //Ű�� ������ ����(Down) �Ǵ� �������� ����(UP) ȣ��
//	[in] int vKey       // �� 4���� ���¸� ��ȯ��. ������ �� �Լ��� ���������� ȣ��� ���ĸ� �������� �ٽ� ȣ��������� Ű������.
//);                      // 1. �������� �������°� �ƴϾ��� ���� ȣ��� �������� �ȴ�����. (Free) ��ȯ�� 0 (0x0000) 
//                        // 2. �������� �������°� �ƴϾ����� ���� �� ���� (Down) ��ȯ�� 0x8000 
//                        // 3. �������� �������¿��� ���ݵ� ���������� (Press) ��ȯ�� 0x8001
//                        // 4. �������� ������������ ������ �� ������ (Up) ��ȯ�� 1 (0x0001)

//KeyCheck() - 0�̴� == ���� Free ������. false ����. 0 �ƴϴ� == ���� Down, Press, Up �� �ϳ��� ���¶�°���. true ����

//Reset() - Press���¿�����  Up ���·�, Up���� ������ Free���·� �ٲ��ش�. GameEngineInput�� �� ����Ŭ������ GameEngineKey�� Reset()�� �̸��� ���� �ϴ��ϵ� �ᱹ ��������