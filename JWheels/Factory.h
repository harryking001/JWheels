#pragma once
#include <iostream>
using std::cout;
using std::endl;

//������������Ƿ�װ���������
//BenzCar��BmwCar�඼�̳���Car��
class Car
{
public:
	virtual void Move() = 0;
};

class BenzCar :public Car
{
public:
	virtual void Move() { cout << "Benz is moving!" << endl; };
};

class BmwCar :public Car
{
public:
	virtual void Move() { cout << "Bmw is moving!" << endl; };
};

//BenzCarFactory��BmwCarFactory�඼�̳���CarFactory��
class CarFactory
{
public:
	virtual Car* ProduceCar() = 0;
};

class BenzCarFactory :public CarFactory
{
	virtual BenzCar* ProduceCar() { return new BenzCar(); };
};

class BmwCarFactory :public CarFactory
{
	virtual BmwCar* ProduceCar() { return new BmwCar(); };
};
