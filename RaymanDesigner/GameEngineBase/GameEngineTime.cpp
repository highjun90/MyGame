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



// ===== ���� ���� �ּ� ==========

// QueryPerformanceFrequency(&Count); - Ÿ�̸��� �ʴ� ���ļ�(�� �ʴ� Ŭ����)�� Count�� �������.
// count�� LARGE_INTEGER ������ �����Ϸ��� 64��Ʈ��� __int64 �� QuardPart�� ����ǰ� 32��Ʈ�� LowPart HighPart�� ���� �����

// QueryPerformanceCounter(&Cur); - Ÿ�̸��� CPU Ŭ������ Cur�� ������ִ� �Լ�. 