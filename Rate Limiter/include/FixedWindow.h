#ifndef FIXED_WINDOW_H
#define FIXED_WINDOW_H

#include "RateLimiter.h"
#include <unordered_map>
#include <mutex>
#include <string> 
class FixedWindow : public RateLimiter {

private:
    int maxRequests;
    int windowSeconds;

    std::unordered_map<std::string, std::pair<long,int>> clients;
    std::mutex mtx;

public:
    FixedWindow(int maxReq, int windowSec);

    bool allowRequest(const std::string& client_id) override;

    std::string name() const override {
        return "FixedWindow";
    }
};

#endif