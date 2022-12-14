#ifndef __TIMER_H__
#define __TIMER_H__

#include <chrono>
using namespace std;
using namespace std::chrono;

class Timer {
 public:
  Timer() : m_begin(high_resolution_clock::now()) {}
  void reset() { m_begin = high_resolution_clock::now(); }

  // 默认输出秒
  template <typename Duration = milliseconds>
  int64_t elapsed() const {
    return duration_cast<Duration>(high_resolution_clock::now() - m_begin)
        .count();
  }

  // 微秒
  int64_t elapsed_micro() const { return elapsed<microseconds>(); }

  // 纳秒
  int64_t elapsed_nano() const { return elapsed<nanoseconds>(); }

  // 秒
  int64_t elapsed_seconds() const { return elapsed<seconds>(); }

  // 分
  int64_t elapsed_minutes() const { return elapsed<minutes>(); }

  // 时
  int64_t elapsed_hours() const { return elapsed<hours>(); }

 private:
  time_point<high_resolution_clock> m_begin;
};

#endif  // __TIMER_H__