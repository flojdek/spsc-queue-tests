# Build

    cmake .
    make
    ./spsc_queue_tests

# Sample output

On my Mac Apple M3 Pro:

    SpscQueueV1 test
    1: producer: processed 100000000 msgs, duration [micros] = 5.69819e+06, tps = 1.75494e+07, avg per msg [nanos] = 56.9819
    1: consumer: processed 100000000 msgs, duration [micros] = 5.69819e+06, tps = 1.75494e+07, avg per msg [nanos] = 56.9819
    2: producer: processed 100000000 msgs, duration [micros] = 5.6766e+06, tps = 1.76162e+07, avg per msg [nanos] = 56.766
    2: consumer: processed 100000000 msgs, duration [micros] = 5.6766e+06, tps = 1.76162e+07, avg per msg [nanos] = 56.766
    SpscQueueV2Padded test
    1: producer: processed 100000000 msgs, duration [micros] = 4.28292e+06, tps = 2.33485e+07, avg per msg [nanos] = 42.8292
    1: consumer: processed 100000000 msgs, duration [micros] = 4.40422e+06, tps = 2.27055e+07, avg per msg [nanos] = 44.0422
    2: producer: processed 100000000 msgs, duration [micros] = 4.39328e+06, tps = 2.2762e+07, avg per msg [nanos] = 43.9328
    2: consumer: processed 100000000 msgs, duration [micros] = 4.51448e+06, tps = 2.21509e+07, avg per msg [nanos] = 45.1448
    SpscQueueV2PaddedMemorder test
    1: producer: processed 100000000 msgs, duration [micros] = 4.28772e+06, tps = 2.33224e+07, avg per msg [nanos] = 42.8772
    1: consumer: processed 100000000 msgs, duration [micros] = 4.40733e+06, tps = 2.26895e+07, avg per msg [nanos] = 44.0733
    2: producer: processed 100000000 msgs, duration [micros] = 4.27345e+06, tps = 2.34003e+07, avg per msg [nanos] = 42.7345
    2: consumer: processed 100000000 msgs, duration [micros] = 4.40548e+06, tps = 2.2699e+07, avg per msg [nanos] = 44.0548
    SpscQueueV1Mutex test
    1: producer: processed 100000000 msgs, duration [micros] = 5.44535e+06, tps = 1.83643e+07, avg per msg [nanos] = 54.4535
    1: consumer: processed 100000000 msgs, duration [micros] = 5.44536e+06, tps = 1.83643e+07, avg per msg [nanos] = 54.4536
    2: producer: processed 100000000 msgs, duration [micros] = 5.45214e+06, tps = 1.83414e+07, avg per msg [nanos] = 54.5214
    2: consumer: processed 100000000 msgs, duration [micros] = 5.45439e+06, tps = 1.83338e+07, avg per msg [nanos] = 54.5439
    SpscQueueMutexV2Modulo test
    1: producer: processed 100000000 msgs, duration [micros] = 5.07884e+06, tps = 1.96895e+07, avg per msg [nanos] = 50.7884
    1: consumer: processed 100000000 msgs, duration [micros] = 5.07892e+06, tps = 1.96892e+07, avg per msg [nanos] = 50.7892
    2: producer: processed 100000000 msgs, duration [micros] = 5.36668e+06, tps = 1.86335e+07, avg per msg [nanos] = 53.6668
    2: consumer: processed 100000000 msgs, duration [micros] = 5.37014e+06, tps = 1.86215e+07, avg per msg [nanos] = 53.7014

# Links

https://www.codeproject.com/Articles/43510/Lock-Free-Single-Producer-Single-Consumer-Circular this article is perfect.