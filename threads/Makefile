CXXFLAGS = -g -Wall
CXXFLAGS += -O2
INCLUDEDIR = -I.
LDFLAGS = -lpthread

HEADERS = $(wildcard *.h)
TESTDIR = test
BINDIR = bin
TESTS = $(BINDIR)/BlockingQueueTest \
	$(BINDIR)/ConditionTest \
	$(BINDIR)/CountDownLatchTest \
	$(BINDIR)/MutexTest \
	$(BINDIR)/MutualDeadLock \
	$(BINDIR)/NonRecursiveMutex \
	$(BINDIR)/SelfDeadLock \
	$(BINDIR)/SingletonTest \
	$(BINDIR)/ThreadPoolTest \
	$(BINDIR)/ThreadTest 

all: $(TESTS)

$(TESTS): $(HEADERS)

$(TESTS): 
	g++ $(CXXFLAGS) -o $@ $(filter %.cpp, $^) $(INCLUDEDIR) $(LDFLAGS)

$(BINDIR)/BlockingQueueTest: $(TESTDIR)/BlockingQueueTest.cpp
$(BINDIR)/ConditionTest: $(TESTDIR)/ConditionTest.cpp
$(BINDIR)/CountDownLatchTest: $(TESTDIR)/CountDownLatchTest.cpp CountDownLatch.cpp
$(BINDIR)/MutexTest: $(TESTDIR)/MutexTest.cpp
$(BINDIR)/MutualDeadLock: $(TESTDIR)/MutualDeadLock.cpp
$(BINDIR)/NonRecursiveMutex: $(TESTDIR)/NonRecursiveMutex.cpp
$(BINDIR)/SelfDeadLock: $(TESTDIR)/SelfDeadLock.cpp
$(BINDIR)/SingletonTest: $(TESTDIR)/SingletonTest.cpp 
$(BINDIR)/ThreadPoolTest: $(TESTDIR)/ThreadPoolTest.cpp ThreadPool.cpp Thread.cpp
$(BINDIR)/ThreadTest: $(TESTDIR)/ThreadTest.cpp Thread.cpp

clean:
	rm -f $(TESTS)
