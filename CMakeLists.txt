cmake_minimum_required(VERSION 3.29)
project(spsc_queue_tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(spsc_queue_tests main.cpp
        src/spsc_queue_lockfree_v1.h
        src/spsc_queue_lockfree_v2_padded.h
        src/spsc_queue_lockfree_v3_padded_memorder.h
        src/spsc_queue_mutex_v1.h
        src/padded_value.h
        src/spsc_queue_mutex_v2_modulo.h
)
