#pragma once

// ���� : ��� �⺻���� �ൿ�� �����ϴ� Ŭ����
// �����ϴ� Ŭ����
class GameEngineObject
{
	friend class GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineObject();
	virtual ~GameEngineObject();

	// delete Function
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

	// �����ϰ�.
	virtual void Start() {}

	// �ൿ�Ѱ�.
	virtual void Update(float _Delta) {}

	// �׷�����.
	virtual void Render() {}

	// �����ȴ�.
	virtual void Release() {}

	void On()
	{
		IsUpdateValue = true;
	}

	void Off()
	{
		IsUpdateValue = false;
	}

	void Death()
	{
		IsDeathValue = true;
	}

	bool IsUpdate()
	{
		return true == IsUpdateValue && false == IsDeathValue;
	}

	virtual bool IsDeath()
	{
		return IsDeathValue;
	}

	void SetOrder(int _Order)
	{
		Order = _Order;
	}

	float GetLiveTime()
	{
		return LiveTime;
	}

	void ResetLiveTime()
	{
		LiveTime = 0.0f;
	}

protected:


private:
	float LiveTime = 0.0f;
	int Order = 0;
	bool IsUpdateValue = true; // �̰� false�� ����� �˴ϴ�.
	bool IsDeathValue = false; // �ƿ� �޸𸮿��� ���������� �;�.

	void AddLiveTime(float _DeltaTime)
	{
		LiveTime += _DeltaTime;
	}
};





// ========= ���� ���� �ּ� ===========

// int Order => ������Ʈ �켱����. ���������״� �̰� ��� Actor�� ���� ���������� �˷��ִ� ����.


//�Ѿ� ���� Object�� ���� �ð� ������ ������� �ϰ� �����״� �� ������Ʈ�� �󸶵��� ����־������� ���� delta time
// float LiveTime = 0.0f;
//float GetLiveTime()
//void ResetLiveTime()
