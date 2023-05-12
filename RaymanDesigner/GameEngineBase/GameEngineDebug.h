#pragma once
#include <Windows.h>
#include <string>
#include <assert.h>

//// 설명 :
class GameEngineDebug
{
public:
	// constrcuter destructer
	GameEngineDebug();
	~GameEngineDebug();

	// delete Function
	GameEngineDebug(const GameEngineDebug& _Other) = delete;
	GameEngineDebug(GameEngineDebug&& _Other) noexcept = delete;
	GameEngineDebug& operator=(const GameEngineDebug& _Other) = delete;
	GameEngineDebug& operator=(GameEngineDebug&& _Other) noexcept = delete;

	static void LeckCheck();

protected:

private:

};

#define MsgBoxAssert(Text) \
std::string Value = Text; \
MessageBoxA(nullptr, Value.c_str(), "Error", MB_OK); assert(false);














//============ 최종 삭제 주석 ==============

//MessageBoxA(
//	nullptr,           //HWND hWnd-> 메세지 박스를 소유할 윈도우 핸들.
//	Value.c_str(),     //LPCTSTR lpTest-> , 메세지박스 내부에 출력될 문자열. LP : Long Pointer, C : Constant (함수내부에서 인자변경금지), T : TypeCasting (컴파일러가 precompile option을 보고 문자 인코딩을 알아서 멀티바이트 또는 와이드바이트로 매칭시켜줌.), STR - STRing, 결론은 const char* 랑 별 차이 없음
//	"Error",           //LPCTSTR lpCaption-> 메세지박스 제목에 출력될 문자열.
//	MB_OK);            //UINT uType -> 메세지 박스의타입 (여러가지 기능을 설정해줌), unsigned int
//
//assert(false);         //조건식이 false면 오류띄움.
