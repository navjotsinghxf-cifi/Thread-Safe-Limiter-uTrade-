# Thread-Safe Rate Limiter (C++)

## Overview

This project implements a **thread-safe rate limiter** that restricts the number of requests a client can make within a specific time period.
It simulates multiple clients sending concurrent requests and applies rate limiting per client.

The system supports multiple algorithms and demonstrates concurrency handling using C++ threads and mutex locks.

---

## Features

* Fixed Window Rate Limiting
* Token Bucket Rate Limiting
* Thread-safe implementation using `std::mutex`
* Concurrent client simulation using `std::thread`
* Per-request logging
* Summary statistics after execution

---

## Project Structure

```
rate-limiter
│
├── Config
│   └── config.json
│
├── include
│   ├── RateLimiter.h
│   ├── FixedWindow.h
│   └── TokenBucket.h
│
├── src
│   ├── main.cpp
│   ├── FixedWindow.cpp
│   └── TokenBucket.cpp
│
├── tests
│   └── load_test.cpp
│
└── README.md
```

---

## Algorithms Implemented

### 1. Fixed Window

Limits the number of requests a client can make within a fixed time window.

Example:
5 requests allowed per 10 seconds.

### 2. Token Bucket

Each client has a bucket of tokens.
A request is allowed only if a token is available. Tokens refill over time.

---

## Build Instructions

Open the terminal in the project directory and run:

```
g++ src/main.cpp src/FixedWindow.cpp src/TokenBucket.cpp -Iinclude -pthread -o limiter
```

---

## Run the Program

```
./limiter
```

---

## Example Output

```
17123456 client=A algorithm=FixedWindow result=ALLOWED
17123457 client=B algorithm=FixedWindow result=ALLOWED
17123458 client=A algorithm=FixedWindow result=RATE_LIMITED
```

At the end of execution, summary statistics are printed.

---

## Summary Statistics

The program prints:

* Total requests
* Allowed requests
* Rejected requests
* Per-client breakdown

---

## Technologies Used

* C++
* STL (`unordered_map`, `thread`, `mutex`)
* Multithreading
* Object-Oriented Design

---

## Author

Navjot Singh
