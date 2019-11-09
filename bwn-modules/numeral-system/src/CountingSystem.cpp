#include "CountingSystem.h"

using namespace bwn;

std::string CountingSystem::ToString() const
{
	std::string myStr;
	
	int localI = 1;
	int i = 0;
	for (; localI < order; localI *= 10, ++i)
	{}

	myStr.reserve(myValue.size() * (i + 1));

	for (i = myValue.size() - 1; i >= 0; --i)
	{
		std::string localS = std::to_string(myValue[i]) + '|';
		myStr = myStr.append(localS);
	}

	return myStr;
}

int CountingSystem::GetSize() const
{
	CountingSystem* cheat = (CountingSystem*)this;

	for (int i = myValue.size(); i >= 0; --i)
		if (myValue[i] == 0)
			cheat->myValue.pop_back();
		else
			break;

	return myValue.size();
}

CountingSystem::CountingSystem(unsigned int inOrder)
{
	if (inOrder > 45000)
		order = 45000;
	else if (inOrder < 2)
		order = 2;
	else
		order = inOrder;

}

CountingSystem::CountingSystem(unsigned int inOrder, int inTenCS)
	: CountingSystem(inOrder)
{
	if (inTenCS == 0)
		return;

	*this += inTenCS;
}

CountingSystem::CountingSystem(const CountingSystem& inCS)
{
	order = inCS.order;

	myValue = inCS.myValue;
}

void CountingSystem::operator=(const CountingSystem& inCS)
{
	order = inCS.order;

	myValue = inCS.myValue;
}

void CountingSystem::Normalize()
{
	for (int i = 0; i < myValue.size(); ++i)
	{
		if (myValue[i] >= order || myValue[i] <= -order)
		{
			if (i < myValue.size() - 1)
				myValue[i + 1] += myValue[i] / order;
			else
				myValue.push_back(myValue[i] / order);

			myValue[i] = myValue[i] % order;
		}
	}

	for (int i = myValue.size() - 1; i >= 0; --i)
		if (myValue[i] == 0)
			myValue.pop_back();
		else
			break;

	if (myValue.size() > 1)
	{
		if(myValue.back() < 0)
			for(int i = myValue.size() - 2; i >= 0; --i)
				if (myValue[i] > 0)
				{
					if (myValue[i + 1] != 0)
					{
						myValue[i] -= order;
						++myValue[i + 1];
					}
					else
					{
						int localI = i + 1;

						while (localI < myValue.size() && myValue[localI] == 0)
							++localI;

						if (localI == myValue.size())
						{
							continue;
						}
						
						while (localI > i)
						{
							++myValue[localI];
							myValue[localI - 1] -= order;

							--localI;
						}

					}
				}

		if (myValue.back() > 0)
			for (int i = myValue.size() - 2; i >= 0; --i)
				if (myValue[i] < 0)
				{

					if (myValue[i + 1] != 0)
					{
						myValue[i] += order;
						--myValue[i + 1];
					}
					else
					{
						int localI = i + 1;

						while (localI < myValue.size() && myValue[localI] == 0)
							++localI;

						if (localI == myValue.size())
						{
							continue;
						}

						while (localI > i)
						{
							--myValue[localI];
							myValue[localI - 1] += order;

							--localI;
						}

					}
				}
	}


	for (int i = myValue.size() - 1 ; i >= 0; --i)
		if (myValue[i] == 0)
			myValue.pop_back();
		else
			break;
}

void CountingSystem::ValueShift(unsigned int inShift)
{
	if (inShift == 0)
		return;

	//int initSize = myValue.size();

	myValue.resize(myValue.size() + inShift);
	
	for (int i = myValue.size() - 1; i >= inShift; --i)
		myValue[i] = myValue[i - inShift];

	for (int i = 0; i < inShift; ++i)
		myValue[i] = 0;

}

CountingSystem CountingSystem::GetNewOrder(unsigned int inOrder)
{
	CountingSystem retCS = *this;

	retCS.ChangeOrder(inOrder);

	return retCS;
}

void CountingSystem::ChangeOrder(unsigned int inOrder)
{
	if (inOrder > 45000)
		inOrder = 45000;
	else if (inOrder < 2)
		inOrder = 2;
	
	CountingSystem newOne(inOrder);

	CountingSystem retCS(inOrder);

	for (int i = 0; i < myValue.size(); ++i)
	{
		newOne.myValue.clear();

		newOne.myValue.push_back(myValue[i]);

		for (int ii = 0; ii < i; ++ii)
			newOne *= (order);

		retCS += newOne;
	}

	myValue = retCS.myValue;

	order = inOrder;
}

CountingSystem CountingSystem::operator+ (const CountingSystem& inCS)
{
	CountingSystem ret(inCS);

	if (order != inCS.order)
	{
		ret.ChangeOrder(order);
	}

	if (ret.myValue.size() < myValue.size())
		ret.myValue.resize(myValue.size());

	for (int i = 0; i < myValue.size(); ++i)
	{
		ret.myValue[i] += myValue[i];
	}

	ret.Normalize();

	return ret;
}

void CountingSystem::operator+=(const CountingSystem& inCS)
{
	if (inCS.order != order)
	{
		CountingSystem localCS = inCS;

		localCS.ChangeOrder(order);

		if (myValue.size() < localCS.myValue.size())
			myValue.resize(localCS.myValue.size());

		for (int i = 0; i < localCS.myValue.size(); ++i)
			myValue[i] += localCS.myValue[i];
	}
	else
	{
		if (myValue.size() < inCS.myValue.size())
			myValue.resize(inCS.myValue.size());

		for (int i = 0; i < inCS.myValue.size(); ++i)
			myValue[i] += inCS.myValue[i];
	}

	Normalize();

}

void CountingSystem::operator+=(int inInt)
{
	if (myValue.size() == 0)
		myValue.resize(1);

	if (2147483647 - (inInt < 0 ? -inInt : inInt) < order)
	{
		if (myValue.size() < 2)
			myValue.resize(2);

		myValue[1] += inInt / order;
		myValue[0] += inInt % order;
	}
	else
	{
		myValue[0] += inInt;
	}

	Normalize();
}

CountingSystem CountingSystem::operator* (const CountingSystem& inCS)
{
	CountingSystem* inSecond = (CountingSystem*)&inCS;

	bool TestBool = false;

	if (inSecond->order != order)
	{
		inSecond = new CountingSystem(inCS);
		inSecond->ChangeOrder(order);
		TestBool = true;
	}

	int localI = inSecond->myValue.size() + myValue.size() + (myValue.back() * inSecond->myValue.back() >= order ? 1 : 0);

	
		
	CountingSystem retCS(order);

	retCS.myValue.reserve(localI);

	CountingSystem localCS(order);

	localCS.myValue.reserve(localI);

	for (int i = 0; i < inSecond->myValue.size(); ++i)
	{
		localCS.myValue = myValue;

		for (int ii = 0; ii < localCS.myValue.size(); ++ii)
			localCS.myValue[ii] *= inSecond->myValue[i];

		localCS.Normalize();

		localCS.ValueShift(i);

		retCS += localCS;
	}

	
	if (TestBool)
		delete inSecond;

	return retCS;
}

void CountingSystem::operator*=(const CountingSystem& inCS)
{
	CountingSystem* inSecond = (CountingSystem*)&inCS;

	bool TestBool = false;

	if (inSecond->order != order)
	{
		inSecond = new CountingSystem(inCS);
		inSecond->ChangeOrder(order);
		TestBool = true;
	}

	int localI = inSecond->myValue.size() + inCS.myValue.size() + (myValue.back() * inSecond->myValue.back() >= order ? 1 : 0);



	CountingSystem retCS(order);

	retCS.myValue.resize(localI);

	CountingSystem localCS(order);

	localCS.myValue.reserve(localI);

	for (int i = 0; i < inSecond->myValue.size(); ++i)
	{
		localCS.myValue = myValue;

		for (int ii = 0; ii < localCS.myValue.size(); ++ii)
			localCS.myValue[ii] *= inSecond->myValue[i];

		localCS.Normalize();

		localCS.ValueShift(i);

		retCS += localCS;
	}


	if (TestBool)
		delete inSecond;

	myValue = retCS.myValue;
}

void CountingSystem::operator*=(int inInt)
{
	if (2147483648 / inInt < order)
	{
		CountingSystem localCS(order, inInt);

		*this *= localCS;
	}
	else
	{
		for (int i = 0; i < myValue.size(); ++i)
			myValue[i] *= inInt;

		Normalize();
	}
}

CountingSystem CountingSystem::operator- (const CountingSystem& inCS)
{
	CountingSystem ret(inCS);

	if (order != inCS.order)
	{
		ret.ChangeOrder(order);
	}

	if (ret.myValue.size() < myValue.size())
		ret.myValue.resize(myValue.size());

	for (int i = 0; i < myValue.size(); ++i)
	{
		ret.myValue[i] *= -1;
		ret.myValue[i] += myValue[i];
	}

	ret.Normalize();

	return ret;
}

void CountingSystem::operator-=(const CountingSystem& inCS)
{
	if (inCS.order != order)
	{
		CountingSystem localCS = inCS;

		localCS.ChangeOrder(order);

		if (myValue.size() < localCS.myValue.size())
			myValue.resize(localCS.myValue.size());

		for (int i = 0; i < localCS.myValue.size(); ++i)
		
			myValue[i] -= localCS.myValue[i];
	}
	else
	{
		if (myValue.size() < inCS.myValue.size())
			myValue.resize(inCS.myValue.size());

		for (int i = 0; i < inCS.myValue.size(); ++i)
			myValue[i] -= inCS.myValue[i];
	}

	Normalize();
}

void CountingSystem::operator-=(int inInt)
{
	if (myValue.size() == 0)
		myValue.resize(1);

	if (2147483647 - (inInt < 0 ? -inInt : inInt) < order)
	{
		if (myValue.size() < 2)
			myValue.resize(2);

		myValue[1] -= inInt / order;
		myValue[0] -= inInt % order;
	}
	else
	{
		myValue[0] -= inInt;
	}

	Normalize();
}

CountingSystem CountingSystem::operator/ (const CountingSystem& inCS)
{
	{
		bool testBool = true;

		for(int i = inCS.myValue.size() - 1; i >= 0; ++i)
			if (inCS.myValue[i] != 0)
			{
				testBool = false;
				break;
			}
		if (testBool)
			return *this;

	}


	CountingSystem* inSecond = (CountingSystem*)&inCS;
	bool TestBool = false;

	if (order != inSecond->order)
	{
		inSecond = new CountingSystem(inCS);
		inSecond->ChangeOrder(order);
		TestBool = true;
	}

	if (*this < *inSecond)
	{
		if (TestBool)
			delete inSecond;

		return CountingSystem(order);
	}

	CountingSystem retCS(order);

	retCS.myValue.clear();

	retCS.myValue.reserve(myValue.size() - inSecond->myValue.size() + 1);

	CountingSystem testCS(order);

	testCS.myValue.clear();

	testCS.myValue.reserve(inSecond->myValue.size() + 1);

	CountingSystem localCS(order);

	localCS.myValue.clear();

	localCS.myValue.reserve(inSecond->myValue.size() + 2);

	for (int i = 1; i < inSecond->myValue.size(); ++i)
		testCS.myValue.push_back(myValue[myValue.size() - inSecond->myValue.size() + i]);
	

	for (int i = myValue.size() - inSecond->myValue.size(); i >= 0; --i)
	{
		testCS.myValue.insert(testCS.myValue.begin(), myValue[i]);

		if (testCS < *inSecond)
		{
			retCS.myValue.push_back(0);

			continue;
		}
	
		int Min = 1;
		int Max = order;

		int Mid;

		while (Max - Min > 1)
		{
			Mid = (Max + Min) / 2;

			localCS.myValue = inSecond->myValue;
			localCS *= Mid;

			if (localCS <= testCS)
			{
				Min = Mid;
				if (localCS == testCS)
					break;
			}
			else
				Max = Mid;
		}

		retCS.myValue.push_back(Min);

		localCS.myValue = inSecond->myValue;

		localCS *= Min;

		testCS -= localCS;

	}

	std::reverse(retCS.myValue.begin(), retCS.myValue.end());

	retCS.Normalize();

	if (TestBool)
		delete inSecond;

	return retCS;
}

void CountingSystem::operator/=(const CountingSystem& inCS)
{
	{
		bool testBool = true;

		for (int i = inCS.myValue.size() - 1; i >= 0; ++i)
			if (inCS.myValue[i] != 0)
			{
				testBool = false;
				break;
			}
		if (testBool)
			return;

	}

	CountingSystem* inSecond = (CountingSystem*)&inCS;
	bool TestBool = false;

	if (order != inSecond->order)
	{
		inSecond = new CountingSystem(inCS);
		inSecond->ChangeOrder(order);
		TestBool = true;
	}

	if (*this < *inSecond)
	{
		if (TestBool)
			delete inSecond;

		myValue.clear();
	}

	CountingSystem retCS(order);

	retCS.myValue.clear();

	retCS.myValue.reserve(myValue.size() - inSecond->myValue.size() + 1);

	CountingSystem testCS(order);

	testCS.myValue.clear();

	testCS.myValue.reserve(inSecond->myValue.size() + 1);

	CountingSystem localCS(order);

	localCS.myValue.clear();

	localCS.myValue.reserve(inSecond->myValue.size() + 2);

	for (int i = 1; i < inSecond->myValue.size(); ++i)
		testCS.myValue.push_back(myValue[myValue.size() - inSecond->myValue.size() + i]);


	for (int i = myValue.size() - inSecond->myValue.size(); i >= 0; --i)
	{
		testCS.myValue.insert(testCS.myValue.begin(), myValue[i]);

		if (testCS < *inSecond)
		{
			retCS.myValue.push_back(0);

			continue;
		}

		int Min = 1;
		int Max = order;

		int Mid;

		while (Max - Min > 1)
		{
			Mid = (Max + Min) / 2;

			localCS.myValue = inSecond->myValue;
			localCS *= Mid;

			if (localCS <= testCS)
			{
				Min = Mid;
				if (localCS == testCS)
					break;
			}
			else
				Max = Mid;
		}

		retCS.myValue.push_back(Min);

		localCS.myValue = inSecond->myValue;

		localCS *= Min;

		testCS -= localCS;

	}

	std::reverse(retCS.myValue.begin(), retCS.myValue.end());

	retCS.Normalize();

	if (TestBool)
		delete inSecond;

	myValue = retCS.myValue;
}

void CountingSystem::operator/=(int inInt)
{
	if (inInt == 0)
		return;

	CountingSystem inSecond(order, inInt);


	if (*this < inSecond)
	{
		myValue.clear();
	}

	CountingSystem retCS(order);

	retCS.myValue.clear();

	retCS.myValue.reserve(myValue.size() - inSecond.myValue.size() + 1);

	CountingSystem testCS(order);

	testCS.myValue.clear();

	testCS.myValue.reserve(inSecond.myValue.size() + 1);

	CountingSystem localCS(order);

	localCS.myValue.clear();

	localCS.myValue.reserve(inSecond.myValue.size() + 2);

	for (int i = 1; i < inSecond.myValue.size(); ++i)
		testCS.myValue.push_back(myValue[myValue.size() - inSecond.myValue.size() + i]);


	for (int i = myValue.size() - inSecond.myValue.size(); i >= 0; --i)
	{
		testCS.myValue.insert(testCS.myValue.begin(), myValue[i]);

		if (testCS < inSecond)
		{
			retCS.myValue.push_back(0);

			continue;
		}

		int Min = 1;
		int Max = order;

		int Mid;

		while (Max - Min > 1)
		{
			Mid = (Max + Min) / 2;

			localCS.myValue = inSecond.myValue;
			localCS *= Mid;

			if (localCS <= testCS)
			{
				Min = Mid;
				if (localCS == testCS)
					break;
			}
			else
				Max = Mid;
		}

		retCS.myValue.push_back(Min);

		localCS.myValue = inSecond.myValue;

		localCS *= Min;

		testCS -= localCS;

	}

	std::reverse(retCS.myValue.begin(), retCS.myValue.end());

	retCS.Normalize();
	
	myValue = retCS.myValue;
}

bool CountingSystem::operator>(const CountingSystem& inCS)
{
	if (order != inCS.order)
	{
		CountingSystem localCS(inCS);

		localCS.ChangeOrder(order);

		if (myValue.size() > localCS.myValue.size())
			return myValue.back() > 0;

		if (myValue.size() < localCS.myValue.size())
			return myValue.back() < 0;

		for (int i = myValue.size() - 1; i >= 0; --i)
		{
			if (myValue[i] == localCS.myValue[i])
				continue;

			if (myValue[i] > localCS.myValue[i])
				return true;

			if (myValue[i] < localCS.myValue[i])
				return false;
		}

		
	}
	else
	{
		if (myValue.size() > inCS.myValue.size())
			return myValue.back() > 0;

		if (myValue.size() < inCS.myValue.size())
			return myValue.back() < 0;

		for (int i = myValue.size() - 1; i >= 0; --i)
		{
			if (myValue[i] == inCS.myValue[i])
				continue;

			if (myValue[i] > inCS.myValue[i])
				return true;

			if (myValue[i] < inCS.myValue[i])
				return false;
		}
	}

	return false;
}

bool CountingSystem::operator<(const CountingSystem& inCS)
{
	if (order != inCS.order)
	{
		CountingSystem localCS(inCS);

		localCS.ChangeOrder(order);

		if (myValue.size() > localCS.myValue.size())
			return myValue.back() < 0;

		if (myValue.size() < localCS.myValue.size())
			return myValue.back() > 0;

		for (int i = myValue.size() - 1; i >= 0; --i)
		{
			if (myValue[i] == localCS.myValue[i])
				continue;

			if (myValue[i] > localCS.myValue[i])
				return false;

			if (myValue[i] < localCS.myValue[i])
				return true;
		}


	}
	else
	{
		if (myValue.size() > inCS.myValue.size())
			return myValue.back() < 0;

		if (myValue.size() < inCS.myValue.size())
			return myValue.back() > 0;

		for (int i = myValue.size() - 1; i >= 0; --i)
		{
			if (myValue[i] == inCS.myValue[i])
				continue;

			if (myValue[i] > inCS.myValue[i])
				return false;

			if (myValue[i] < inCS.myValue[i])
				return true;
		}
	}

	return false;
}

bool CountingSystem::operator>=(const CountingSystem& inCS)
{
	return !(*this < inCS);
}

bool CountingSystem::operator<=(const CountingSystem& inCS)
{
	return !(*this > inCS);
}

bool CountingSystem::operator==(const CountingSystem& inCS)
{
	if (order != inCS.order)
	{
		CountingSystem localCS(inCS);

		localCS.ChangeOrder(order);

		if (myValue.size() != localCS.myValue.size())
			return false;

		for (int i = myValue.size() - 1; i >= 0; --i)
		{
			if (myValue[i] != localCS.myValue[i])
				false;

		}


	}
	else
	{
		if (myValue.size() != inCS.myValue.size())
			return false;

		for (int i = myValue.size() - 1; i >= 0; --i)
		{
			if (myValue[i] != inCS.myValue[i])
				false;
		}
	}

	return true;
}

bool CountingSystem::operator!=(const CountingSystem& inCS)
{
	return !(*this == inCS);
}

void CountingSystem::BreakZeroEnd()
{
	for (int i = myValue.size() - 1; i >= 0; --i)
		if (myValue[i] == 0)
			myValue.pop_back();
		else
			break;
}