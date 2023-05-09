#include "GameEngineRandom.h"
#include <iostream>

GameEngineRandom GameEngineRandom::MainRandom;

GameEngineRandom::GameEngineRandom()
{
	Seed = (int)time(nullptr);
	srand(Seed);
}

GameEngineRandom::GameEngineRandom(int _Seed)
{
	Seed = _Seed;
	srand(Seed);
}

int GameEngineRandom::RandomInt(int _Min, int _Max)
{
	return (rand() % (_Max + 1 - _Min)) + _Min;
}

GameEngineRandom::~GameEngineRandom()
{
}




//===== 최종 삭제 주석 ========

// RandomInt() 함수 원리
// 맨 오른쪽 + _Min을 붙여야 최종으로 리턴해줄 숫자가 _Min 보다 작게 안나옴
// 이제  _Min에 랜덤숫자 rand()를 더하는데, 그 랜덤숫자는 더하고 나서 Max보다는 안크게 해주는 랜덤숫자여야함.
// 즉 정확히 말하자면 Min에 더할수 있는 랜덤수의 범위는 '0 ~ 크기차이(Max-Min)' 이다. 
// 
// 나머지 연산을 이용하면 랜덤수 rand() 의 범위를 내가 원하는 범위로 제한할 수 있음. 
// 랜덤숫자 rand() 에 나누는숫자를 나머지연산 하면 그 범위가 '0~나누는숫자-1'이 될것임. 
// 그렇다면 어떻게 뭘로 나눠줘야 나머지 범위가 '0 ~ (Max-Min)' 으로 되게 할까?
// 방정식 '나누는숫자-1 = (Max - Min)'을 풀면됨. -1 이항하면 '나누는숫자 = Max - Min + 1' 이됨.
// 
// rand() % (_Max - Min +1) 이 바로 _Min에 더할 수 있는 랜덤숫자의 범위인 것이다.
// 
// 번외 - (_Max - Min +1) 이 아니라 1을 뺸  (_Max - _Min)으로 나머지 연산하면 안되나? +1이 되게 거슬린다라고 느꼈는데
// 결론 - 그렇게 하면 랜덤숫자 결과에 Max는 절대 나올 수 없고 최대로 나올 수 있는 랜덤숫자가 Max-1이 되버림.

