#include <iostream>
#include <map>

std::map<int, std::string> data;

std::map<int, std::string> & getRef ()
{
    data.insert(std::pair<int, std::string>(1, "one"));
    data.insert(std::pair<int, std::string>(2, "two"));
    data.insert(std::pair<int, std::string>(3, "three"));
    data.insert(std::pair<int, std::string>(4, "four"));
    return data;
}


int main( )
{
    std::map<int, std::string> &ref = getRef();
    for (auto i : ref)
    {
        std::cout << i.second << std::endl;
    }


    return 0;
}
