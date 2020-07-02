#pragma once

//����ģʽ
class LazySingleton
{
public:
	static LazySingleton* GetInstance();
private:
	LazySingleton();//���캯���ŵ�private����ֹ�û��������ɶ���
	static LazySingleton* instance;//��ָ̬���������Ψһ�Ķ���ָ��
};

LazySingleton* LazySingleton::instance = nullptr;
LazySingleton* LazySingleton:: GetInstance()//��Ҫ����ʱ������
{
	if (instance == nullptr)//ֻ����һ�ζ��󣬷��̰߳�ȫ�����Լ���
		instance = new LazySingleton();
	return instance;
}


//����ģʽ
class HungrySingleton
{
public:
	static HungrySingleton* GetInstance();
private:
	HungrySingleton();
	static HungrySingleton* instance;
};

HungrySingleton* HungrySingleton::instance = new HungrySingleton();//��ʼ�����ɺö���
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

JSingleton JSingleton::instance;//����Ӧ�ÿ��Ե���private�Ĺ��캯��
JSingleton& JSingleton::GetInstance()
{	
	return instance;
}