#include <iostream>

int main(void)
{
    std::cout << std::locale().name() << std::endl;
    std::locale::global(std::locale(""));
    std::cout << std::locale().name() << std::endl;
    std::locale::global(std::locale("C"));
    std::cout << std::locale().name() << std::endl;
    return 0;
}
