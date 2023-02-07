#include "Order.h"

int testout(void)
{
    Order order("Oid", "Gid", "Sid", Date(2023, 2, 2), 2);
    std::cout << order;
    return 0;
}

int main(void)
{
    Order order;
    std::cin >> order;
    std::cout << order;
    return 0;
}