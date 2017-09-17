#include "Thread.h"
#include <syscall.h>
#include <unistd.h>

Thread::Thread(StartRoutine func, void* arg)
    : m_tid(0), m_func(func), m_arg(arg)
{
}

Thread::~Thread()
{
    pthread_detach(m_tid);
}

int Thread::Start()
{
    return pthread_create(&m_tid, NULL, m_func, m_arg);
}

int Thread::Join()
{
    return pthread_join(m_tid, NULL);
}

namespace CurrentThread
{
pid_t tid()
{
    return syscall(SYS_gettid);
}
}