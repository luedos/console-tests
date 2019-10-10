#pragma once

#include <memory>
#include <iterator>
#include <type_traits>

namespace bwn
{

//
// Forward definitions.
//
template<typename>
class ForwardIterator;
template<typename>
class BidirectionalIterator;
template<typename>
class RandomAccessIterator;

template<typename IteratorSubclass, typename TestedIterT, typename = std::void_t<>>
struct IterTest : public std::false_type {};

template<typename ValueT, typename IterT>
struct IterTest<ForwardIterator<ValueT>, IterT, std::void_t<
	typename std::enable_if<std::is_copy_constructible<IterT>::value>::type, // Checks if iterator is copy constructable.
	typename std::enable_if<std::is_copy_assignable<IterT>::value>::type, // Checks if iterator is copy assignable.
	decltype((void)(++std::declval<IterT&>())), // Checks if iterator if forward iteratable.
	typename std::enable_if<std::is_same<decltype(*std::declval<IterT>()), ValueT&>::value>::type, // Checks if iterator can return value.
	typename std::enable_if<std::is_convertible<decltype(std::declval<IterT>() == std::declval<IterT>()), bool>::value>::type  // Checks if iterator can be comparisible.
>> : public std::true_type {};

template<typename ValueT, typename IterT>
struct IterTest<BidirectionalIterator<ValueT>, IterT, std::void_t<
	typename std::enable_if<IterTest<ForwardIterator<ValueT>, IterT>::value>::type, // Everything working for forward iterator works here as well
	decltype((void)(--std::declval<IterT&>())) // Checks if iterator if backward iteratable.
>> : public std::true_type {};

template<typename ValueT, typename IterT>
struct IterTest<RandomAccessIterator<ValueT>, IterT, std::void_t<
	typename std::enable_if<IterTest<BidirectionalIterator<ValueT>, IterT>::value>::type, // Everything working for bidirectional iterator works here as well
	decltype((void)(std::declval<IterT&>() -= std::declval<typename RandomAccessIterator<ValueT>::difference_type>())), // Check that iterator backward iteratable on custom amount.
	decltype((void)(std::declval<IterT&>() += std::declval<typename RandomAccessIterator<ValueT>::difference_type>())), // Check that iterator froward iteratable on custom amount.
	typename std::enable_if<std::is_convertible<decltype(std::declval<IterT>() < std::declval<IterT>()), bool>::value>::type, // Check if iterator is comparisible.
	typename std::enable_if<std::is_convertible<decltype(std::declval<IterT>() - std::declval<IterT>()), typename RandomAccessIterator<ValueT>::difference_type>::value>::type // Check if iterator can calculate difference.
>> : public std::true_type {};

template<typename ValueT>
class ForwardIterator
{
	//
	// Public aliases.
	//
public:
	using  iterator_category = std::forward_iterator_tag;
	using  value_type = ValueT;
	using  difference_type = ptrdiff_t;
	using  pointer = ValueT*;
	using  reference = ValueT&;

	//
	// Additional classes.
	//
private:
	template<typename BaseValueT>
	class Base
	{
		//
		// Construction and destruction.
		//
	public:
		//! Destructor.
		virtual ~Base() = default;

		//
		// Public interface.
		//
	public:
		//! Iterates forward.
		virtual void IterateForward() = 0;
		//! Returns value.
		virtual BaseValueT& GetValue() = 0;
		//! Returns true if iterators are equal.
		virtual bool IsEqual(const Base&) const = 0;
		//! Returns deep copy of iterator.
		virtual void GetCopy(std::unique_ptr<Base>&) const = 0;
	};

	template<typename, typename = std::void_t<>>
	class Impl;

	template<typename IterT>
	class Impl<IterT, std::void_t<
		typename std::iterator_traits<IterT>::value_type,
		typename std::enable_if<IterTest<ForwardIterator<typename std::iterator_traits<IterT>::value_type>,IterT>::value>::type>>
		: public virtual ForwardIterator<ValueT>::template Base<typename std::iterator_traits<IterT>::value_type>
	{
		//
		// Public aliases.
		//
	public:
		using value_type = typename std::iterator_traits<IterT>::value_type;

		//
		// Construction and destruction.
		//
	public:
		Impl(const IterT& iter)
			: iter_{ iter }
		{}

		//
		// Public interface.
		//
	public:
		//! Iterates forward.
		void IterateForward() override
		{
			++iter_;
		}
		//! Returns value.
		value_type& GetValue() override
		{
			return *iter_;
		}
		//! Returns true if iterators are equal.
		bool IsEqual(const ForwardIterator<ValueT>::Base<value_type>& other_base) const override
		{
			if (typeid(*this) != typeid(other_base)) {
				return false;
			}

			const Impl& other = dynamic_cast<const Impl&>(other_base);

			return iter_ == other.iter_;
		}
		//! Returns deep copy of iterator.
		void GetCopy(std::unique_ptr<ForwardIterator<ValueT>::Base<value_type>>& ptr) const override
		{
			ptr = std::make_unique<Impl>(iter_);
		}

		//
		// Private members.
		//
	protected:
		//! Incapsulated iterator.
		IterT iter_;
	};

	//
	// Public construction and destruction.
	//
public:
	//! Constructor from iterator.
	template<typename IterT, typename = decltype((void)(Impl<IterT>(std::declval<IterT>())))>
	ForwardIterator(IterT iter)
		: impl_{ std::make_unique<Impl<IterT>>(iter) }
	{
	}
	//! Constructor from bidirectional iterator.
	ForwardIterator(const BidirectionalIterator<ValueT>& other);
	//! Constructor from random access iterator.
	ForwardIterator(const RandomAccessIterator<ValueT>& other);
	//! Copy constructor.
	ForwardIterator(const ForwardIterator& other)
	{
		other.impl_->GetCopy(impl_);
	}
	//! Copy operator.
	ForwardIterator& operator=(const ForwardIterator& other)
	{
		if (this != &other) {
			other.impl_->GetCopy(impl_);
		}

		return *this;
	}
	//! Move constructor.
	ForwardIterator(ForwardIterator&&) noexcept = default;
	//! Move opeartor.
	ForwardIterator& operator=(ForwardIterator&&) noexcept = default;

	//
	// Public interface.
	//
public:
	//! Prefix unary operator ++.
	ForwardIterator& operator++()
	{
		impl_->IterateForward();

		return *this;
	}
	//! Postfix unary operator ++.
	ForwardIterator operator++(int)
	{
		ForwardIterator ret = *this;

		++(*this);

		return ret;
	}
	//! Returns value of iterator.
	reference operator*()
	{
		return impl_->GetValue();
	}
	//! Returns value of iterator.
	pointer operator->()
	{
		return &(impl_->GetValue());
	}

	//
	// Friends.
	//
public:
	friend BidirectionalIterator<ValueT>;
	friend RandomAccessIterator<ValueT>;
	//! Returns true if two iterators are equal.
	friend bool operator==(const bwn::ForwardIterator<ValueT>& left, const bwn::ForwardIterator<ValueT>& right)
	{
		return left.impl_->IsEqual(*right.impl_);
	}
	//! Returns true if two iterators are not equal.
	friend bool operator!=(const bwn::ForwardIterator<ValueT>& left, const bwn::ForwardIterator<ValueT>& right)
	{
		return !(left == right);
	}

	//
	// Private members.
	//
private:
	std::unique_ptr<Base<ValueT>> impl_;

};

template<typename ValueT>
class BidirectionalIterator
{
	//
	// Public aliases.
	//
public:
	using  iterator_category = std::bidirectional_iterator_tag;
	using  value_type = ValueT;
	using  difference_type = ptrdiff_t;
	using  pointer = ValueT*;
	using  reference = ValueT&;

	//
	// Additional classes.
	//
private:
	template<typename BaseValueT>
	class Base : public virtual ForwardIterator<ValueT>::template Base<BaseValueT>
	{
		//
		// Public interface.
		//
	public:
		//! Iterates backwards.
		virtual void IterateBackward() = 0;
		//! Returns deep copy of iterator.
		virtual void GetCopy(std::unique_ptr<Base>&) const = 0;
	};

	template<typename, typename = std::void_t<>>
	class Impl;

	template<typename IterT>
	class Impl<IterT, std::void_t<
		typename std::enable_if<std::is_constructible<typename ForwardIterator<ValueT>::template Impl<IterT>, IterT>::value>::type,
		typename std::enable_if<IterTest<BidirectionalIterator<typename std::iterator_traits<IterT>::value_type>, IterT>::value>::type>>
		: public ForwardIterator<ValueT>::template Impl<IterT>
		, public virtual Base<typename std::iterator_traits<IterT>::value_type>
	{
		//
		// Public aliases.
		//
	public:
		using BaseImpl = typename ForwardIterator<ValueT>::template Impl<IterT>;
		using typename BaseImpl::value_type;

		//
		// Construction and destruction.
		//
	public:
		Impl(IterT iter)
			: BaseImpl{ iter }
		{}

		//
		// Public interface.
		//
	public:
		//! Iterates backwards.
		void IterateBackward() override
		{
			--(this->iter_);
		}
		void GetCopy(std::unique_ptr<BidirectionalIterator<ValueT>::Base<value_type>>& ptr) const override
		{
			ptr = std::make_unique<Impl>(this->iter_);
		}
	};

	//
	// Public construction and destruction.
	//
public:
	//! Constructor from iterator.
	template<typename IterT, typename = decltype((void)(Impl<IterT>(std::declval<IterT>())))>
	BidirectionalIterator(IterT iter)
		: impl_{ std::make_unique<Impl<IterT>>(iter) }
	{
	}
	//! Constructor from random access iterator.
	explicit BidirectionalIterator(const RandomAccessIterator<ValueT>& other);
	//! Copy constructor.
	BidirectionalIterator(const BidirectionalIterator& other)
	{
		other.impl_->GetCopy(impl_);
	}
	//! Copy operator.
	BidirectionalIterator& operator=(const BidirectionalIterator& other)
	{
		if (this != &other) {
			other.impl_->GetCopy(impl_);
		}

		return *this;
	}
	//! Move constructor.
	BidirectionalIterator(BidirectionalIterator&&) noexcept = default;
	//! Move opeartor.
	BidirectionalIterator& operator=(BidirectionalIterator&&) noexcept = default;

	//
	// Public interface.
	//
public:
	//! Prefix unary operator --.
	BidirectionalIterator& operator--()
	{
		this->impl_->IterateBackward();

		return *this;
	}
	//! Postfix unary operator ++.
	BidirectionalIterator operator--(int)
	{
		BidirectionalIterator ret = *this;

		--(*this);

		return ret;
	}
	//! Prefix unary operator ++.
	BidirectionalIterator& operator++()
	{
		impl_->IterateForward();

		return *this;
	}
	//! Postfix unary operator ++.
	BidirectionalIterator operator++(int)
	{
		BidirectionalIterator ret = *this;

		++(*this);

		return ret;
	}
	//! Returns value of iterator.
	reference operator*()
	{
		return impl_->GetValue();
	}
	//! Returns value of iterator.
	pointer operator->()
	{
		return &(impl_->GetValue());
	}

	//
	// Friends.
	//
public:
	friend ForwardIterator<ValueT>;
	friend RandomAccessIterator<ValueT>;
	//! Returns true if two iterators are equal.
	friend bool operator==(const bwn::BidirectionalIterator<ValueT>& left, const bwn::BidirectionalIterator<ValueT>& right)
	{
		return left.impl_->IsEqual(*right.impl_);
	}
	//! Returns true if two iterators are not equal.
	friend bool operator!=(const bwn::BidirectionalIterator<ValueT>& left, const bwn::BidirectionalIterator<ValueT>& right)
	{
		return !(left == right);
	}

	//
	// Private members.
	//
protected:
	std::unique_ptr<Base<ValueT>> impl_;
};

template<typename ValueT>
class RandomAccessIterator
{
	//
	// Aliases.
	//
public:
	using  iterator_category = std::random_access_iterator_tag;
	using  value_type = ValueT;
	using  difference_type = ptrdiff_t;
	using  pointer = ValueT*;
	using  reference = ValueT&;

	//
	// Additional classes.
	//
private:
	template<typename BaseValueT>
	class Base : public virtual BidirectionalIterator<ValueT>::template Base<BaseValueT>
	{
		//
		// Public interface.
		//
	public:
		//! Iterates forward on a custom amount.
		virtual void IterateForwardAmount(difference_type) = 0;
		//! Iterates backwards on a random amount.
		virtual void IterateBackwardAmount(difference_type) = 0;
		//! Compare 2 iterators.
		virtual bool CompareLess(const Base&) const = 0;
		//! Returns difference between two iterators.
		virtual difference_type GetDifference(const Base&) const = 0;
		//! Returns deep copy of iterator.
		virtual void GetCopy(std::unique_ptr<Base>&) const = 0;
	};

	template<typename, typename = std::void_t<>>
	class Impl;

	template<typename IterT>
	class Impl<IterT, std::void_t<
		decltype((void)(typename BidirectionalIterator<ValueT>::template Impl<IterT>(std::declval<IterT>()))),
		typename std::enable_if<IterTest<RandomAccessIterator<typename std::iterator_traits<IterT>::value_type>, IterT>::value>::type>>
		: public BidirectionalIterator<ValueT>::template Impl<IterT>
		, public virtual Base<typename std::iterator_traits<IterT>::value_type>
	{
		//
		// Public aliases.
		//
	public:
		using BaseImpl = typename BidirectionalIterator<ValueT>::template Impl<IterT>;
		using typename BaseImpl::value_type;

		//
		// Construction and destruction.
		//
	public:
		Impl(const IterT& iter)
			: BaseImpl{ iter }
		{}

		//
		// Public interface.
		//
	public:
		//! Iterates forward on a custom amount.
		void IterateForwardAmount(difference_type amount) override
		{
			this->iter_ += amount;
		}
		//! Iterates backwards on a random amount.
		void IterateBackwardAmount(difference_type amount) override
		{
			this->iter_ -= amount;
		}
		//! Compare 2 iterators.
		bool CompareLess(const Base<value_type>& base) const override
		{
			if (typeid(*this) != typeid(base)) {
				throw std::runtime_error{"Iterators are not comparible."};
			}

			const Impl& other = dynamic_cast<const Impl&>(base);

			return this->iter_ < other.iter_;
		}
		//! Returns difference between two iterators.
		difference_type GetDifference(const Base<value_type>& base) const override
		{
			if (typeid(*this) != typeid(base)) {
				throw std::runtime_error{"Iterators are not comparible."};
			}

			const Impl& other = dynamic_cast<const Impl&>(base);

			return this->iter_ - other.iter_;
		}
		//! Returns deep copy of iterator,
		void GetCopy(std::unique_ptr<Base<value_type>>& ptr) const override
		{
			ptr = std::make_unique<Impl>(this->iter_);
		}
	};

	//
	// Public construction and destruction.
	//
public:
	//! Constructor from iterator.
	template<typename IterT, typename = decltype((void)(Impl<IterT>(std::declval<IterT>())))>
	RandomAccessIterator(IterT iter)
		: impl_{ std::make_unique<Impl<IterT>>(iter) }
	{
	}
	//! Copy constructor.
	RandomAccessIterator(const RandomAccessIterator& other)
	{
		other.impl_->GetCopy(impl_);
	}
	//! Copy operator.
	RandomAccessIterator& operator=(const RandomAccessIterator& other)
	{
		if (this != &other) {
			other.impl_->GetCopy(impl_);
		}

		return *this;
	}
	//! Move constructor.
	RandomAccessIterator(RandomAccessIterator&&) noexcept = default;
	//! Move opeartor.
	RandomAccessIterator& operator=(RandomAccessIterator&&) noexcept = default;

	//
	// Public interface.
	//
public:
	//! Iterates forward on some amount.
	RandomAccessIterator& operator+=(difference_type steps)
	{
		impl_->IterateForwardAmount(steps);

		return *this;
	}
	//! Iterates forward on some amount.
	RandomAccessIterator& operator-=(difference_type steps)
	{
		this->impl_->IterateBackwardAmount(steps);

		return *this;
	}
	//! Prefix unary operator --.
	RandomAccessIterator& operator--()
	{
		this->impl_->IterateBackward();

		return *this;
	}
	//! Postfix unary operator ++.
	RandomAccessIterator operator--(int)
	{
		RandomAccessIterator ret = *this;

		--(*this);

		return ret;
	}
	//! Prefix unary operator ++.
	RandomAccessIterator& operator++()
	{
		impl_->IterateForward();

		return *this;
	}
	//! Postfix unary operator ++.
	RandomAccessIterator operator++(int)
	{
		RandomAccessIterator ret = *this;

		++(*this);

		return ret;
	}
	//! Returns value of iterator.
	reference operator*()
	{
		return impl_->GetValue();
	}
	//! Returns value of iterator.
	pointer operator->()
	{
		return &(impl_->GetValue());
	}

	//
	// Friends.
	//
public:
	friend ForwardIterator<ValueT>;
	friend BidirectionalIterator<ValueT>;
	//! Iterates forward for some amount.
	friend RandomAccessIterator<ValueT> operator+(const bwn::RandomAccessIterator<ValueT>& iter, difference_type steps)
	{
		RandomAccessIterator ret = iter;
		ret.impl_->IterateForward(steps);

		return ret;
	}
	//! Iterates backward for some amount.
	friend RandomAccessIterator<ValueT> operator-(const bwn::RandomAccessIterator<ValueT>& iter, difference_type steps)
	{
		RandomAccessIterator ret = iter;
		ret.impl_->IterateBackwardAmount(steps);

		return ret;
	}
	//! Returns difference between two iterators.
	friend difference_type operator-(const bwn::RandomAccessIterator<ValueT>& left, const bwn::RandomAccessIterator<ValueT>& right)
	{
		return left.impl_->GetDifference(*right.impl_);
	}
	//! Returns true if two iterators are equal.
	friend bool operator==(const bwn::RandomAccessIterator<ValueT>& left, const bwn::RandomAccessIterator<ValueT>& right)
	{
		return left.impl_->IsEqual(*right.impl_);
	}
	//! Returns true if two iterators are not equal.
	friend bool operator!=(const bwn::RandomAccessIterator<ValueT>& left, const bwn::RandomAccessIterator<ValueT>& right)
	{
		return !(left == right);
	}
	//! Returns true if left iterator less then right one.
	friend bool operator<(const bwn::RandomAccessIterator<ValueT>& left, const bwn::RandomAccessIterator<ValueT>& right)
	{
		return left.impl_->CompareLess(*right.impl_);
	}
	//! Returns true if left iterator higher then right one.
	friend bool operator>(const bwn::RandomAccessIterator<ValueT>& left, const bwn::RandomAccessIterator<ValueT>& right)
	{
		return !(left < right || left == right);
	}
	//! Returns true if left iterator less or equal then right one.
	friend bool operator<=(const bwn::RandomAccessIterator<ValueT>& left, const bwn::RandomAccessIterator<ValueT>& right)
	{
		return left < right || left == right;
	}
	//! Returns true if left iterator higher or equal then right one.
	friend bool operator>=(const bwn::RandomAccessIterator<ValueT>& left, const bwn::RandomAccessIterator<ValueT>& right)
	{
		return !(left < right);
	}

	//
	// Private members.
	//
protected:
	std::unique_ptr<Base<value_type>> impl_;
};


template<typename ValueT>
ForwardIterator<ValueT>::ForwardIterator(const BidirectionalIterator<ValueT>& other)
{
	std::unique_ptr<typename BidirectionalIterator<ValueT>::Base> new_impl;
	other.impl_->GetCopy(new_impl);

	impl_ = std::move(new_impl);
}

template<typename ValueT>
ForwardIterator<ValueT>::ForwardIterator(const RandomAccessIterator<ValueT>& other)
{
	std::unique_ptr<typename RandomAccessIterator<ValueT>::Base> new_impl;
	other.impl_->GetCopy(new_impl);

	impl_ = std::move(new_impl);
}

template<typename ValueT>
BidirectionalIterator<ValueT>::BidirectionalIterator(const RandomAccessIterator<ValueT>& other)
{
	std::unique_ptr<typename RandomAccessIterator<ValueT>::Base> new_impl;
	other.impl_->GetCopy(new_impl);

	impl_ = std::move(new_impl);
}

}
