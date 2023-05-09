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







// ========= 최종 삭제 주석 ============

//_CrtSetDbgFlag(   // Crt -> C RunTime. 넣어준 비트 필드(Flag)를 바탕으로 디버그 힙 관리자의 할당 동작을 제어해줌.
//	int newFlag)    // _CRTDBG_ALLOC_MEM_DF -> ON: 디버그 힙 할당과 메모리 블록형식 식별자의 사용을 설정한다. OFF: 힙에 연결된 목록에 새 할당을 추가하지만 블록 형식을 _IGNORE_BLOCK 으로 설정.
//	                                           // 한국말로해석: 디버그 모드에서 힙 메모리 할당을 허용해주고 사용자 정의 메모리 블럭을 사용한다.
//	                // _CRTDBG_LEAK_CHECK_DF -> ON: _CrtDumpMeMoryLeaks 프로그램 종료시 자동 누수 검사를 수행하고 애플리케이션이 할당한 모든 메모리를 해제하지 못한 경우 오류를 report합니다
//	                // https://learn.microsoft.com/ko-kr/cpp/c-runtime-library/reference/crtsetdbgflag?view=msvc-170
//                  // 결론은 그냥 메모리 누수 체크해주고 누수되면 오류나게 해주는 함수.