
#include "GoodManager.h"
#include <fstream>

GoodManager::GoodManager(std::string dataFilePath)
{
    goodNumber_ = 0;
    savedGoodId_ = 0;
    dataFilePath_ = dataFilePath;
}

GoodManager::~GoodManager()
{
    saveGoods();

    for (auto i = goods_.begin(); i != goods_.end(); ++i)
    {
        delete (*i);
    }
}

bool GoodManager::pullGoods()
{
    std::ifstream in(dataFilePath_, std::ios::in);
    if (in.is_open())
    {
        std::string str;
        unsigned int goodNumber = 0;
        in >> str;
        if (str == "goodNumber=")
        {
            in >> goodNumber_;
        }
        in >> str;
        if (str == "savedGoodId=")
        {
            in >> savedGoodId_;
        }

        for (int i = 0; i < goodNumber_; ++i)
        {
            Good *good = new Good();
            in >> (*good);
            goods_.push_back(good);
            ++goodNumber;
        }
        goodNumber_ = goodNumber;
        in.close();
        return true;
    }
    in.close();
    return false;
}

bool GoodManager::saveGoods() const
{
    std::ofstream out(dataFilePath_, std::ios::out);
    out << "goodNumber=" << std::endl
        << goodNumber_ << std::endl
        << "savedGoodId=" << std::endl
        << savedGoodId_ << std::endl;

    for (auto i = goods_.begin(); i != goods_.end(); ++i)
    {
        out << *(*i);
    }
    out.close();
    return true;
}

void GoodManager::addGoods(Good *good)
{
    good->setId(getNewId());
    goods_.push_back(good);
    ++goodNumber_;
}

void GoodManager::traverse(void (*func)(Good *good)) const
{
    for (auto i = goods_.begin(); i != goods_.end(); ++i)
    {
        func((*i));
    }
}

std::string GoodManager::getNewId()
{
    std::string insertStr(std::to_string(++savedGoodId_));
    std::string newStr = std::string("G00000000").substr(0, 10 - insertStr.length()) + insertStr;
    return newStr;
}