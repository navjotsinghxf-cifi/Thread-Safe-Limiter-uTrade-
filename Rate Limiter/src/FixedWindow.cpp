#include "../include/FixedWindow.h"
#include <chrono>

using namespace std;

FixedWindow::FixedWindow(int maxReq, int windowSec) {
    maxRequests = maxReq;
    windowSeconds = windowSec;
}

bool FixedWindow::allowRequest(const string& client_id) {

    lock_guard<mutex> lock(mtx);

    long now = chrono::duration_cast<chrono::seconds>(
        chrono::system_clock::now().time_since_epoch()).count();

    if(clients.find(client_id) == clients.end()) {
        clients[client_id] = {now,1};
        return true;
    }

    auto &entry = clients[client_id];

    long windowStart = entry.first;
    int count = entry.second;

    if(now - windowStart < windowSeconds) {

        if(count < maxRequests) {
            entry.second++;
            return true;
        }

        return false;

    } else {

        clients[client_id] = {now,1};
        return true;
    }
}