#include <iostream>

using namespace std;

class Car
{
public:
	Car()
	{
		cout << "Car�� �����մϴ�\n";
	}
	~Car()
	{
		cout << "Car�� �Ҹ�˴ϴ�\n";
	}

	virtual void OpenWindow()
	{
		cout << "â���� ���ϴ�\n";
	}
	virtual void ChangeGear()
	{
		cout << "�� �����մϴ�\n";
	}
};

class Spark : public Car
{
public:
	Spark()
	{
		cout << "Spark�� �����մϴ�\n";
	}
	~Spark()
	{
		cout << "����ũ�� �Ҹ�˴ϴ�\n";
	}

	void OpenWindow()
	{
		cout << "�������� â���� ���ϴ�\n";
	}
	void ChangeGear()
	{
		cout << "�������� �� �ٲߴϴ�\n";
	}
};

class Escalade : public Car
{
public:
	Escalade()
	{
		cout << "Escalade�� �����մϴ�\n";
	}
	~Escalade()
	{
		cout << "Escalade�� �Ҹ�˴ϴ�\n";
	}

	void OpenWindow()
	{
		cout << "�ڵ����� â���� ���ϴ�\n";
	}
	void ChangeGear()
	{
		cout << "�ڵ����� �� �ٲߴϴ�\n";
	}
};


//������ �Լ�
void main()
{
	int carNum = 1;
	

	Car** c;
	c = new Car*[carNum];
	c[0] = new Spark();
	//c[1] = new Escalade();	

	for (size_t i = 0; i < carNum; i++)
	{
		c[i]->OpenWindow();
		c[i]->ChangeGear();
		delete(c[i]);
	}
}