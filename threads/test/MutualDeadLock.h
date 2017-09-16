#ifndef MUTUALDEADLOCK_H
#define MUTUALDEADLOCK_H

#include "Mutex.h"
#include <iostream>
#include <set>
#include <unistd.h>

class Request;

class Inventory
{
public:
    void Add(Request* req)
    {
        MutexLockGuard guard(m_ml);
        m_requests.insert(req);
    }
    void Remove(Request* req)
    {
        MutexLockGuard guard(m_ml);
        m_requests.erase(req);
    }
    void PrintAll() const;

private:
    mutable MutexLock m_ml;
    std::set<Request*> m_requests;
};

Inventory g_inventory;

class Request
{
public:
    void Process()
    {
        MutexLockGuard guard(m_ml);
        std::cout << "Process()\n";
        g_inventory.Add(this);
    }
    void Print() const
    {
        MutexLockGuard guard(m_ml);
        std::cout << "Print()\n";
    }
    ~Request()
    {
        MutexLockGuard guard(m_ml);
        sleep(1); //为了容易复现死锁，延时
        g_inventory.Remove(this);
    }
private:
    mutable MutexLock m_ml;
};

#endif
