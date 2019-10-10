#include "BwnWinTimer.h"

#include <mutex>

struct core::BwnWinTimer::Implementation
{
	//
	// Public interface.
	//
public:
	//! Callback of the timer.
	static void __stdcall TimerCallback(void* params, unsigned char timerOrWaitFired);

	//
	// Public members.
	//
public:
	//! Current callback.
	Callback callback_;
	//! Is timer running.
	bool running_ = false;
	//! Is timer on repeat.
	bool repeat_ = false;
	//! Timers mutex for operations with running member.
	std::mutex mutex_;
	//! Timer handle.
	HANDLE timer_;
};

core::BwnWinTimer::BwnWinTimer()
	: impl_{ new Implementation }
{
}

core::BwnWinTimer::BwnWinTimer(BwnWinTimer&& other) noexcept
	: BwnWinTimer{}
{
	impl_.swap(other.impl_);
}

core::BwnWinTimer::~BwnWinTimer()
{
	stop();
}

bool core::BwnWinTimer::start(std::chrono::milliseconds interval, Callback callback, bool isRepeat)
{
	if (isRunning()) {
		stop();
	}

	if (!interval.count()) {
		stop();
	}
	else
	{
		impl_->callback_ = callback;
		impl_->repeat_ = isRepeat;

		return !CreateTimerQueueTimer(
			&impl_->timer_,
			NULL, 
			Implementation::TimerCallback, 
			impl_.get(), 
			interval.count(), 
			interval.count() * isRepeat,
			0);
	}

	return true;
}

void core::BwnWinTimer::stop()
{
	bool test;

	impl_->mutex_.lock();
	test = impl_->running_;
	impl_->mutex_.unlock();

	if (test) 
	{
		DeleteTimerQueueTimer(NULL, &impl_->timer_, NULL);
		impl_->running_ = false;
	}
}

bool core::BwnWinTimer::isRunning() const
{
	bool test;

	impl_->mutex_.lock();
	test = impl_->running_;
	impl_->mutex_.unlock();

	return test;
}

void __stdcall core::BwnWinTimer::Implementation::TimerCallback(void* params, unsigned char timerOrWaitFired)
{
	Implementation* ptr = reinterpret_cast<Implementation*>(params);

	ptr->mutex_.lock();

	ptr->callback_();

	if (!ptr->repeat_) {
		ptr->running_ = false;
	}
	ptr->mutex_.unlock();
}