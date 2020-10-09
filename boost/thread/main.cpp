#include <iostream>

#include "boost/thread/thread.hpp"

void threadFoo (void)
{
    std::cout << "boost thread" << std::endl;
}

int main( )
{
    boost::thread t(threadFoo);
    t.join();

    return 0;
}
