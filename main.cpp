#include <iostream>
#include <thread>
#include <latch>
#include <chrono>

#include "src/spsc_queue_lockfree_v1.h"
#include "src/spsc_queue_lockfree_v2_padded.h"
#include "src/spsc_queue_lockfree_v3_padded_memorder.h"
#include "src/spsc_queue_mutex_v1.h"
#include "src/spsc_queue_mutex_v2_modulo.h"

using namespace std::literals::chrono_literals;

struct X {
    size_t x;
};

constexpr int F = 10;
constexpr int N = 10000000;
constexpr int M = F * N;
std::mutex cout_mutex;

#define MEASURE_DURATION(RUN, PREFIX, TOTAL_MSGS, CODE) \
    { \
        auto start = std::chrono::high_resolution_clock::now(); \
        CODE \
        auto end = std::chrono::high_resolution_clock::now(); \
        std::chrono::duration<double, std::micro> duration = end - start; \
        cout_mutex.lock(); \
        std::cout << RUN << ": " \
                  << PREFIX << ": processed " << TOTAL_MSGS << " msgs, duration [micros] = " << duration.count() << ", " \
                  << "tps = " << static_cast<double>(TOTAL_MSGS)/(duration.count() / 1000000) << ", " \
                  << "avg per msg [nanos] = " << (duration.count() * 1000) / TOTAL_MSGS << std::endl; \
        cout_mutex.unlock(); \
    }

template <typename T>
auto consumeFunction(std::latch& latch_warmup, std::latch& latch_final, T& queue) {
    latch_warmup.arrive_and_wait();
    MEASURE_DURATION(1, "consumer", M, {
        size_t count{0};
        while (count < M) {
            X item{};
            if (queue.pop(item)) count++;
        }
    });

    latch_final.arrive_and_wait();
    MEASURE_DURATION(2, "consumer", M, {
        size_t count{0};
        while (count < M) {
            X item{};
            if (queue.pop(item)) count++;
        }
    });
}

int main()
{
    {
        std::cout << "SpscQueueV1 test" << std::endl;

        SpscQueueV1<X> queue(N);
        std::latch latch_warmup(2);
        std::latch latch_final(2);

        std::thread t{[&latch_warmup, &latch_final, &queue] {
            consumeFunction(latch_warmup, latch_final, queue);
        }};

        latch_warmup.arrive_and_wait();
        MEASURE_DURATION(1, "producer", M, {
            size_t count = 0;
            while (count < M) {
                while (!queue.push(X{count}));
                count++;
            }
        });

        latch_final.arrive_and_wait();
        MEASURE_DURATION(2, "producer", M, {
            size_t count = 0;
            while (count < M) {
                while (!queue.push(X{count}));
                count++;
            }
        });

        t.join();
        std::this_thread::sleep_for(2s);
    }

    {
        std::cout << "SpscQueueV2Padded test" << std::endl;

        SpscQueueV2Padded<X> queue(N);
        std::latch latch_warmup(2);
        std::latch latch_final(2);

        std::thread t{[&latch_warmup, &latch_final, &queue] {
            consumeFunction(latch_warmup, latch_final, queue);
        }};

        latch_warmup.arrive_and_wait();
        MEASURE_DURATION(1, "producer", M, {
            size_t count = 0;
            while (count < M) {
                while (!queue.push(X{count}));
                count++;
            }
        });

        latch_final.arrive_and_wait();
        MEASURE_DURATION(2, "producer", M, {
            size_t count = 0;
            while (count < M) {
                while (!queue.push(X{count}));
                count++;
            }
        });

        t.join();
        std::this_thread::sleep_for(2s);
    }

    {
        std::cout << "SpscQueueV2PaddedMemorder test" << std::endl;

        SpscQueueV3PaddedMemorder<X> queue(N);
        std::latch latch_warmup(2);
        std::latch latch_final(2);

        std::thread t{[&latch_warmup, &latch_final, &queue] {
            consumeFunction(latch_warmup, latch_final, queue);
        }};

        latch_warmup.arrive_and_wait();
        MEASURE_DURATION(1, "producer", M, {
            size_t count = 0;
            while (count < M) {
                while (!queue.push(X{count}));
                count++;
            }
        });

        latch_final.arrive_and_wait();
        MEASURE_DURATION(2, "producer", M, {
            size_t count = 0;
            while (count < M) {
                while (!queue.push(X{count}));
                count++;
            }
        });

        t.join();
        std::this_thread::sleep_for(2s);
    }

    {
        std::cout << "SpscQueueV1Mutex test" << std::endl;

        SpscQueueMutexV1<X> queue(N);
        std::latch latch_warmup(2);
        std::latch latch_final(2);

        std::thread t{[&latch_warmup, &latch_final, &queue] {
            consumeFunction(latch_warmup, latch_final, queue);
        }};

        latch_warmup.arrive_and_wait();
        MEASURE_DURATION(1, "producer", M, {
            size_t count = 0;
            while (count < M) {
                while (!queue.push(X{count}));
                count++;
            }
        });

        latch_final.arrive_and_wait();
        MEASURE_DURATION(2, "producer", M, {
            size_t count = 0;
            while (count < M) {
                while (!queue.push(X{count}));
                count++;
            }
        });

        t.join();
        std::this_thread::sleep_for(2s);
    }

    {
        std::cout << "SpscQueueMutexV2Modulo test" << std::endl;

        SpscQueueMutexV2Modulo<X> queue(N);
        std::latch latch_warmup(2);
        std::latch latch_final(2);

        std::thread t{[&latch_warmup, &latch_final, &queue] {
            consumeFunction(latch_warmup, latch_final, queue);
        }};

        latch_warmup.arrive_and_wait();
        MEASURE_DURATION(1, "producer", M, {
            size_t count = 0;
            while (count < M) {
                while (!queue.push(X{count}));
                count++;
            }
        });

        latch_final.arrive_and_wait();
        MEASURE_DURATION(2, "producer", M, {
            size_t count = 0;
            while (count < M) {
                while (!queue.push(X{count}));
                count++;
            }
        });

        t.join();
        std::this_thread::sleep_for(2s);
    }

    return 0;
}
