#include "TypeName.h"
#include "units-declarations.h"

class UintStructCl
{

	static void Func1()
	{
		std::cout << "Unit1 : inline UnitStruct::Func1" << std::endl;
	}
	static void Func2();
	static void Func3();
};

struct UintStruct
{

	static void Func1()
	{
		std::cout << "Unit1 : inline UnitStruct::Func1" << std::endl;
	}
	static void Func2();
	static void Func3();
};



//inline int Inline_X = 10;

inline void InlineFunc()
{
	std::cout << "Unit1 : inline func" << std::endl;
}

void Unit1_Func()
{
	std::cout << "Unit1 : function" << std::endl;
	//std::cout << "inline x : " << Inline_X << std::endl;
	InlineFunc();
}


//void UintStruct::Func1()
//{
//	std::cout << "Unit1 : UnitStruct::Func1" << std::endl;
//}
