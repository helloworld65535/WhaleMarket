
#include "Good.h"

Good::Good()
{
    price_ = 0;
    goodState_ = SOLD_OUT;
}

Good::Good(const std::string &id, const std::string &name, double price, const std::string &description,
           const std::string &sellerId, const Date &shelfTime, Good::GoodState goodState)
    : id_(id), name_(name), price_(price), description_(description),
      sellerId_(sellerId), shelfDate_(shelfTime), goodState_(goodState) {}

const std::string &Good::getId() const
{
    return id_;
}

void Good::setId(const std::string &id)
{
    id_ = id;
}

const std::string &Good::getName() const
{
    return name_;
}

void Good::setName(const std::string &name)
{
    name_ = name;
}

double Good::getPrice() const
{
    return price_;
}

void Good::setPrice(double price)
{
    price_ = price;
}

const std::string &Good::getDescription() const
{
    return description_;
}

void Good::setDescription(const std::string &description)
{
    description_ = description;
}

const std::string &Good::getSellerId() const
{
    return sellerId_;
}

void Good::setSellerId(const std::string &sellerId)
{
    sellerId_ = sellerId;
}

const Date &Good::getShelfTime() const
{
    return shelfDate_;
}

void Good::setShelfDate(const Date &shelfDate)
{
    shelfDate_ = shelfDate;
}

Good::GoodState Good::getGoodState() const
{
    return goodState_;
}

void Good::setGoodState(Good::GoodState goodState)
{
    goodState_ = goodState;
}

std::ostream &operator<<(std::ostream &out, const Good &good)
{
    out << good.id_ << std::endl
        << good.name_ << std::endl
        << good.price_ << std::endl
        << good.description_ << std::endl
        << good.sellerId_ << std::endl
        << good.shelfDate_ << std::endl
        << good.goodState_ << std::endl;
    return out;
}

std::istream &operator>>(std::istream &in, Good &good)
{
    unsigned int goodState;
    in >> good.id_ >> good.name_ >> good.price_ >> good.description_ >> good.sellerId_ >> good.shelfDate_ >> goodState;
    good.goodState_ = (Good::GoodState)goodState;
    return in;
}
