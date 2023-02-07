
#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <vector>
#include "Order.h"

class OrderManager
{
public:
    OrderManager(std::string dataFilePath);
    ~OrderManager();

    bool saveOrders() const;
    bool pullOrders();

    void addOrder(Order *order);

protected:
    std::vector<Order *> orders_; ///< 商品数组容器
    unsigned int orderNumber_;    ///< 商品数量
    unsigned int savedOrderId_;   ///< 生成过的id数量
    std::string dataFilePath_;    ///< 数据文件路径

    std::string getNewId();
};

#endif // ORDERMANAGER_H
