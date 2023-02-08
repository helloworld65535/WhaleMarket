#include "Order.h"

Order::Order()
{
    quantity_ = 0;
}

Order::Order(const rapidjson::Value &value)
{
    //     vObject.AddMember("id", rapidjson::StringRef(id_.c_str()), allocator);
    // vObject.AddMember("goodId", rapidjson::StringRef(goodId_.c_str()), allocator);
    // vObject.AddMember("buyerId", rapidjson::StringRef(buyerId_.c_str()), allocator);
    // vObject.AddMember("date", date_.toJSONObject(allocator), allocator);
    // vObject.AddMember("quantity", quantity_, allocator);
    if (!value.IsObject())
        return;

    if (value.HasMember("id") && value["id"].IsString())
        id_ = value["id"].GetString();
    if (value.HasMember("goodId") && value["goodId"].IsString())
        goodId_ = value["goodId"].GetString();
    if (value.HasMember("buyerId") && value["buyerId"].IsString())
        buyerId_ = value["buyerId"].GetString();
    if (value.HasMember("date") && value["date"].IsObject())
        date_ = value["date"].GetObject();
    if (value.HasMember("quantity") && value["quantity"].IsUint())
        quantity_ = value["quantity"].GetUint();
        
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

rapidjson::Value Order::toJSONObject(rapidjson::Document::AllocatorType &allocator)
{
    rapidjson::Value vObject(rapidjson::kObjectType);
    vObject.AddMember("id", rapidjson::StringRef(id_.c_str()), allocator);
    vObject.AddMember("goodId", rapidjson::StringRef(goodId_.c_str()), allocator);
    vObject.AddMember("buyerId", rapidjson::StringRef(buyerId_.c_str()), allocator);
    vObject.AddMember("date", date_.toJSONObject(allocator), allocator);
    vObject.AddMember("quantity", quantity_, allocator);
    return vObject;
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
