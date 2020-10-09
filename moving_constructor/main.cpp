#include <iostream>




class MovingType
{
public:
    MovingType()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    MovingType(const MovingType & m) noexcept
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    MovingType(MovingType && m)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    ~MovingType()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    MovingType &operator= (MovingType && m)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    MovingType &operator= (MovingType & m)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

void MoveFunction (MovingType & m) noexcept
{
    MovingType moveToHere(std::move(m));
}

int main( )
{
    MovingType m1;
    MoveFunction(m1);

    return 0;
}
