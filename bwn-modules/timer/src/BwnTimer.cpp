#include "BwnTimer.h"

class DestructionCall
{
	//
	// Public aliases.
	//
public:
	using Callback = std::function<void()>;

	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	DestructionCall(Callback callback)
		: callback_{ callback }
	{}
	//! Destructor.
	~DestructionCall()
	{
		if (callback_) {
			callback_();
		}
	}

	//
	// Private members.
	//
private:
	//! Destruction callback.
	Callback callback_;
};

struct core::BwnTimer::Implementation
{
	//
	// Public interface.
	//
public:
	//! Threads main method.
	void ThreadTimer(std::chrono::milliseconds interval, bool isRepeat) const;

	//
	// Public members.
	//
public:
	//! Current callback.
	Callback callback_;
	//! Timers mutex for operations with running member.
	mutable std::mutex mutex_;
	//! Is thread running.
	mutable bool running_ = false;
	//! Current timer thread.
	std::thread thread_;
};

core::BwnTimer::BwnTimer()
	: impl_ {new Implementation }
{
}

core::BwnTimer::BwnTimer(BwnTimer&& other) noexcept
	: BwnTimer{}
{
	impl_.swap(other.impl_);
}

core::BwnTimer::~BwnTimer()
{
	stop();
}

bool core::BwnTimer::start(std::chrono::milliseconds interval, Callback callback, bool isRepeat)
{
	if (isRunning()) {
		stop();
	}

	impl_->callback_ = callback;

	impl_->thread_ = std::thread(
		std::function<void(Implementation*, std::chrono::milliseconds, bool)>(&Implementation::ThreadTimer), 
		impl_.get(), 
		interval, 
		isRepeat);

	return true;
}

void core::BwnTimer::stop()
{
	impl_->mutex_.lock();
	impl_->running_ = false;
	impl_->mutex_.unlock();

	if (impl_->thread_.joinable()) {
		impl_->thread_.join();
	}
}

bool core::BwnTimer::isRunning() const
{
	bool test;

	impl_->mutex_.lock();
	test = impl_->running_;
	impl_->mutex_.unlock();

	return test;
}

void core::BwnTimer::Implementation::ThreadTimer(std::chrono::milliseconds interval, bool isRepeat) const
{
	mutex_.lock();
	running_ = true;
	mutex_.unlock();

	DestructionCall mutex_lock([&](){
		mutex_.lock();
		running_ = false;
		mutex_.unlock();
	});	

	do
	{
		std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

		while ((std::chrono::high_resolution_clock::now() - start) < interval)
		{
			bool test;

			mutex_.lock();
			test = running_;
			mutex_.unlock();

			if (!test) {
				return;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}

		if (callback_) {
			callback_();
		}
	} while (isRepeat);
}
