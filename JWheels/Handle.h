#pragma once

template <class T>
class Handle
{
public:
	Handle() :ptr(0), used(new int(1)) {}//Ĭ�Ϲ��캯����ptr�����κ�ָ�룬����ֵ��ʼ��Ϊ1
	Handle(T* p) :ptr(p), used(1) {}//��ָ������Ĺ��캯����ptr�󶨵�����p,pӦ��Ϊĳ�����¡�����Ķ���ָ�룬����p��Ȼ�п�����handle��֪������±���������
	Handle(const Handle& handle) :ptr(handle.ptr), used(handle.used) {}
	T* operator->() { return ptr; }
	T& operator&() { return *ptr; }
private:
	T* ptr;
	int* used;
};

