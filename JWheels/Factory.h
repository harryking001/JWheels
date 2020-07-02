#pragma once
#include <iostream>
using std::cout;
using std::endl;

//工厂类的作用是封装对象的生成
//BenzCar和BmwCar类都继承自Car类
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

//BenzCarFactory和BmwCarFactory类都继承自CarFactory类
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
