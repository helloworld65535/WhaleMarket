
#include "GoodManager.h"
#include <fstream>

GoodManager::GoodManager()
{
    goodNumber_ = 0;
    savedGoodId_ = 0;
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
        if (str == "savedGoodId=")
        {
            in >> savedGoodId_;
        }

        for (int i = 0; i < goodNumber_; ++i)
        {
            Good *good = new Good();
            in >> *good;
            goods_.push_back(good);
            ++goodNumber;
        }
        goodNumber_=goodNumber;
        return true;
    }
    return false;
}

bool GoodManager::saveGoods() const
{
    std::ofstream out(dataFilePath_, std::ios::out);
    out << "goodNumber=" << std::endl
        << "goodNumber=" << std::endl
        << "savedGoodId=" << std::endl
        << savedGoodId_ << std::endl;

    for (auto i = goods_.begin(); i != goods_.end(); ++i)
    {
        out << *(*i);
    }

    return true;
}

std::string GoodManager::getNewId()
{
    std::string insertStr(std::to_string(++savedGoodId_));
    std::string newStr = std::string("G00000000").substr(0, 10 - insertStr.length()) + insertStr;
    return newStr;
}