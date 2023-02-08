
#include "Good.h"

Good::Good()
{
    price_ = 0;
    goodState_ = SOLD_OUT;
}

Good::Good(const rapidjson::Value &value) : Good()
{
    if (!value.IsObject())
        return;
    if (value.HasMember("id") && value["id"].IsString())
        id_ = value["id"].GetString();

    if (value.HasMember("name") && value["name"].IsString())
        name_ = value["name"].GetString();

    if (value.HasMember("price") && value["price"].IsDouble())
        price_ = value["price"].GetDouble();

    if (value.HasMember("description") && value["description"].IsString())
        description_ = value["description"].GetString();

    if (value.HasMember("sellerId") && value["sellerId"].IsString())
        sellerId_ = value["sellerId"].GetString();

    if (value.HasMember("shelfDate") && value["shelfDate"].IsObject())
        shelfDate_ = value["shelfDate"].GetObject();

    if (value.HasMember("goodState") && value["goodState"].IsUint())
        goodState_ = (Good::GoodState)value["goodState"].GetUint();
}

Good::Good(const std::string &id, const std::string &name, double price, const std::string &description,
           const std::string &sellerId, const Date &shelfTime, Good::GoodState goodState)
    : id_(id), name_(name), price_(price), description_(description),
      sellerId_(sellerId), shelfDate_(shelfTime), goodState_(goodState)
{
}

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

rapidjson::Value Good::toJSONObject(rapidjson::Document::AllocatorType &allocator)
{
    rapidjson::Value vObject(rapidjson::kObjectType);
    vObject.AddMember("id", rapidjson::StringRef(id_.c_str()), allocator);
    vObject.AddMember("name", rapidjson::StringRef(name_.c_str()), allocator);
    vObject.AddMember("price", rapidjson::Value().SetDouble(price_), allocator);
    vObject.AddMember("description", rapidjson::StringRef(description_.c_str()), allocator);
    vObject.AddMember("sellerId", rapidjson::StringRef(sellerId_.c_str()), allocator);
    vObject.AddMember("shelfDate", shelfDate_.toJSONObject(allocator), allocator);
    vObject.AddMember("goodState_", rapidjson::Value().SetUint(goodState_), allocator);
    return vObject;
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
