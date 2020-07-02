#pragma once

//懒汉模式
class LazySingleton
{
public:
	static LazySingleton* GetInstance();
private:
	LazySingleton();//构造函数放到private，防止用户随意生成对象
	static LazySingleton* instance;//静态指针变量保存唯一的对象指针
};

LazySingleton* LazySingleton::instance = nullptr;
LazySingleton* LazySingleton:: GetInstance()//需要对象时再生成
{
	if (instance == nullptr)//只生成一次对象，非线程安全，可以加锁
		instance = new LazySingleton();
	return instance;
}


//饿汉模式
class HungrySingleton
{
public:
	static HungrySingleton* GetInstance();
private:
	HungrySingleton();
	static HungrySingleton* instance;
};

HungrySingleton* HungrySingleton::instance = new HungrySingleton();//开始就生成好对象
HungrySingleton* HungrySingleton::GetInstance()
{
	return instance;
}

class JSingleton
{
public:
	JSingleton& GetInstance();
private:
	JSingleton();
	static JSingleton instance;
};

JSingleton JSingleton::instance;//这里应该可以调用private的构造函数
JSingleton& JSingleton::GetInstance()
{	
	return instance;
}