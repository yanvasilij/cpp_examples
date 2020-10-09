#include <thread>
#include <iostream>
#include <chrono>
#include <string>
#include <csignal>

namespace
{
    volatile std::sig_atomic_t gSignalStatus;
}

void signal_handler(int signal)
{
    gSignalStatus = signal;
}

class ThreadTest
{
    std::string output;

    void thread1 ()
    {
        std::signal(SIGINT, signal_handler);
        while (gSignalStatus == 0)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << output << "signal value: " << gSignalStatus << std::endl;
        }
        std::cout << "thread1 end " << std::endl;
    }

    void thread2 ()
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        output = "New string value" + std::to_string(10);
    }

public:
    ThreadTest() : output("Value 1") {}

    void start (void)
    {

        std::thread t2 (&ThreadTest::thread2, this);
        t2.detach();

        std::thread t1 (&ThreadTest::thread1, this);
        t1.join();

    }
};

int main( )
{
    ThreadTest test;

    test.start();

    return 0;
}
