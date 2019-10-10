#pragma once

#include "TimerImpl.h"

#include <Windows.h>

#include <atomic>

namespace core {

class WinTimer : public TimerImpl
{
public:
    WinTimer();
    ~WinTimer() override;

    bool start(std::chrono::milliseconds interval, Callback callback, bool isRepeat) override;

    void stop() override;

    bool isRunning() const override;

private:
    void invokeCallback();

    /**
     * Application-defined function of type WAITORTIMERCALLBACK to be executed when the timer expires.
     */
    static void CALLBACK onTimerProc(void* param, BOOLEAN);

    HANDLE m_timer;
	Callback m_callback;
    std::atomic_bool m_isRepeatable;
};

} // namespace core
