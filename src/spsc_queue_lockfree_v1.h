#pragma once

#include <vector>

template<typename T>
class SpscQueueV1 final {
public:
  explicit SpscQueueV1(std::size_t maxElems) : store_(maxElems, T()) {
  }

  SpscQueueV1() = delete;
  SpscQueueV1(const SpscQueueV1 &) = delete;
  SpscQueueV1(const SpscQueueV1 &&) = delete;
  SpscQueueV1 &operator=(const SpscQueueV1 &) = delete;
  SpscQueueV1 &operator=(const SpscQueueV1 &&) = delete;

  auto push(const T &elem) noexcept {
    const auto idx = nextWriteIdx_.load();
    const auto next_idx = increment(idx);
    if (next_idx != nextReadIdx_.load()) {
      store_[idx] = elem;
      nextWriteIdx_.store(next_idx);
      return true;
    }
    return false;
  }

  auto pop(T &elem) noexcept {
    const auto idx = nextReadIdx_.load();
    if (idx == nextWriteIdx_.load()) {
      return false;
    }
    elem = store_[idx];
    const auto next_idx = increment(idx);
    nextReadIdx_.store(next_idx);
    return true;
  }

private:
  size_t increment(size_t idx) const {
    if (idx == store_.capacity() - 1) {
      [[unlikely]]
          return 0;
    }
    return idx + 1;
  }

  std::vector<T> store_;
  std::atomic<size_t> nextWriteIdx_{0};
  std::atomic<size_t> nextReadIdx_{0};
};