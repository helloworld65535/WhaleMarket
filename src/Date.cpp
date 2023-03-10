#include "Date.h"
#include <string>

static const unsigned int daysOfLeapYear[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};   // 闰年天数
static const unsigned int daysOfCommonYear[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // 平年天数

bool Date::isValidity()
{
    if (isInRange(year_, 0, 9999))
        if (isInRange(month_, 1, 12))
        {
            if (day_ <= getDaysOfMonth(year_, month_))
                return true;
        }
    return false;
}

bool Date::isLeapYear(unsigned int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool Date::isLeapYear()
{
    return isLeapYear(year_);
}

void Date::operator=(const Date &date)
{
    year_ = date.year_;
    month_ = date.month_;
    day_ = date.day_;
}

void Date::operator=(const rapidjson::Value &value)
{
    if (value.HasMember("year") && value["year"].IsUint())
        year_ = value["year"].GetUint();
    if (value.HasMember("month") && value["month"].IsUint())
        month_ = value["month"].GetUint();
    if (value.HasMember("day") && value["day"].IsUint())
        day_ = value["day"].GetUint();
}

bool Date::operator==(const Date &date)
{
    return ((year_ == date.year_) && (month_ == date.month_) && (day_ == date.day_));
}

bool Date::operator!=(const Date &date)
{
    return !((*this) == date);
}

bool Date::operator>(const Date &date)
{
    if ((*this) == date)
        return false;
    if (year_ < date.year_)
    {
        return false;
    }
    else if (month_ < date.month_)
    {
        return false;
    }
    else if (day_ < date.day_)
    {
        return false;
    }
    return true;
}

bool Date::operator>=(const Date &date)
{
    if ((*this) != date)
    {
        if (year_ < date.year_)
        {
            return false;
        }
        else if (month_ < date.month_)
        {
            return false;
        }
        else if (day_ < date.day_)
        {
            return false;
        }
    }
    return true;
}

bool Date::operator<(const Date &date)
{
    return !((*this) >= date);
}

bool Date::operator<=(const Date &date)
{
    return !((*this) > date);
}

std::string Date::toString()
{
    char s[11];
    sprintf(s, "%04u/%02u/%02u", year_, month_, day_);
    std::string str = s;
    return str;
}

rapidjson::Value Date::toJSONObject(rapidjson::Document::AllocatorType &allocator)
{
    rapidjson::Value vObject(rapidjson::kObjectType);
    vObject.AddMember("year", year_, allocator);
    vObject.AddMember("month", month_, allocator);
    vObject.AddMember("day", day_, allocator);
    return vObject;
}

unsigned int Date::getDaysOfMonth(unsigned int year, unsigned int month)
{
    if (isLeapYear(year))
    {
        return daysOfLeapYear[month];
    }
    else
    {
        return daysOfCommonYear[month];
    }
}

bool Date::isInRange(unsigned int value, unsigned int Min, unsigned int Max)
{
    return ((value >= Min) && (value <= Max));
}

std::ostream &operator<<(std::ostream &cout, const Date &date)
{
    char s[11] = "YYYY-MM-DD";
    sprintf(s, "%04u-%02u-%02u", date.year_, date.month_, date.day_);

    cout << s;
    return cout;
}

std::istream &operator>>(std::istream &in, Date &date)
{
    std::string str;
    in >> str;
    date.year_ = std::stoul(str.substr(0, 4));
    date.month_ = std::stoul(str.substr(5, 2));
    date.day_ = std::stoul(str.substr(8, 2));
    return in;
}
