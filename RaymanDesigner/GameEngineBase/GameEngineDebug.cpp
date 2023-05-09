#include "GameEngineDebug.h"
#include <crtdbg.h>

GameEngineDebug::GameEngineDebug()
{
}

GameEngineDebug::~GameEngineDebug()
{
}


void GameEngineDebug::LeckCheck()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}







// ========= ���� ���� �ּ� ============

//_CrtSetDbgFlag(   // Crt -> C RunTime. �־��� ��Ʈ �ʵ�(Flag)�� �������� ����� �� �������� �Ҵ� ������ ��������.
//	int newFlag)    // _CRTDBG_ALLOC_MEM_DF -> ON: ����� �� �Ҵ�� �޸� ������� �ĺ����� ����� �����Ѵ�. OFF: ���� ����� ��Ͽ� �� �Ҵ��� �߰������� ��� ������ _IGNORE_BLOCK ���� ����.
//	                                           // �ѱ������ؼ�: ����� ��忡�� �� �޸� �Ҵ��� ������ְ� ����� ���� �޸� ���� ����Ѵ�.
//	                // _CRTDBG_LEAK_CHECK_DF -> ON: _CrtDumpMeMoryLeaks ���α׷� ����� �ڵ� ���� �˻縦 �����ϰ� ���ø����̼��� �Ҵ��� ��� �޸𸮸� �������� ���� ��� ������ report�մϴ�
//	                // https://learn.microsoft.com/ko-kr/cpp/c-runtime-library/reference/crtsetdbgflag?view=msvc-170
//                  // ����� �׳� �޸� ���� üũ���ְ� �����Ǹ� �������� ���ִ� �Լ�.