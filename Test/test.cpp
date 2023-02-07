#include "OrderManager.h"

int testaddOrder(void)
{
    OrderManager orderManager("Order.txt");
    orderManager.addOrder(new Order("Order", "G000000001", "B000000001", Date(2023, 2, 2), 2));
    orderManager.addOrder(new Order("Order", "G000000001", "B000000001", Date(2023, 2, 2), 2));
    orderManager.addOrder(new Order("Order", "G000000001", "B000000001", Date(2023, 2, 2), 2));
    orderManager.addOrder(new Order("Order", "G000000001", "B000000001", Date(2023, 2, 2), 2));
    return 0;
}

int main(void)
{
    OrderManager orderManager("Order.txt");
    orderManager.pullOrders();

    return 0;
}