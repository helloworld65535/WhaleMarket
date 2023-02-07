#include "Order.h"

Order::Order()
{
    quantity_ = 0;
}

Order::Order(const std::string &id, const std::string &goodId,
             const std::string &sellerId, const Date &date,
             unsigned int quantity)
    : id_(id), goodId_(goodId), buyerId_(sellerId),
      date_(date), quantity_(quantity) {}

const std::string &Order::getId() const
{
    return id_;
}

const std::string &Order::getGoodId() const
{
    return goodId_;
}

const std::string &Order::getBuyerId() const
{
    return buyerId_;
}

const Date &Order::getDate() const
{
    return date_;
}

unsigned int Order::getQuantity() const
{
    return quantity_;
}

void Order::setId(const std::string &id)
{
    id_ = id;
}

void Order::setGoodId(const std::string &goodId)
{
    goodId_ = goodId;
}

void Order::setBuyerId(const std::string &sellerId)
{
    buyerId_ = sellerId;
}

void Order::setDate(const Date &date)
{
    date_ = date;
}

void Order::setQuantity(unsigned int quantity)
{
    quantity_ = quantity;
}

std::ostream &operator<<(std::ostream &out, const Order &order)
{
    out << order.id_ << std::endl
        << order.goodId_ << std::endl
        << order.buyerId_ << std::endl
        << order.date_ << std::endl
        << order.quantity_ << std::endl;
    return out;
}

std::istream &operator>>(std::istream &in, Order &order)
{
    in >> order.id_ >> order.goodId_ >> order.buyerId_ >> order.date_ >> order.quantity_;
    return in;
}
