#pragma once
#include <Windows.h>

// 설명 :
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




// =============== 최종 삭제 주석 =============

// LARGE_INTEGER는 일단 공용체임. 
// 
//typedef union _LARGE_INTEGER {
//	struct {
//		DWORD LowPart;      //DWORD 는 그냥 unsigned long임
//		LONG HighPart;      //LONG 은 말그대로 long
//	} DUMMYSTRUCTNAME;
//	struct {
//		DWORD LowPart;
//		LONG HighPart;
//	} u;
//	LONGLONG QuadPart;       //LONGLONG 은 __int64임.
//} LARGE_INTEGER;