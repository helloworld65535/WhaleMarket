#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date
{
public:
    Date(unsigned int year = 2000, unsigned int month = 1, unsigned int day = 1)
        : year_(year), month_(month), day_(day) {}

    ~Date() {}

    bool isValidity();                         // 检测输入的年、月、日是否合法
    static bool isLeapYear(unsigned int year); // 判断year是否为闰年
    bool isLeapYear();                         // 判断当前Date是否为闰年
    void operator=(const Date &date);          // =赋值
    bool operator==(const Date &date);         // ==比较
    bool operator!=(const Date &date);         // !=比较
    bool operator>(const Date &date);          // >比较
    bool operator>=(const Date &date);         // >=比较
    bool operator<(const Date &date);          // <比较
    bool operator<=(const Date &date);         // <=比较

    friend std::ostream &operator<<(std::ostream &cout, const Date &date); // 输出到std::ostream
    friend std::istream &operator>>(std::istream &cin, Date &date);        // 从 std::istream 获取输入

    /*     Date getNextNDays(int n);      // 取得year-month-day的下n天日期
        Date getPreviousNDays(int n);  // 取得year-month-day的前n天日期
        int getDaysofDates(Date date); // 求当前日期与date之间相差的天数
        std::string showDate();        // 以“year-month-day”格式返回日期值 */

protected:
    unsigned int year_;
    unsigned int month_;
    unsigned int day_;

    /**
     * @brief 根据年份和月份返回天数
     * @param year 年份
     * @param month 月份
     * @return 该月有多少天
     */
    unsigned int getDaysOfMonth(unsigned int year, unsigned int month);

    /**
     * @brief 判断 value 是否在[Min, Max] 范围内
     * @param value 要判断的值
     * @param Min 左边界
     * @param Max 右边界
     * @return 是否在[Min, Max] 范围内
     */
    inline bool isInRange(unsigned int value, unsigned int Min, unsigned int Max);
};

#endif // DATE_H
