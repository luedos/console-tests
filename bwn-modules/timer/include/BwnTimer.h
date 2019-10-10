#pragma once

#include <thread>
#include <mutex>

#include "TimerImpl.h"

namespace core
{

class BwnTimer 
	: public TimerImpl
{
	//
	// Private class.
	//
private:
	struct Implementation;

	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	BwnTimer();
	//! Copy constructor.
	BwnTimer(const BwnTimer&) = delete;
	//! Move constructor.
	BwnTimer(BwnTimer&& other) noexcept;
	//! Destructor.
	~BwnTimer();

	//! Copy operator.
	BwnTimer& operator=(const BwnTimer&) = delete;
	//! Move operator.
	BwnTimer& operator=(BwnTimer&& other) noexcept = default;

	//
	// Public interface.
	//
public:
	//! Starts the timer.
	bool start(std::chrono::milliseconds interval, Callback callback, bool isRepeat) override;
	//! Stops the timer.
	void stop() override;
	//! Checks if timer is running.
	bool isRunning() const override;

	//
	// Private members.
	//
private:
	//! Timer impl.
	std::unique_ptr<Implementation> impl_;
};

}