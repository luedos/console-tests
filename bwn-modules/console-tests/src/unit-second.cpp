#include "units-declarations.h"



struct UintStruct
{
	static void Func1()
	{
		std::cout << "Unit2 : UnitStruct::Func1" << std::endl;
	}
	static void Func2();
	static void Func3();
};



//inline int Inline_X = 20;

inline void InlineFunc()
{
	std::cout << "Unit2 : inline func" << std::endl;
}

void Unit2_Func()
{
	std::cout << "Unit2 : function" << std::endl;
	//std::cout << "inline x : " << Inline_X << std::endl;
	InlineFunc();
}
void UintStruct::Func2()
{
	std::cout << "Unit2 : UnitStruct::Func2" << std::endl;
	UintStruct::Func1();
}


