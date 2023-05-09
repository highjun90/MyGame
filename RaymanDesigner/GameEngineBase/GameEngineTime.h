#pragma once
#include <Windows.h>

// ���� :
class GameEngineTime
{
public:
	static GameEngineTime MainTimer;

	// constrcuter destructer
	GameEngineTime();
	~GameEngineTime();

	// delete Function
	GameEngineTime(const GameEngineTime& _Other) = delete;
	GameEngineTime(GameEngineTime&& _Other) noexcept = delete;
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete;
	GameEngineTime& operator=(GameEngineTime&& _Other) noexcept = delete;

	float GetDeltaTime()
	{
		return FloatDelta;
	}

	void Reset();

	void Update();

protected:

private:
	LARGE_INTEGER Count = { 0 };
	LARGE_INTEGER Cur = { 0 };
	LARGE_INTEGER Prev = { 0 };
	__int64 Tick;
	double DoubleDelta;
	float FloatDelta;
};




// =============== ���� ���� �ּ� =============

// LARGE_INTEGER�� �ϴ� ����ü��. 
// 
//typedef union _LARGE_INTEGER {
//	struct {
//		DWORD LowPart;      //DWORD �� �׳� unsigned long��
//		LONG HighPart;      //LONG �� ���״�� long
//	} DUMMYSTRUCTNAME;
//	struct {
//		DWORD LowPart;
//		LONG HighPart;
//	} u;
//	LONGLONG QuadPart;       //LONGLONG �� __int64��.
//} LARGE_INTEGER;