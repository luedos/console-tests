#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "NumeralSystem.h"

namespace test
{

constexpr int64_t row_number = 355345211;

static const std::vector<bwn::NumeralSystem::Digit> correct10{
		1,1,2,5,4,3,5,5,3
};

static const std::vector<bwn::NumeralSystem::Digit> correct2{
		1,1,0,1,1,1,0,0,1,1,0,0,0,1,0,0,0,1,1,1,0,1,0,0,1,0,1,0,1
};

static void AssertBase10(const bwn::NumeralSystem& number, bool positive)
{
	REQUIRE(number.GetLength() == correct10.size());
	for (std::size_t i = 0; i < correct10.size(); ++i) {
		REQUIRE((correct10[i] * (positive * 2 - 1)) == number[i]);
	}
}

static void AssertBase2(const bwn::NumeralSystem& number, bool positive)
{
	REQUIRE(number.GetLength() == correct2.size());
	for (std::size_t i = 0; i < correct2.size(); ++i) {
		REQUIRE((correct2[i] * (positive * 2 - 1)) == number[i]);
	}
}

}

TEST_CASE("Creation")
{
	SECTION("Basic constructor")
	{
		bwn::NumeralSystem number{ 10 };

		REQUIRE(!number);
		REQUIRE(number.GetLength() == 0);
	}

	SECTION("Based 10 system")
	{
		bwn::NumeralSystem positive{ 10, test::row_number };
		bwn::NumeralSystem negative{ 10, -test::row_number };

		test::AssertBase10(positive, true);
		test::AssertBase10(negative, false);
	}

	SECTION("Based 2 system")
	{
		bwn::NumeralSystem positive{ 2, test::row_number };
		bwn::NumeralSystem negative{ 2, -test::row_number };

		test::AssertBase2(positive, true);
		test::AssertBase2(negative, false);
	}

	SECTION("Copy construction")
	{
		bwn::NumeralSystem base{ 10, test::row_number };

		bwn::NumeralSystem derived = base;

		REQUIRE(base.GetLength() == derived.GetLength());
		for (std::size_t i = 0; i < base.GetLength(); ++i) {
			REQUIRE(base[i] == derived[i]);
		}
	}

	SECTION("Move construction")
	{
		bwn::NumeralSystem base{ 10, test::row_number };

		bwn::NumeralSystem derived = std::move(base);

		REQUIRE(!base);
		REQUIRE(base.GetLength() == 0);

		test::AssertBase10(derived, true);
	}
}

TEST_CASE("Changing numeral systems")
{
	SECTION("Base 10 to base 2")
	{
		bwn::NumeralSystem number{ 10, test::row_number };

		number.ChangeBase(2);

		test::AssertBase2(number, true);
	}

	SECTION("Base 2 to base 10")
	{
		bwn::NumeralSystem number{ 2, test::row_number };

		number.ChangeBase(10);

		test::AssertBase10(number, true);
	}

	SECTION("Copy assignment")
	{
		bwn::NumeralSystem base{ 2, test::row_number };

		bwn::NumeralSystem derived{ 10 };

		derived = base;

		test::AssertBase10(derived, true);
	}

	SECTION("Move assignment")
	{
		bwn::NumeralSystem base{ 10, test::row_number };

		bwn::NumeralSystem derived{ 2 };

		derived = std::move(base);

		REQUIRE(!base);
		REQUIRE(base.GetLength() == 0);

		test::AssertBase2(derived, true);
	}
}

TEST_CASE("Comparison")
{
	SECTION("Equal positive")
	{
		bwn::NumeralSystem first10{ 10, test::row_number };
		bwn::NumeralSystem second10{ 10, test::row_number };
		REQUIRE(first10 == first10);

		bwn::NumeralSystem first2{ 2, test::row_number };
		bwn::NumeralSystem second2{ 2, test::row_number };
		REQUIRE(first2 == first2);

		REQUIRE(first10 == second10);
		REQUIRE(first2 == second2);
		REQUIRE(first10 == first2);
		REQUIRE(first10 == second2);

		REQUIRE(first10 <= second10);
		REQUIRE(first2 <= second2);
		REQUIRE(first10 <= first2);
		REQUIRE(first10 <= second2);

		REQUIRE(first10 >= second10);
		REQUIRE(first2 >= second2);
		REQUIRE(first10 >= first2);
		REQUIRE(first10 >= second2);

	}

	SECTION("Equal positive")
	{
		bwn::NumeralSystem first10{ 10, -test::row_number };
		bwn::NumeralSystem second10{ 10, -test::row_number };
		REQUIRE(first10 == first10);

		bwn::NumeralSystem first2{ 2, -test::row_number };
		bwn::NumeralSystem second2{ 2, -test::row_number };
		REQUIRE(first2 == first2);

		REQUIRE(first10 == second10);
		REQUIRE(first2 == second2);
		REQUIRE(first10 == first2);
		REQUIRE(first10 == second2);

		REQUIRE(first10 <= second10);
		REQUIRE(first2 <= second2);
		REQUIRE(first10 <= first2);
		REQUIRE(first10 <= second2);

		REQUIRE(first10 >= second10);
		REQUIRE(first2 >= second2);
		REQUIRE(first10 >= first2);
		REQUIRE(first10 >= second2);
	}

	SECTION("Unequal positives")
	{
		bwn::NumeralSystem less10{ 10, test::row_number - 1 };
		bwn::NumeralSystem greater10{ 10, test::row_number + 1 };

		bwn::NumeralSystem less2{ 10, test::row_number - 1 };
		bwn::NumeralSystem greater2{ 10, test::row_number + 1 };

		REQUIRE(less10 != greater10);
		REQUIRE(less2 != greater2);
		REQUIRE(less10 != greater2);
		REQUIRE(less2 != greater10);

		REQUIRE(less10 < greater10);
		REQUIRE(less2 < greater2);
		REQUIRE(less10 < greater2);
		REQUIRE(less2 < greater10);

		REQUIRE(greater10 > less10);
		REQUIRE(greater2 > less2);
		REQUIRE(greater2 > less10);
		REQUIRE(greater10 > less2);

		REQUIRE(less10 <= greater10);
		REQUIRE(less2 <= greater2);
		REQUIRE(less10 <= greater2);
		REQUIRE(less2 <= greater10);

		REQUIRE(greater10 >= less10);
		REQUIRE(greater2 >= less2);
		REQUIRE(greater2 >= less10);
		REQUIRE(greater10 >= less2);
	}

	SECTION("Unequal negatives")
	{
		bwn::NumeralSystem less10{ 10, -test::row_number - 1 };
		bwn::NumeralSystem greater10{ 10, -test::row_number + 1 };

		bwn::NumeralSystem less2{ 10, -test::row_number - 1 };
		bwn::NumeralSystem greater2{ 10, -test::row_number + 1 };

		REQUIRE(less10 != greater10);
		REQUIRE(less2 != greater2);
		REQUIRE(less10 != greater2);
		REQUIRE(less2 != greater10);

		REQUIRE(less10 < greater10);
		REQUIRE(less2 < greater2);
		REQUIRE(less10 < greater2);
		REQUIRE(less2 < greater10);

		REQUIRE(greater10 > less10);
		REQUIRE(greater2 > less2);
		REQUIRE(greater2 > less10);
		REQUIRE(greater10 > less2);

		REQUIRE(less10 <= greater10);
		REQUIRE(less2 <= greater2);
		REQUIRE(less10 <= greater2);
		REQUIRE(less2 <= greater10);

		REQUIRE(greater10 >= less10);
		REQUIRE(greater2 >= less2);
		REQUIRE(greater2 >= less10);
		REQUIRE(greater10 >= less2);
	}
}

TEST_CASE("Operations")
{
	constexpr int64_t first_row = 514229;
	constexpr int64_t second_row = 233;

	bwn::NumeralSystem first_positive10{ 10, first_row };
	bwn::NumeralSystem second_positive10{ 10, second_row };
	bwn::NumeralSystem first_negative10{ 10, -first_row };
	bwn::NumeralSystem second_negative10{ 10, -second_row };

	bwn::NumeralSystem first_positive2{ 2, first_row };
	bwn::NumeralSystem second_positive2{ 2, second_row };
	bwn::NumeralSystem first_negative2{ 2, -first_row };
	bwn::NumeralSystem second_negative2{ 2, -second_row };

	SECTION("Addition")
	{
		REQUIRE(first_positive10 + second_positive10 == bwn::NumeralSystem{ 10, first_row + second_row });
		REQUIRE(first_positive2 + second_positive10 == bwn::NumeralSystem{ 2, first_row + second_row });
		REQUIRE(first_positive10 + second_positive2 == bwn::NumeralSystem{ 10, first_row + second_row });
		REQUIRE(first_positive2 + second_positive2 == bwn::NumeralSystem{ 2, first_row + second_row });

		REQUIRE(first_positive10 + second_negative10 == bwn::NumeralSystem{ 10, first_row - second_row });
		REQUIRE(first_positive2 + second_negative10 == bwn::NumeralSystem{ 2, first_row - second_row });
		REQUIRE(first_positive10 + second_negative2 == bwn::NumeralSystem{ 10, first_row - second_row });
		REQUIRE(first_positive2 + second_negative2 == bwn::NumeralSystem{ 2, first_row - second_row });

		REQUIRE(!(first_positive10 + first_negative10));
		REQUIRE(!(first_positive2 + first_negative10));
		REQUIRE(!(first_positive10 + first_negative2));
		REQUIRE(!(first_positive2 + first_negative2));
	}

	SECTION("Substruction")
	{
		REQUIRE(second_positive10 - first_positive10 == bwn::NumeralSystem{ 10, second_row - first_row });
		REQUIRE(second_positive10 - first_positive2 == bwn::NumeralSystem{ 2, second_row - first_row  });
		REQUIRE(second_positive2 - first_positive10 == bwn::NumeralSystem{ 10, second_row - first_row  });
		REQUIRE(second_positive2 - first_positive2 == bwn::NumeralSystem{ 2, second_row - first_row  });

		REQUIRE(second_negative10 - first_positive10 == bwn::NumeralSystem{ 10, -(second_row + first_row) });
		REQUIRE(second_negative10 - first_positive2 == bwn::NumeralSystem{ 2, -(second_row + first_row)  });
		REQUIRE(second_negative2 - first_positive10 == bwn::NumeralSystem{ 10, -(second_row + first_row)  });
		REQUIRE(second_negative2 - first_positive2 == bwn::NumeralSystem{ 2, -(second_row + first_row)  });

		REQUIRE(!(first_positive10 - first_positive10));
		REQUIRE(!(first_positive2 - first_positive10));
		REQUIRE(!(first_positive10 - first_positive2));
		REQUIRE(!(first_positive2 - first_positive2));
	}

	SECTION("Multiplication")
	{
		REQUIRE(first_positive10 * second_positive10 == bwn::NumeralSystem{ 10, first_row * second_row });
		REQUIRE(first_positive2 * second_positive10 == bwn::NumeralSystem{ 2, first_row * second_row });
		REQUIRE(first_positive10 * second_positive2 == bwn::NumeralSystem{ 10, first_row * second_row });
		REQUIRE(first_positive2 * second_positive2 == bwn::NumeralSystem{ 2, first_row * second_row });

		REQUIRE(first_positive10 * second_negative10 == bwn::NumeralSystem{ 10, first_row * -second_row });
		REQUIRE(first_positive2 * second_negative10 == bwn::NumeralSystem{ 2, first_row * -second_row });
		REQUIRE(first_positive10 * second_negative2 == bwn::NumeralSystem{ 10, first_row * -second_row });
		REQUIRE(first_positive2 * second_negative2 == bwn::NumeralSystem{ 2, first_row * -second_row });

		REQUIRE(!(first_positive10 * bwn::NumeralSystem{ 10 }));
		REQUIRE(!(first_positive2 * bwn::NumeralSystem{ 10 }));
		REQUIRE(!(first_positive10 * bwn::NumeralSystem{ 2 }));
		REQUIRE(!(first_positive2 * bwn::NumeralSystem{ 2 }));
	}

	SECTION("Division")
	{
		REQUIRE(first_positive10 / second_positive10 == bwn::NumeralSystem{ 10, first_row / second_row });
		REQUIRE(first_positive2 / second_positive10 == bwn::NumeralSystem{ 2, first_row / second_row });
		REQUIRE(first_positive10 / second_positive2 == bwn::NumeralSystem{ 10, first_row / second_row });
		REQUIRE(first_positive2 / second_positive2 == bwn::NumeralSystem{ 2, first_row / second_row });

		REQUIRE(first_positive10 / second_negative10 == bwn::NumeralSystem{ 10, first_row / -second_row });
		REQUIRE(first_positive2 / second_negative10 == bwn::NumeralSystem{ 2, first_row / -second_row });
		REQUIRE(first_positive10 / second_negative2 == bwn::NumeralSystem{ 10, first_row / -second_row });
		REQUIRE(first_positive2 / second_negative2 == bwn::NumeralSystem{ 2, first_row / -second_row });

		REQUIRE(!(second_negative10 / first_positive10));
		REQUIRE(!(second_negative10 / first_positive2));
		REQUIRE(!(second_negative2 / first_positive10));
		REQUIRE(!(second_negative2 / first_positive2));

		REQUIRE_THROWS_AS(first_positive10 / bwn::NumeralSystem{ 10 }, std::logic_error);
		REQUIRE_THROWS_WITH(first_positive10 / bwn::NumeralSystem{ 10 }, "Division by zero.");
	}
}