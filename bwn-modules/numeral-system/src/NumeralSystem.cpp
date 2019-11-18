#include "NumeralSystem.h"

#include <algorithm>
#include <stdexcept>

using namespace bwn;

NumeralSystem::NumeralSystem(Digit base)
{
	if (base > 45000)
	{
		base_ = 45000;
	}
	else if (base < 2)
	{
		base_ = 2;
	}
	else
	{
		base_ = base;
	}
}

NumeralSystem::NumeralSystem(Digit base, int64_t value)
	: NumeralSystem{ base }
{
	for (; value; value /= base_) {
		container_.push_back(value % base_);
	}
}

NumeralSystem::NumeralSystem(const NumeralSystem& other, Digit base)
	: NumeralSystem{ base }
{
	*this = other;
}

NumeralSystem::NumeralSystem(NumeralSystem&& other, Digit base) noexcept(std::is_nothrow_move_constructible<Container>::value)
	: NumeralSystem{ base }
{
	*this = std::move(other);
}

NumeralSystem& NumeralSystem::operator=(const NumeralSystem& other)
{
	if (this != &other) 
	{
		NumeralSystem temp = other;

		if (base_ != temp.base_) {
			temp.ChangeBase(base_);
		}

		container_.swap(temp.container_);
	}

	return *this;
}

NumeralSystem& NumeralSystem::operator=(NumeralSystem&& other) noexcept(std::is_nothrow_move_assignable<Container>::value)
{
	if (this != &other)
	{
		NumeralSystem temp = std::move(other);

		if (base_ != temp.base_) {
			temp.ChangeBase(base_);
		}

		container_.swap(temp.container_);
	}

	return *this;
}

void NumeralSystem::ValueShift(std::size_t shift)
{
	if (shift == 0) {
		return;
	}

	container_.resize(container_.size() + shift);

	for (std::size_t i = container_.size() - 1; i >= shift; --i) {
		container_[i] = container_[i - shift];
	}

	for (std::size_t i = 0; i < shift; ++i) {
		container_[i] = 0;
	}
}

std::size_t NumeralSystem::TrimEnd()
{
	std::size_t size = container_.size();
	for (; size > 0 && !container_[size - 1]; --size);

	container_.resize(size);

	return container_.size();
}

void NumeralSystem::Normalize()
{
	if (container_.empty()) {
		return;
	}

	for (std::size_t i = 0; i < container_.size(); ++i)
	{
		if (container_[i] >= base_ || container_[i] <= -base_)
		{
			if (i < container_.size() - 1) 
			{
				container_[i + 1] += container_[i] / base_;
			}
			else 
			{
				container_.push_back(container_[i] / base_);
			}

			container_[i] = container_[i] % base_;
		}
	}

	if (!TrimEnd()) {
		return;
	}

	const int32_t sign = (container_.back() > 0) * 2 - 1;

	for (std::size_t i = 0; i + 1 < container_.size(); ++i)
	{
		if (container_[i] * sign < 0)
		{
			container_[i] += base_ * sign;
			container_[i + 1] -= sign;
		}
	}

	TrimEnd();
}

void NumeralSystem::FastMul(Digit value)
{
	for (auto& digit : container_) {
		digit *= value;
	}
	Normalize();
}

void bwn::NumeralSystem::MakeAbs()
{
	for (auto& digit : container_) {
		digit = std::abs(digit);
	}
}

bool bwn::NumeralSystem::LessOnLasts(const NumeralSystem& left, const NumeralSystem& right)
{
	NumeralSystem hidden{ left.base_ };
	const NumeralSystem* correct;

	if (left.base_ == right.base_)
	{
		correct = &right;
	}
	else
	{
		hidden = right;
		correct = &hidden;
	}

	for (auto left_it = left.container_.rbegin(), right_it = correct->container_.rbegin();
		left_it != left.container_.rend() && right_it != correct->container_.rend();
		++left_it, ++right_it)
	{

		if (*left_it > *right_it) {
			return false;
		}

		if (*left_it < *right_it) {
			return true;
		}
	}

	return false;
}

std::string NumeralSystem::ToString() const
{
	std::string ret;

	{
		std::size_t i = 0;
		for (Digit localI = 1; localI < base_; localI *= 10, ++i);

		ret.reserve(container_.size() * (i + 1));
	}

	for (int32_t i = container_.size() - 1; i >= 0; --i)
	{
		ret.append(std::to_string(container_[i]));
		ret.push_back('|');
	}
	ret.pop_back();

	return ret;
}

NumeralSystem::Digit NumeralSystem::GetBase() const
{
	return base_;
}

NumeralSystem NumeralSystem::GetNewBase(Digit base) const
{
	NumeralSystem ret{ *this };
	ret.ChangeBase(base);

	return ret;
}

void NumeralSystem::ChangeBase(Digit base)
{
	if (base > 45000) 
	{
		base = 45000;
	}
	else if (base < 2)
	{
		base = 2;
	}

	NumeralSystem temp(base);

	NumeralSystem accumulator(base);

	for (std::size_t i = 0; i < container_.size(); ++i)
	{
		temp.container_.clear();

		temp.container_.push_back(container_[i]);

		for (std::size_t ii = 0; ii < i; ++ii) {
			temp.FastMul(base_);
		}
		
		accumulator += temp;
	}

	Swap(accumulator);
}

const NumeralSystem::Digit& NumeralSystem::operator[] (std::size_t index) const
{
	if (index >= container_.size()) {
		throw std::runtime_error{ "Incorrect index for the number" };
	}

	return container_[index];
}

std::size_t NumeralSystem::GetLength() const
{
	return container_.size();
}

void NumeralSystem::Swap(NumeralSystem& other)
{
	std::swap(base_, other.base_);
	container_.swap(other.container_);
}

NumeralSystem::operator bool() const
{
	if (container_.empty()) {
		return false;
	}

	auto it = container_.end();

	do
	{
		--it;

		if (*it) {
			return true;
		}
	} while (it != container_.begin());

	return false;
}

bool bwn::operator==(const NumeralSystem& left, const NumeralSystem& right)
{
	NumeralSystem hidden{ left.base_ };
	const NumeralSystem* correct;

	if (left.base_ == right.base_)
	{
		correct = &right;
	}
	else
	{
		hidden = right;
		correct = &hidden;
	}

	if (left.container_.size() != correct->container_.size()) {
		return false;
	}

	for (auto left_it = left.container_.rbegin(), right_it = correct->container_.rbegin();
		 left_it != left.container_.rend() && right_it != correct->container_.rend();
		 ++left_it, ++right_it)
	{
		if (*left_it != *right_it) {
			return false;
		}
	}

	return true;
}

bool bwn::operator!=(const NumeralSystem& left, const NumeralSystem& right)
{
	return !(left == right);
}

bool bwn::operator>(const NumeralSystem& left, const NumeralSystem& right)
{
	NumeralSystem hidden{ left.base_ };
	const NumeralSystem* correct;

	if (left.base_ == right.base_)
	{
		correct = &right;
	}
	else
	{
		hidden = right;
		correct = &hidden;
	}

	if (left.container_.size() != correct->container_.size()) {
		return left.container_.size() > correct->container_.size();
	}

	for (auto left_it = left.container_.rbegin(), right_it = correct->container_.rbegin();
		 left_it != left.container_.rend() && right_it != correct->container_.rend();
		 ++left_it, ++right_it)
	{
		if (*left_it > *right_it) {
			return true;
		}

		if (*left_it < *right_it) {
			return false;
		}
	}

	return false;
}

bool bwn::operator<(const NumeralSystem& left, const NumeralSystem& right)
{
	NumeralSystem hidden{ left.base_ };
	const NumeralSystem* correct;

	if (left.base_ == right.base_)
	{
		correct = &right;
	}
	else
	{
		hidden = right;
		correct = &hidden;
	}

	if (left.container_.size() != correct->container_.size()) {
		return left.container_.size() < correct->container_.size();
	}

	for (auto left_it = left.container_.rbegin(), right_it = correct->container_.rbegin();
		 left_it != left.container_.rend() && right_it != correct->container_.rend();
		 ++left_it, ++right_it)
	{
		if (*left_it < *right_it) {
			return true;
		}

		if (*left_it > *right_it) {
			return false;
		}
	}

	return false;
}

bool bwn::operator<=(const NumeralSystem& left, const NumeralSystem& right)
{
	return !(left > right);
}

bool bwn::operator>=(const NumeralSystem& left, const NumeralSystem& right)
{
	return !(left < right);
}

NumeralSystem& NumeralSystem::operator+=(const NumeralSystem& other)
{
	const auto add_all = [](Container& left, const Container& right)
	{
		if (left.size() < right.size()) {
			left.resize(right.size());
		}

		for (std::size_t i = 0; i < right.size(); ++i) {
			left[i] += right[i];
		}
	};

	if (other.base_ == base_)
	{
		add_all(container_, other.container_);
	}
	else
	{
		NumeralSystem local{ other };
		local.ChangeBase(base_);

		add_all(container_, local.container_);
	}

	Normalize();

	return *this;
}

NumeralSystem& NumeralSystem::operator-=(const NumeralSystem& other)
{
	const auto sub_all = [](Container& left, const Container& right)
	{
		if (left.size() < right.size()) {
			left.resize(right.size());
		}

		for (std::size_t i = 0; i < right.size(); ++i) {
			left[i] -= right[i];
		}
	};

	if (other.base_ == base_)
	{
		sub_all(container_, other.container_);
	}
	else
	{
		NumeralSystem local{ other };
		local.ChangeBase(base_);

		sub_all(container_, local.container_);
	}

	Normalize();

	return *this;
}

NumeralSystem& NumeralSystem::operator*=(const NumeralSystem& other)
{
	if (other.container_.empty())
	{
		container_.clear();
		return *this;
	}

	NumeralSystem hidden{ base_ };
	const NumeralSystem* correct;

	if (base_ == other.base_)
	{
		correct = &other;
	}
	else
	{
		hidden = other;
		correct = &hidden;
	}

	const std::size_t size = container_.size() + correct->container_.size();

	NumeralSystem accumulator(base_);
	NumeralSystem temp(base_);
	accumulator.container_.reserve(size);
	temp.container_.reserve(size);

	for (std::size_t i = 0; i < correct->container_.size(); ++i)
	{
		const Digit factor = correct->container_[i];
		temp.container_ = container_;

		temp.FastMul(factor);

		temp.ValueShift(i);

		accumulator += temp;
	}

	container_.swap(accumulator.container_);

	return *this;
}

NumeralSystem& NumeralSystem::operator/=(const NumeralSystem& other)
{
	if (!other) {
		throw std::logic_error{ "Division by zero." };
	}

	if (!*(this)) {
		return *this;
	}

	const int32_t end_sign = (!((other.container_.back() < 0) ^ (container_.back() < 0))) * 2 - 1;

	NumeralSystem hidden{ base_ };
	const NumeralSystem* correct;

	if (base_ == other.base_ && other.container_.back() > 0)
	{
		correct = &other;
	}
	else
	{
		hidden = other;
		hidden.MakeAbs();
		correct = &hidden;
	}

	if (container_.back() < 0) {
		MakeAbs();
	}

	if (*this < *correct)
	{
		container_.clear();
		return *this;
	}

	NumeralSystem accumulator(base_);
	NumeralSystem devidend(base_);
	NumeralSystem devider(base_);

	accumulator.container_.reserve(container_.size() - correct->container_.size() + 1);
	devidend.container_.reserve(correct->container_.size() + 1);
	devider.container_.reserve(correct->container_.size() + 2);

	for (std::size_t i = 1; i < correct->container_.size(); ++i) {
		devidend.container_.push_back(container_[container_.size() - correct->container_.size() + i]);
	}

	for (int32_t i = container_.size() - correct->container_.size(); i >= 0; --i)
	{
		devidend.container_.insert(devidend.container_.begin(), container_[i]);

		if (devidend < *correct)
		{
			accumulator.container_.push_back(0);

			continue;
		}

		Digit min = 1;
		Digit max = base_;

		Digit mid = min;
		devider.container_ = correct->container_;

		while (max - min > 1)
		{
			mid = (max + min) / 2;

			devider.container_ = correct->container_;
			devider.FastMul(mid);

			if (devider <= devidend)
			{
				min = mid;
				if (devider == devidend) {
					break;
				}
			}
			else
			{
				max = mid;
			}
		}

		accumulator.container_.push_back(min);

		if (mid != min)
		{
			devider.container_ = correct->container_;
			devider.FastMul(min);
		}

		devidend -= devider;
	}

	std::reverse(accumulator.container_.begin(), accumulator.container_.end());

	accumulator.Normalize();

	container_.swap(accumulator.container_);

	FastMul(end_sign);

	return *this;
}

NumeralSystem bwn::operator+ (const NumeralSystem& left, const NumeralSystem& right)
{
	NumeralSystem ret{ left };

	ret += right;

	return ret;
}

NumeralSystem bwn::operator- (const NumeralSystem& left, const NumeralSystem& right)
{
	NumeralSystem ret{ left };

	ret -= right;

	return ret;
}

NumeralSystem bwn::operator* (const NumeralSystem& left, const NumeralSystem& right)
{
	NumeralSystem ret{ left };

	ret *= right;

	return ret;
}

NumeralSystem bwn::operator/ (const NumeralSystem& left, const NumeralSystem& right)
{
	NumeralSystem ret{ left };

	ret /= right;

	return ret;
}

bwn::NumeralSystem std::abs(const bwn::NumeralSystem& number)
{
	bwn::NumeralSystem ret{ number };

	ret.MakeAbs();

	return ret;
}

void swap(bwn::NumeralSystem& left, bwn::NumeralSystem& right)
{
	left.Swap(right);
}