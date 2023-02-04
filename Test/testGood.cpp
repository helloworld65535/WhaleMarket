#include "Good.h"

int main(void)
{
    Good good("G0000001", "good", 2.5, "description", "S0001", Date(2023, 1, 2), Good::IN_SALE);

    std::cout << good;
    return 0;
}