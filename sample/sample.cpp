#include "omgopasscc.h"
#include <iostream>

int main()
{
    std::cout << "omgopasscc sample\n";

    omgopasscc::config cfg;
    std::cout << "config: " << omgopasscc::to_string(cfg) << "\n";
    std::cout << "result: " << omgopasscc::generate(cfg) << "\n";

    return 0;
}
