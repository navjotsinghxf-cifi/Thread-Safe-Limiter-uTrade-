#include "../include/TokenBucket.h"
#include <chrono>

using namespace std;

TokenBucket::TokenBucket(int cap, double rate) {
    capacity = cap;
    refillRate = rate;
}

bool TokenBucket::allowRequest(const string& client_id) {

    lock_guard<mutex> lock(mtx);

    long now = chrono::duration_cast<chrono::seconds>(
        chrono::system_clock::now().time_since_epoch()).count();

    if(buckets.find(client_id) == buckets.end()) {
        buckets[client_id] = {capacity, now};
    }

    Bucket &bucket = buckets[client_id];

    long elapsed = now - bucket.lastRefill;

    bucket.tokens = min((double)capacity,
                        bucket.tokens + elapsed * refillRate);

    bucket.lastRefill = now;

    if(bucket.tokens >= 1) {
        bucket.tokens -= 1;
        return true;
    }

    return false;
}