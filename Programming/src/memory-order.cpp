#include <atomic>
#include <semaphore>
#include <random>
#include <cstdio>
#include <thread>

#define USE_CPU_FENCE 0

std::binary_semaphore beginSema1 {0};
std::binary_semaphore beginSema2 {0};
std::counting_semaphore<2> endSema {0};

std::atomic<int> X, Y;
std::atomic<int> r1, r2;
std::random_device seed_generator;

void *thread1Func() {
    std::mt19937 random(seed_generator());
    for (;;) {
        beginSema1.acquire();
        while (random() % 8 != 0) { }  // Random delay

        // ----- THE TRANSACTION! -----
        X.store(1, std::memory_order_relaxed);
#if USE_CPU_FENCE
        std::atomic_thread_fence(std::memory_order_seq_cst);
#else
        std::atomic_signal_fence(std::memory_order_seq_cst); 
#endif
        r1.store(Y.load(std::memory_order_relaxed), std::memory_order_relaxed);

        endSema.release();
    }

    return nullptr;  // Never returns
};

void *thread2Func() {
    std::mt19937 random(seed_generator());
    for (;;) {
        beginSema2.acquire();
        while (random() % 8 != 0) { }  // Random delay

        // ----- THE TRANSACTION! -----
        Y.store(1, std::memory_order_relaxed);
#if USE_CPU_FENCE
        std::atomic_thread_fence(std::memory_order_seq_cst);
#else
        std::atomic_signal_fence(std::memory_order_seq_cst);
#endif
        r2.store(X.load(std::memory_order_relaxed), std::memory_order_relaxed);

        endSema.release();
    }

    return nullptr;  // Never returns
};

int main() {
    // Spawn the threads
    std::thread thread1 { thread1Func };
    std::thread thread2 { thread2Func };

    // Repeat the experiment
    std::size_t detected = 0;
    for (int iterations = 1; ; iterations++) {
        // Reset X and Y
        X.store(0, std::memory_order_relaxed);
        Y.store(0, std::memory_order_relaxed);

        // Signal both threads
        beginSema1.release();
        beginSema2.release();

        // Wait for both threads
        endSema.acquire();
        endSema.acquire();

        // Check if there was a simultaneous reorder
        if (r1 == 0 and r2 == 0) {
            detected++;
            printf("%d reorders detected after %d iterations\n", static_cast<int>(detected), iterations);
        }
    }

    thread1.join();
    thread2.join();
    return 0;  // Never returns
}
