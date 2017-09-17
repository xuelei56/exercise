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
	$(BINDIR)/SingletonTest \
	$(BINDIR)/MutexTest \
	$(BINDIR)/MutualDeadLock \
	$(BINDIR)/SelfDeadLock \
	$(BINDIR)/NonRecursiveMutex 

all: $(TESTS)

$(TESTS): $(HEADERS)

$(TESTS): 
	g++ $(CXXFLAGS) -o $@ $(filter %.cpp, $^) $(INCLUDEDIR) $(LDFLAGS)

$(BINDIR)/BlockingQueueTest: $(TESTDIR)/BlockingQueueTest.cpp
$(BINDIR)/ConditionTest: $(TESTDIR)/ConditionTest.cpp
$(BINDIR)/CountDownLatchTest: $(TESTDIR)/CountDownLatchTest.cpp CountDownLatch.cpp
$(BINDIR)/SingletonTest: $(TESTDIR)/SingletonTest.cpp 
$(BINDIR)/MutexTest: $(TESTDIR)/MutexTest.cpp
$(BINDIR)/MutualDeadLock: $(TESTDIR)/MutualDeadLock.cpp
$(BINDIR)/SelfDeadLock: $(TESTDIR)/SelfDeadLock.cpp
$(BINDIR)/NonRecursiveMutex: $(TESTDIR)/NonRecursiveMutex.cpp

clean:
	rm -f $(TESTS)
