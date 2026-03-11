#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <unordered_map>
#include <chrono>

#include "../include/FixedWindow.h"
#include "../include/TokenBucket.h"

using namespace std;

mutex statsMutex;

int totalRequests = 0;
int allowedRequests = 0;
int rejectedRequests = 0;

unordered_map<string,int> allowedPerClient;
unordered_map<string,int> rejectedPerClient;

long getTimestamp() {

    return chrono::duration_cast<chrono::milliseconds>(
        chrono::system_clock::now().time_since_epoch()).count();
}

void simulateClient(RateLimiter& limiter, string client_id) {

    for(int i=0;i<20;i++) {

        bool allowed = limiter.allowRequest(client_id);

        long ts = getTimestamp();

        {
            lock_guard<mutex> lock(statsMutex);

            totalRequests++;

            if(allowed) {
                allowedRequests++;
                allowedPerClient[client_id]++;
            }
            else {
                rejectedRequests++;
                rejectedPerClient[client_id]++;
            }

            cout << ts
                 << " client=" << client_id
                 << " algorithm=" << limiter.name()
                 << " result=" << (allowed ? "ALLOWED" : "RATE_LIMITED")
                 << endl;
        }

        this_thread::sleep_for(chrono::milliseconds(50));
    }
}

void printStats() {

    cout << "\n====== SUMMARY ======\n";

    cout << "Total Requests: " << totalRequests << endl;
    cout << "Allowed: " << allowedRequests << endl;
    cout << "Rejected: " << rejectedRequests << endl;

    cout << "\nPer Client\n";

    for(auto &c : allowedPerClient) {

        string id = c.first;

        cout << "Client " << id
             << " Allowed=" << allowedPerClient[id]
             << " Rejected=" << rejectedPerClient[id]
             << endl;
    }
}

int main() {

    FixedWindow limiter(5,10);
    // TokenBucket limiter(10,1);

    vector<string> clients = {"A","B","C","D","E"};

    vector<thread> threads;

    for(string client : clients) {
        threads.emplace_back(simulateClient, ref(limiter), client);
    }

    for(auto &t : threads)
        t.join();

    printStats();
}