#include "simpleton/util/cTimer.hpp"

namespace Simpleton {
    using namespace std::chrono;
    using namespace std::literals::chrono_literals;

    cTimer::cTimer() {
        mStartTime = steady_clock::now();
        mLastElapsed = steady_clock::now();
        mPassedTime = seconds::zero();
    }

    cTimer::~cTimer() {
    }

    void cTimer::Start() {
        if(mState == TimerState::Running)
            return;

        mStartTime = steady_clock::now();
        mState = TimerState::Running;
    }

    void cTimer::Pause() {
        if(mState != TimerState::Running)
            return;

        mPassedTime += steady_clock::now() - mStartTime;
        mState = TimerState::Paused;
    }

    void cTimer::Clear() {
        mPassedTime = seconds::zero();
        mState = TimerState::Stopped;
    }

    void cTimer::Restart() {
        mPassedTime = seconds::zero();
        mStartTime = steady_clock::now();
        mState = TimerState::Running;
    }

    float cTimer::Elapsed() {
        if(mState != TimerState::Running)
            return 0.0f;

        duration<float> timePassed;
        timePassed = steady_clock::now() - mLastElapsed;
        mLastElapsed = steady_clock::now();
        return timePassed.count();
    }

    float cTimer::GetPassedTime() {
        duration<float> timePassed = mPassedTime;
        if(mState == TimerState::Running) {
            timePassed += steady_clock::now() - mStartTime;
        }
        return timePassed.count();
    }

    bool cTimer::IsRunning() const {
        return mState == TimerState::Running;
    }

    bool cTimer::IsPaused() const {
        return mState == TimerState::Paused;
    }
}