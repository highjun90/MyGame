#pragma once
#include <Windows.h>
#include <string>
#include <assert.h>

//// ���� :
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














//============ ���� ���� �ּ� ==============

//MessageBoxA(
//	nullptr,           //HWND hWnd-> �޼��� �ڽ��� ������ ������ �ڵ�.
//	Value.c_str(),     //LPCTSTR lpTest-> , �޼����ڽ� ���ο� ��µ� ���ڿ�. LP : Long Pointer, C : Constant (�Լ����ο��� ���ں������), T : TypeCasting (�����Ϸ��� precompile option�� ���� ���� ���ڵ��� �˾Ƽ� ��Ƽ����Ʈ �Ǵ� ���̵����Ʈ�� ��Ī������.), STR - STRing, ����� const char* �� �� ���� ����
//	"Error",           //LPCTSTR lpCaption-> �޼����ڽ� ���� ��µ� ���ڿ�.
//	MB_OK);            //UINT uType -> �޼��� �ڽ���Ÿ�� (�������� ����� ��������), unsigned int
//
//assert(false);         //���ǽ��� false�� �������.
