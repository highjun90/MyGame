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




//===== ���� ���� �ּ� ========

// RandomInt() �Լ� ����
// �� ������ + _Min�� �ٿ��� �������� �������� ���ڰ� _Min ���� �۰� �ȳ���
// ����  _Min�� �������� rand()�� ���ϴµ�, �� �������ڴ� ���ϰ� ���� Max���ٴ� ��ũ�� ���ִ� �������ڿ�����.
// �� ��Ȯ�� �����ڸ� Min�� ���Ҽ� �ִ� �������� ������ '0 ~ ũ������(Max-Min)' �̴�. 
// 
// ������ ������ �̿��ϸ� ������ rand() �� ������ ���� ���ϴ� ������ ������ �� ����. 
// �������� rand() �� �����¼��ڸ� ���������� �ϸ� �� ������ '0~�����¼���-1'�� �ɰ���. 
// �׷��ٸ� ��� ���� ������� ������ ������ '0 ~ (Max-Min)' ���� �ǰ� �ұ�?
// ������ '�����¼���-1 = (Max - Min)'�� Ǯ���. -1 �����ϸ� '�����¼��� = Max - Min + 1' �̵�.
// 
// rand() % (_Max - Min +1) �� �ٷ� _Min�� ���� �� �ִ� ���������� ������ ���̴�.
// 
// ���� - (_Max - Min +1) �� �ƴ϶� 1�� �A  (_Max - _Min)���� ������ �����ϸ� �ȵǳ�? +1�� �ǰ� �Ž����ٶ�� �����µ�
// ��� - �׷��� �ϸ� �������� ����� Max�� ���� ���� �� ���� �ִ�� ���� �� �ִ� �������ڰ� Max-1�� �ǹ���.

