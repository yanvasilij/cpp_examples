#include <thread>
#include <iostream>
#include <chrono>

class ThreadTest
{
    std::string output;

    void thread1 ()
    {
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << output << std::endl;
        }
    }

    void thread2 ()
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        output = "New string value";
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
