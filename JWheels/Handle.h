#pragma once

template <class T>
class Handle
{
public:
	Handle() :ptr(0), used(new int(1)) {}//默认构造函数，ptr不绑定任何指针，计数值初始化为1
	Handle(T* p) :ptr(p), used(1) {}//带指针参数的构造函数，ptr绑定到参数p,p应该为某个类克隆出来的对象指针，否则p依然有可能在handle不知情情况下被析构或复制
	Handle(const Handle& handle) :ptr(handle.ptr), used(handle.used) {}
	T* operator->() { return ptr; }
	T& operator&() { return *ptr; }
private:
	T* ptr;
	int* used;
};

