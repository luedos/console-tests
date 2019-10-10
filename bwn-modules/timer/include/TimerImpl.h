#pragma once

#include <functional>
#include <chrono>

namespace core {

class TimerImpl
{
public:
	using Callback = std::function<void()>;

	virtual ~TimerImpl() = default;

	virtual bool start(std::chrono::milliseconds interval, Callback callback, bool isRepeat) = 0;
	virtual void stop() = 0;

	virtual bool isRunning() const = 0;
};

} // namespace core