#include "units-declarations.h"



struct UintStruct
{
	static inline void Func1();
	static void Func2();
	static void Func3();
};

void UintStruct::Func1()
{
	std::cout << "Unit1 : inline UnitStruct::Func1" << std::endl;
}

//inline int Inline_X = 30;

inline void InlineFunc()
{
	std::cout << "Unit3 : inline func" << std::endl;
}

void Unit3_Func()
{
	std::cout << "Unit3 : function" << std::endl;
	//std::cout << "inline x : " << Inline_X << std::endl;
	InlineFunc();
}
void UintStruct::Func3()
{
	std::cout << "Unit3 : UnitStruct::Func3" << std::endl;
	UintStruct::Func1();
}


