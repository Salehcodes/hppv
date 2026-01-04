#include "ThreadSafeRingBuffer.h"
#include <thread>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

ThreadSafeRingBuffer<int> buffer(10);
const int TOTAL_ITEMS = 1000;

void produce() {
    int produced = 0;

    while (produced < TOTAL_ITEMS) {
        // Try to push current value
        if (buffer.tryPush(produced)) {
            ++produced;
        } else {
            // Buffer is full → give consumer a chance
            this_thread::sleep_for(chrono::microseconds(10));
        }
    }

    cout << "done prod, produced: " << produced << endl;
}

void consume() {
    int consumed = 0;
    vector<int> received;
    received.reserve(TOTAL_ITEMS);

    while (consumed < TOTAL_ITEMS) {
        int out;
        if (buffer.tryPop(out)) {
            ++consumed;
            received.push_back(out);
        } else {
            // Buffer empty → give producer a chance
            this_thread::sleep_for(chrono::microseconds(10));
        }
    }

    cout << "done cons, consumed: " << consumed << endl;

    // Optional: quick sanity check (not required, but nice to have)
    // for (int i = 0; i < 10 && i < (int)received.size(); ++i) {
    //     cout << received[i] << " ";
    // }
    // cout << endl;
}

int main() {
    thread cns(consume);
    thread prd(produce);

    cns.join();
    prd.join();
}
