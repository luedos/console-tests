#include "NumeralSystem.h"

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

NumeralSystem::NumeralSystem(NumeralSystem&& other, Digit base) noexcept
	: NumeralSystem{ base }
{
	*this = std::move(other);
}

NumeralSystem& NumeralSystem::operator=(const NumeralSystem& other)
{
	if (this != &other) 
	{
		NumeralSystem temp = other;
		temp.ChangeBase(base_);

		container_.swap(temp.container_);
	}

	return *this;
}

NumeralSystem& NumeralSystem::operator=(NumeralSystem&& other) noexcept
{
	if (this != &other)
	{
		NumeralSystem temp = std::move(other);
		temp.ChangeBase(base_);

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

	for (int i = 0; i < shift; ++i) {
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

	for (std::size_t i = 0; i < container_.size() - 1; ++i)
	{
		if (container_[i] * sign < 0)
		{
			container_[i] += base_ * sign;
			container_[i + 1] -= sign;
		}
	}

	//if (container_.back() < 0)
	//{
	//	for (int32_t i = container_.size() - 2; i >= 0; --i)
	//	{
	//		if (container_[i] > 0)
	//		{
	//			if (container_[i + 1] != 0)
	//			{
	//				container_[i] -= base_;
	//				++container_[i + 1];
	//			}
	//			else
	//			{
	//				int32_t localI = i + 1;
	//
	//				for (; localI < container_.size() && container_[localI] == 0; ++localI);
	//
	//				if (localI == container_.size()) {
	//					continue;
	//				}
	//
	//				while (localI > i)
	//				{
	//					++container_[localI];
	//					container_[localI - 1] -= base_;
	//
	//					--localI;
	//				}
	//			}
	//		}
	//	}
	//}
	//
	//if (container_.back() > 0)
	//{
	//	for (int32_t i = container_.size() - 2; i >= 0; --i)
	//	{
	//		if (container_[i] < 0)
	//		{
	//			if (container_[i + 1] != 0)
	//			{
	//				container_[i] += base_;
	//				--container_[i + 1];
	//			}
	//			else
	//			{
	//				int32_t localI = i + 1;
	//				for (; localI < container_.size() && container_[localI] == 0; ++localI);
	//
	//				if (localI == container_.size()) {
	//					continue;
	//				}
	//
	//				while (localI > i)
	//				{
	//					--container_[localI];
	//					container_[localI - 1] += base_;
	//
	//					--localI;
	//				}
	//
	//			}
	//		}
	//	}
	//}

	TrimEnd();
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

	NumeralSystem final(base);

	for (int i = 0; i < container_.size(); ++i)
	{
		temp.container_.clear();

		temp.container_.push_back(container_[i]);

		for (int ii = 0; ii < i; ++ii) {
			temp *= base_;
		}

		final += temp;
	}

	Swap(final);
}

const NumeralSystem::Digit& NumeralSystem::operator[] (std::size_t index) const
{
	if (index >= container_.size()) {
		throw std::runtime_error{ "Incorrect index for the number" };
	}

	return container_[index];
}

std::size_t NumeralSystem::GetSize() const
{
	return container_.size();
}

void NumeralSystem::Swap(NumeralSystem& other)
{
	Digit temp = base_;
	base_ = other.base_;
	other.base_ = temp;

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
		hidden.ChangeBase(right.base_);

		correct = &hidden;
	}

	if (left.container_.size() != correct->container_.size()) {
		return false;
	}

	if (left.container_.empty()) {
		return true;
	}

	std::size_t i = left.container_.size();

	do
	{
		--i;

		if (left.container_[i] != correct->container_[i]) {
			return false;
		}

	} while (i);

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
		hidden.ChangeBase(right.base_);

		correct = &hidden;
	}

	if (left.container_.size() != correct->container_.size()) {
		return left.container_.size() > correct->container_.size();
	}

	if (left.container_.empty()) {
		return true;
	}

	std::size_t i = left.container_.size();

	do
	{
		--i;

		if (left.container_[i] > correct->container_[i]) {
			return true;
		}

		if (left.container_[i] < correct->container_[i]) {
			return false;
		}

	} while (i);

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
		hidden.ChangeBase(right.base_);

		correct = &hidden;
	}

	if (left.container_.size() != correct->container_.size()) {
		return left.container_.size() < correct->container_.size();
	}

	if (left.container_.empty()) {
		return true;
	}

	std::size_t i = left.container_.size();

	do
	{
		--i;

		if (left.container_[i] > correct->container_[i]) {
			return false;
		}

		if (left.container_[i] < correct->container_[i]) {
			return true;
		}

	} while (i);

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

		for (int i = 0; i < right.size(); ++i) {
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

NumeralSystem& NumeralSystem::operator+=(int64_t value)
{
	NumeralSystem local{ base_, value };

	return *this += local;
}

NumeralSystem& NumeralSystem::operator-=(const NumeralSystem& other)
{
	const auto sub_all = [](Container& left, const Container& right)
	{
		if (left.size() < right.size()) {
			left.resize(right.size());
		}

		for (int i = 0; i < right.size(); ++i) {
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

NumeralSystem& NumeralSystem::operator-=(int64_t value)
{
	NumeralSystem local{ base_, value };

	return *this -= local;
}

NumeralSystem& NumeralSystem::operator*=(const NumeralSystem& other)
{
	NumeralSystem hidden{ base_ };
	const NumeralSystem* correct;

	if (base_ == other.base_)
	{
		correct = &other;
	}
	else
	{
		hidden = other;
		hidden.ChangeBase(base_);

		correct = &hidden;
	}

	const std::size_t size = container_.size() + correct->container_.size();

	NumeralSystem ret(base_);
	NumeralSystem temp(base_);
	ret.container_.reserve(size);
	temp.container_.reserve(size);

	for (std::size_t i = 0; i < correct->container_.size(); ++i)
	{
		temp.container_ = container_;

		for (int ii = 0; ii < temp.container_.size(); ++ii) {
			temp.container_[ii] *= correct->container_[i];
		}

		temp.Normalize();

		temp.ValueShift(i);

		ret += temp;
	}

	container_.swap(ret.container_);

	return *this;
}

NumeralSystem& NumeralSystem::operator*=(int64_t value)
{
	NumeralSystem local{ base_, value };

	return *this *= local;
}

NumeralSystem& NumeralSystem::operator/=(const NumeralSystem& other)
{
	if (!other) {
		throw std::runtime_error{ "Division by zerro." };
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
		hidden.ChangeBase(base_);

		correct = &hidden;
	}

	if (*this < *correct)
	{
		container_.clear();
		return *this;
	}

	NumeralSystem ret(base_);
	NumeralSystem temp(base_);
	NumeralSystem local(base_);

	ret.container_.reserve(container_.size() - correct->container_.size() + 1);
	temp.container_.reserve(correct->container_.size() + 1);
	local.container_.reserve(correct->container_.size() + 2);

	for (std::size_t i = 1; i < correct->container_.size(); ++i) {
		temp.container_.push_back(container_[container_.size() - correct->container_.size() + i]);
	}

	for (int32_t i = container_.size() - correct->container_.size(); i >= 0; --i)
	{
		temp.container_.insert(temp.container_.begin(), container_[i]);

		if (temp < *correct)
		{
			ret.container_.push_back(0);

			continue;
		}

		int32_t min = 1;
		int32_t max = base_;

		int32_t mid;

		while (max - min > 1)
		{
			mid = (max + min) / 2;

			local.container_ = correct->container_;
			local *= mid;

			if (local <= temp)
			{
				min = mid;
				if (local == temp) {
					break;
				}
			}
			else
			{
				max = mid;
			}
		}

		ret.container_.push_back(min);

		local.container_ = correct->container_;

		local *= min;

		temp -= local;
	}

	std::reverse(ret.container_.begin(), ret.container_.end());

	ret.Normalize();

	container_.swap(ret.container_);

	return *this;
}

NumeralSystem& NumeralSystem::operator/=(int64_t value)
{
	NumeralSystem local{ base_, value };

	return *this *= local;
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