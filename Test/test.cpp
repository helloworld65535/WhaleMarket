
#include "DataManager.h"
#include "Good.h"
#include "Order.h"

int main(void)
{
    DataManager<Order> dataManager("Order.json", 'O');
    dataManager.addData(new Order("Order","G000000001","B000000001",Date(2023,2,8),2));
    dataManager.addData(new Order("Order","G000000002","B000000001",Date(2023,2,8),3));
    dataManager.addData(new Order("Order","G000000003","B000000001",Date(2023,2,8),4));
    dataManager.addData(new Order("Order","G000000004","B000000001",Date(2023,2,8),5));
    

    return 0;
}