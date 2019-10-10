#include "WinTimer.h"

namespace core {

WinTimer::WinTimer()
    : m_timer{nullptr}
    , m_callback{}
    , m_isRepeatable{false}
{
}

WinTimer::~WinTimer()
{
    stop();
}

bool WinTimer::start(std::chrono::milliseconds interval, Callback callback, bool isRepeat)
{
    if (!callback) {
        return false;
    }

    m_callback = callback;
    m_isRepeatable = isRepeat;

    if (isRunning()) {
        stop();
    }

    if (interval.count() == 0) {
        isRepeat = false;
    }

    const DWORD period = isRepeat ? static_cast<DWORD>(interval.count()) : 0;
    const auto ok =
        CreateTimerQueueTimer(&m_timer, nullptr, WinTimer::onTimerProc, this, interval.count(), period, WT_EXECUTEINTIMERTHREAD);

    return ok != 0;
}

void WinTimer::stop()
{
    if (m_timer) {
        DeleteTimerQueueTimer(nullptr, m_timer, nullptr);
        m_timer = nullptr;
    }
}

bool WinTimer::isRunning() const
{
    return m_timer != nullptr;
}

void WinTimer::invokeCallback()
{
    m_callback();

    if (!m_isRepeatable) {
        stop();
    }
}

void CALLBACK WinTimer::onTimerProc(void *param, BOOLEAN)
{
    WinTimer *timer = static_cast<WinTimer *>(param);
    timer->invokeCallback();
}

} // namespace core
