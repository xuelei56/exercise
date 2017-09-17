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
        MutexLock lock(m_mutex);
        m_requests.insert(req);
    }
    void Remove(Request* req)
    {
        MutexLock lock(m_mutex);
        m_requests.erase(req);
    }
    void PrintAll() const;

private:
    mutable Mutex m_mutex;
    std::set<Request*> m_requests;
};

Inventory g_inventory;

class Request
{
public:
    void Process()
    {
        MutexLock lock(m_mutex);
        std::cout << "Process()\n";
        g_inventory.Add(this);
    }
    void Print() const
    {
        MutexLock lock(m_mutex);
        std::cout << "Print()\n";
    }
    ~Request()
    {
        MutexLock lock(m_mutex);
        sleep(1); //为了容易复现死锁，延时
        g_inventory.Remove(this);
    }
private:
    mutable Mutex m_mutex;
};

#endif
