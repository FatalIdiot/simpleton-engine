#pragma once

#include <chrono>

namespace Simpleton {
    using namespace std::chrono;
    using namespace std::literals::chrono_literals;

    class cTimer {
        public:
            enum TimerState { Running, Paused, Stopped };
            
            cTimer();
            ~cTimer();

            void Start();
            void Pause();
            void Clear(); // Stop timer

            float GetPassedTime(); // get time since Start
            float Elapsed(); // get time from last Elapsed call or from timer start

            bool IsRunning() const;
            bool IsPaused() const;

        private:
            time_point<steady_clock> mStartTime; // start time after creation or Start call
            time_point<steady_clock> mLastElapsed; // time passed since last Elapsed call
            duration<float> mPassedTime; // passed time including paused periods
            TimerState mState;
    };
}