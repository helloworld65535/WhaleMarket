#include "GoodManager.h"

int testsaveGoods(void)
{
    GoodManager goodManager("goodManager.txt");

    goodManager.addGoods(new Good("123", "人机交互", 56.5, "软件工程用书", "S000000001", Date(2023, 1, 2), Good::IN_SALE));
    goodManager.addGoods(new Good("123", "人机交互", 56.5, "软件工程用书", "S000000001", Date(2023, 1, 2), Good::IN_SALE));
    goodManager.addGoods(new Good("123", "人机交互", 56.5, "软件工程用书", "S000000001", Date(2023, 1, 2), Good::IN_SALE));
    goodManager.addGoods(new Good("123", "人机交互", 56.5, "软件工程用书", "S000000001", Date(2023, 1, 2), Good::IN_SALE));
    goodManager.saveGoods();
    return 0;
}

int testpullGoods(void)
{
    GoodManager goodManager("goodManager.txt");
    goodManager.pullGoods();
    goodManager.traverse([](Good *good) -> void
                         { std::cout << (*good); });
    return 0;
}
int main(int argc, char const *argv[])
{
    testpullGoods();

    return 0;
}
