#pragma once

#include <vector>

template<typename T>
class SpscQueueMutexV1 final {
public:
  explicit SpscQueueMutexV1(std::size_t maxElems) : store_(maxElems, T()) {
  }

  SpscQueueMutexV1() = delete;
  SpscQueueMutexV1(const SpscQueueMutexV1 &) = delete;
  SpscQueueMutexV1(const SpscQueueMutexV1 &&) = delete;
  SpscQueueMutexV1 &operator=(const SpscQueueMutexV1 &) = delete;
  SpscQueueMutexV1 &operator=(const SpscQueueMutexV1 &&) = delete;

  auto push(const T &elem) noexcept {
    std::lock_guard<std::mutex> lock(mutex_);
    const auto idx = nextWriteIdx_;
    const auto next_idx = increment(idx);
    if (next_idx != nextReadIdx_) {
      store_[idx] = elem;
      nextWriteIdx_ = next_idx;
      return true;
    }
    return false;
  }

  auto pop(T &elem) noexcept {
    std::lock_guard<std::mutex> lock(mutex_);
    const auto idx = nextReadIdx_;
    if (idx == nextWriteIdx_) {
      return false;
    }
    elem = store_[idx];
    const auto next_idx = increment(idx);
    nextReadIdx_ = next_idx;
    return true;
  }

private:
  size_t increment(size_t idx) const {
    if (idx == store_.capacity() - 1) { [[unlikely]]
      return 0;
    }
    return idx + 1;
  }

  std::mutex mutex_;
  std::vector<T> store_;
  size_t nextWriteIdx_{0};
  size_t nextReadIdx_{0};
};