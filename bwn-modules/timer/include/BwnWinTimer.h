#pragma once

#include <Windows.h>
#include <memory>

#include "TimerImpl.h"

namespace core
{

class BwnWinTimer
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
	BwnWinTimer();
	//! Copy constructor.
	BwnWinTimer(const BwnWinTimer&) = delete;
	//! Move constructor.
	BwnWinTimer(BwnWinTimer&& other) noexcept;
	//! Destructor.
	~BwnWinTimer();

	//! Copy operator.
	BwnWinTimer& operator=(const BwnWinTimer&) = delete;
	//! Move operator.
	BwnWinTimer& operator=(BwnWinTimer&& other) noexcept = default;

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