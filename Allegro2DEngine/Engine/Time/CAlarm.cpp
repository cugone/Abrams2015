#include "CAlarm.h"


A2DE_BEGIN


Alarm::Alarm()
: StopWatch(), _delegate([]() { /* DO NOTHING */ }), _tickTime(1.0), _run_count(0) { /* DO NOTHING */ }


Alarm::Alarm(const std::function<void()>& fn)
    : StopWatch(), _delegate(fn), _tickTime(1.0), _run_count(-1) { /* DO NOTHING */ }

Alarm::Alarm(const std::function<void()>& fn, double tickTime)
    : StopWatch(), _delegate(fn), _tickTime(tickTime), _run_count(-1) { /* DO NOTHING */ }

Alarm::Alarm(const std::function<void()>& fn, double tickTime, int run_count)
    : StopWatch(), _delegate(fn), _tickTime(tickTime), _run_count(run_count < -1 ? -1 : run_count) { /* DO NOTHING */ }


Alarm::~Alarm() {
    if(_isRunning) Stop();
}

void Alarm::Tick() {
    if(IsRunning() == false) return;

    if(GetElapsedTimeInSeconds() >= _tickTime) {
        Reset();
        if(_run_count == 0) return;
        _delegate();
        if(_run_count > -1) --_run_count;
        Start();
    }
    return;
}

void Alarm::SetDelegate(std::function<void()> fn) {
    _delegate = fn;
}

void Alarm::SetTickTime(double tickTime) {
    _tickTime = tickTime;
}

void Alarm::SetRunCount(int run_count) {
    _run_count = (run_count < -1 ? -1 : run_count);
}

A2DE_END
