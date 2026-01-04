#include <mutex>
#include "RingBuffer.h"
template <typename T> class ThreadSafeRingBuffer{
private: 
    RingBuffer<T> buffer;
    std::mutex mtx;
    
public:
    explicit ThreadSafeRingBuffer(int capacity) :buffer(capacity) {
    }

    bool tryPush(const T& value){
        std::lock_guard<std::mutex> lock(mtx);
        return buffer.push(value);

    }
    bool tryPop(T& out){
        std::lock_guard<std::mutex> lock(mtx);
        return buffer.pop(out);
    }

    bool isFull() {
        std::lock_guard<std::mutex> lock(mtx);
        return buffer.isFull();

    }
    bool isEmpty() {
        std::lock_guard<std::mutex> lock(mtx);
        return buffer.isEmpty();

    }
};