#pragma once

#include <vector>

#include "padded_value.h"

template<typename T>
class SpscQueueV2Padded final {
public:
  explicit SpscQueueV2Padded(std::size_t maxElems) : store_(maxElems, T()) {
  }

  SpscQueueV2Padded() = delete;
  SpscQueueV2Padded(const SpscQueueV2Padded &) = delete;
  SpscQueueV2Padded(const SpscQueueV2Padded &&) = delete;
  SpscQueueV2Padded &operator=(const SpscQueueV2Padded &) = delete;
  SpscQueueV2Padded &operator=(const SpscQueueV2Padded &&) = delete;

  auto push(const T &elem) noexcept {
    const auto idx = nextWriteIdx_.value.load();
    const auto next_idx = increment(idx);
    if (next_idx != nextReadIdx_.value.load()) {
      store_[idx] = elem;
      nextWriteIdx_.value.store(next_idx);
      return true;
    }
    return false;
  }

  auto pop(T &elem) noexcept {
    const auto idx = nextReadIdx_.value.load();
    if (idx == nextWriteIdx_.value.load()) {
      return false;
    }
    elem = store_[idx];
    const auto next_idx = increment(idx);
    nextReadIdx_.value.store(next_idx);
    return true;
  }

private:
  size_t increment(size_t idx) const {
    if (idx == store_.capacity() - 1) { [[unlikely]]
      return 0;
    }
    return idx + 1;
  }

  std::vector<T> store_;
  PaddedValue<std::atomic<size_t> > nextWriteIdx_{0};
  PaddedValue<std::atomic<size_t> > nextReadIdx_{0};
};