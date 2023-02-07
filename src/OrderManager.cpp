
#include "OrderManager.h"
#include <fstream>

OrderManager::OrderManager(std::string dataFilePath)
{
    dataFilePath_ = dataFilePath;
    orderNumber_ = 0;
    savedOrderId_ = 0;
}

OrderManager::~OrderManager()
{
    saveOrders();

    for (auto i = orders_.begin(); i != orders_.end(); ++i)
    {
        delete (*i);
    }
}

bool OrderManager::saveOrders() const
{
    std::ofstream out(dataFilePath_, std::ios::out);
    out << "orderNumber=" << std::endl
        << orderNumber_ << std::endl
        << "savedOrderId=" << std::endl
        << savedOrderId_ << std::endl;

    for (auto i = orders_.begin(); i != orders_.end(); ++i)
    {
        out << *(*i);
    }
    out.close();
    return true;
}

bool OrderManager::pullOrders()
{
    std::ifstream in(dataFilePath_, std::ios::in);
    if (in.is_open())
    {
        std::string str;
        unsigned int orderNumber = 0;
        in >> str;
        if (str == "orderNumber=")
        {
            in >> orderNumber_;
        }
        in >> str;
        if (str == "savedOrderId=")
        {
            in >> savedOrderId_;
        }

        for (int i = 0; i < orderNumber_; ++i)
        {
            Order *order = new Order();
            in >> (*order);
            orders_.push_back(order);
            ++orderNumber;
        }
        orderNumber_ = orderNumber;
        in.close();
        return true;
    }
    in.close();
    return false;
}

void OrderManager::addOrder(Order *order)
{
    order->setId(getNewId());
    orders_.push_back(order);
    ++orderNumber_;
}

std::string OrderManager::getNewId()
{
    std::string insertStr(std::to_string(++savedOrderId_));
    std::string newStr = std::string("O00000000").substr(0, 10 - insertStr.length()) + insertStr;
    return newStr;
}
