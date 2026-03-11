#ifndef TOKEN_BUCKET_H
#define TOKEN_BUCKET_H

#include "RateLimiter.h"
#include <unordered_map>
#include <mutex>

struct Bucket {
    double tokens;
    long lastRefill;
};

class TokenBucket : public RateLimiter {

private:
    int capacity;
    double refillRate;

    std::unordered_map<std::string, Bucket> buckets;
    std::mutex mtx;

public:
    TokenBucket(int cap, double rate);

    bool allowRequest(const std::string& client_id) override;

    std::string name() const override {
        return "TokenBucket";
    }
};

#endif