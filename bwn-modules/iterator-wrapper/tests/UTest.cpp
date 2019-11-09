#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <random>
#include <ctime>
#include <list>
#include <forward_list>

#include "IteratorWrapper.h"

namespace test
{

class Uncanonical
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor from int.
	Uncanonical(uint32_t x = 0) noexcept
		: x_{ x }
	{}

	//
	// Public interface.
	//
public:
	uint32_t Get() const noexcept
	{
		return x_;
	}

	uint32_t x_;
};

constexpr uint32_t MaxNumber = 50;

static uint32_t GenUint()
{
	static std::mt19937 gen{static_cast<uint32_t>(std::time(0))};

	return gen();
}

template<typename IterT>
void GenContainer(IterT beg, IterT end)
{
	for (; beg != end; ++beg) {
		*beg = GenUint();
	}
}

template< typename TestedIterT, typename InitialIterT>
void AssertForwardIter(
	InitialIterT initial_beg,
	InitialIterT initial_end)
{
	TestedIterT postfix_it = initial_beg;
	TestedIterT postfix_end = initial_end;
	TestedIterT prefix_it = initial_beg;
	TestedIterT prefix_end = initial_end;

	REQUIRE(postfix_it != postfix_end);
	REQUIRE(prefix_it != prefix_end);

	REQUIRE(std::distance(prefix_it, prefix_end) == std::distance(initial_beg, initial_end));

	for(InitialIterT it = initial_beg; it != initial_end;)
	{
		REQUIRE((*it).Get() == (*(postfix_it++)).Get());
		REQUIRE(it->Get() == prefix_it->Get());

		if (std::distance(it, initial_end) > 1)
		{
			REQUIRE((++it)->Get() == (++prefix_it)->Get());
		}
		else
		{
			++prefix_it;
			++it;
		}
	}

	REQUIRE(postfix_it == postfix_end);
	REQUIRE(prefix_it == prefix_end);
}

template< typename TestedIterT, typename InitialIterT>
void AssertBackwardIter(
	InitialIterT initial_beg,
	InitialIterT initial_end)
{
	TestedIterT postfix_beg = initial_beg;
	TestedIterT postfix_it = initial_end;
	TestedIterT prefix_beg = initial_beg;
	TestedIterT prefix_it = initial_end;

	REQUIRE(postfix_it != postfix_beg);
	REQUIRE(prefix_it != prefix_beg);

	REQUIRE(std::distance(postfix_beg, postfix_it) == std::distance(initial_beg, initial_end));

	InitialIterT it = initial_end;

	do
	{
		if (it != initial_end) {
			REQUIRE(it->Get() == (postfix_it--)->Get());
		}
		else {
			postfix_it--;
		}

		REQUIRE((--it)->Get() == (--prefix_it)->Get());

	} while(it != initial_beg);

	REQUIRE(postfix_it == postfix_beg);
	REQUIRE(prefix_it == prefix_beg);
}

template< typename TestedIterT, typename InitialIterT>
void AssertRandomForwardIter(
	InitialIterT initial_beg,
	InitialIterT initial_end)
{
	TestedIterT tested_it = initial_beg;
	TestedIterT tested_end = initial_end;

	REQUIRE(tested_it != tested_end);

	REQUIRE(std::distance(tested_it, tested_end) == std::distance(initial_beg, initial_end));

	using dist_t = typename std::iterator_traits<InitialIterT>::difference_type;

	const dist_t total_distance = std::distance(initial_beg, initial_end);

	if (total_distance < 2) {
		return;
	}

	for (uint32_t i = 0; i < 5; ++i)
	{
		tested_it = initial_beg;

		dist_t local_distance = total_distance;

		for(InitialIterT it = initial_beg; it != initial_end;)
		{
			REQUIRE(it->Get() == tested_it->Get());

			dist_t delta = GenUint() % (total_distance / 5 + 1) + 1;
			if (delta > local_distance) {
				delta = local_distance;
			}

			local_distance -= delta;
			tested_it += delta;
			it += delta;
		}

		REQUIRE(tested_it == tested_end);
	}
}

}

TEST_CASE("ForwardIterator tests")
{
	SECTION("Vector")
	{
		std::vector<test::Uncanonical> template_vec;
		template_vec.resize(test::MaxNumber);

		std::vector<test::Uncanonical>::iterator beg = template_vec.begin();
		std::vector<test::Uncanonical>::iterator end = template_vec.end();

		test::GenContainer(beg, end);

		test::AssertForwardIter<bwn::ForwardIterator<test::Uncanonical>>(beg, end);
	}
	SECTION("Forward List")
	{
		std::forward_list<test::Uncanonical> template_list;
		template_list.resize(test::MaxNumber);
	
		std::forward_list<test::Uncanonical>::iterator beg = template_list.begin();
		std::forward_list<test::Uncanonical>::iterator end = template_list.end();
	
		test::GenContainer(beg, end);
	
		test::AssertForwardIter<bwn::ForwardIterator<test::Uncanonical>>(beg, end);
	}
	SECTION("Pointer")
	{
		test::Uncanonical template_arr[test::MaxNumber + 1];
	
		test::Uncanonical* beg = template_arr;
		test::Uncanonical* end = template_arr + test::MaxNumber;
	
		test::GenContainer(beg, end);
	
		test::AssertForwardIter<bwn::ForwardIterator<test::Uncanonical>>(beg, end);
	}
}

TEST_CASE("BidirectionalIterator tests")
{
	SECTION("Vector")
	{
		std::vector<test::Uncanonical> template_vec;
		template_vec.resize(test::MaxNumber);

		std::vector<test::Uncanonical>::iterator beg = template_vec.begin();
		std::vector<test::Uncanonical>::iterator end = template_vec.end();

		test::GenContainer(beg, end);

		test::AssertForwardIter<bwn::BidirectionalIterator<test::Uncanonical>>(beg, end);
		test::AssertBackwardIter<bwn::BidirectionalIterator<test::Uncanonical>>(beg, end);
	}
	SECTION("Both side List")
	{
		std::list<test::Uncanonical> template_list;
		template_list.resize(test::MaxNumber);

		std::list<test::Uncanonical>::iterator beg = template_list.begin();
		std::list<test::Uncanonical>::iterator end = template_list.end();

		test::GenContainer(beg, end);

		test::AssertForwardIter<bwn::BidirectionalIterator<test::Uncanonical>>(beg, end);
		test::AssertBackwardIter<bwn::BidirectionalIterator<test::Uncanonical>>(beg, end);
	}
	SECTION("Pointer")
	{
		test::Uncanonical template_arr[test::MaxNumber + 1];

		test::Uncanonical* beg = template_arr;
		test::Uncanonical* end = template_arr + test::MaxNumber;

		test::GenContainer(beg, end);

		test::AssertForwardIter<bwn::BidirectionalIterator<test::Uncanonical>>(beg, end);
		test::AssertBackwardIter<bwn::BidirectionalIterator<test::Uncanonical>>(beg, end);
	}
}

TEST_CASE("RandomAccessIterator tests")
{
	SECTION("Vector")
	{
		std::vector<test::Uncanonical> template_vec;
		template_vec.resize(test::MaxNumber);

		std::vector<test::Uncanonical>::iterator beg = template_vec.begin();
		std::vector<test::Uncanonical>::iterator end = template_vec.end();

		test::GenContainer(beg, end);

		test::AssertForwardIter<bwn::RandomAccessIterator<test::Uncanonical>>(beg, end);
		test::AssertBackwardIter<bwn::RandomAccessIterator<test::Uncanonical>>(beg, end);
		test::AssertRandomForwardIter<bwn::RandomAccessIterator<test::Uncanonical>>(beg, end);
	}
	SECTION("Pointer")
	{
		test::Uncanonical template_arr[test::MaxNumber + 1];

		test::Uncanonical* beg = template_arr;
		test::Uncanonical* end = template_arr + test::MaxNumber;

		test::GenContainer(beg, end);

		test::AssertForwardIter<bwn::RandomAccessIterator<test::Uncanonical>>(beg, end);
		test::AssertBackwardIter<bwn::RandomAccessIterator<test::Uncanonical>>(beg, end);
		test::AssertRandomForwardIter<bwn::RandomAccessIterator<test::Uncanonical>>(beg, end);
	}
}