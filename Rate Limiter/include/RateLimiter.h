#ifndef RATE_LIMITER_H
#define RATE_LIMITER_H

#include <string>

class RateLimiter {
public:
    virtual bool allowRequest(const std::string& client_id) = 0;
    virtual std::string name() const = 0;
    virtual ~RateLimiter() {}
};

#endif