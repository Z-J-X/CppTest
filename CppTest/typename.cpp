#if 0
#include<iostream>
class MyArray
{
public:
	typedef int LengthType;
	LengthType t;
};

template<class T>
void MyMethod(T myarr)
{
	typedef  T::LengthType LengthType;
	LengthType length = myarr.t;
}
int main()
{
	MyArray a;
	a.t = 100;
	MyMethod(a);
}
#endif