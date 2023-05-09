#include "GameEngineTime.h"
#include <Windows.h>

GameEngineTime GameEngineTime::MainTimer;

GameEngineTime::GameEngineTime()
{
	QueryPerformanceFrequency(&Count);
	Reset();
}

GameEngineTime::~GameEngineTime()
{
}

void GameEngineTime::Reset()
{
	QueryPerformanceCounter(&Cur);
	Prev = Cur;
}

void GameEngineTime::Update()
{
	QueryPerformanceCounter(&Cur);
	Tick = Cur.QuadPart - Prev.QuadPart;

	DoubleDelta = static_cast<double>(Tick) / static_cast<double>(Count.QuadPart);
	Prev.QuadPart = Cur.QuadPart;
	FloatDelta = static_cast<float>(DoubleDelta);
}



// ===== 최종 삭제 주석 ==========

// QueryPerformanceFrequency(&Count); - 타이머의 초당 주파수(즉 초당 클럭수)를 Count에 기록해줌.
// count는 LARGE_INTEGER 에서도 컴파일러가 64비트라면 __int64 인 QuardPart에 저장되고 32비트면 LowPart HighPart에 나눠 저장됨

// QueryPerformanceCounter(&Cur); - 타이머의 CPU 클럭수를 Cur에 기록해주는 함수. 