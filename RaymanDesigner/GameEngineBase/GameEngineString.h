#pragma once
#include <string>

// 설명 :
class GameEngineString
{
public:
	// constrcuter destructer
	GameEngineString();
	~GameEngineString();

	// delete Function
	GameEngineString(const GameEngineString& _Other) = delete;
	GameEngineString(GameEngineString&& _Other) noexcept = delete;
	GameEngineString& operator=(const GameEngineString& _Other) = delete;
	GameEngineString& operator=(GameEngineString&& _Other) noexcept = delete;

	static std::string ToUpperReturn(const std::string& _Value)
	{
		std::string UpperString = _Value;

		for (size_t i = 0; i < UpperString.size(); i++)
		{
			UpperString[i] = toupper(UpperString[i]);
		}

		return UpperString;
	}

protected:

private:

};




// ======== 최종 삭제 주석 ===========

// int toupper(int c) 함수 - 문자를 정수형으로 받아서 소문자였을 경우 대문자인 값으로 바꿔서 리턴하는 간단한 함수
// 참고 - char& std::string::operator[] (size_t pos); - string의 연산자 []의 정의. const 버전 오버로딩 함수도 있음.
// size_t는 unsigned __int64임