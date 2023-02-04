

#ifndef GOOD_H
#define GOOD_H

#include <iostream>
#include "Date.h"

class Good
{
public:
    /// @brief 商品状态枚举
    typedef enum
    {
        IN_SALE,  ///< 销售中
        SOLD_OUT, ///< 已售完
    } GoodState;

    Good();

    Good(const std::string &id, const std::string &name, double price, const std::string &description,
         const std::string &sellerId, const Date &shelfTime, GoodState goodState);

    const std::string &getId() const;

    void setId(const std::string &id);

    const std::string &getName() const;

    void setName(const std::string &name);

    double getPrice() const;

    void setPrice(double price);

    const std::string &getDescription() const;

    void setDescription(const std::string &description);

    const std::string &getSellerId() const;

    void setSellerId(const std::string &sellerId);

    const Date &getShelfTime() const;

    void setShelfDate(const Date &shelfDate);

    GoodState getGoodState() const;

    void setGoodState(GoodState goodState);


    friend std::ostream &operator<<(std::ostream &out, const Good &good);

    friend std::istream &operator>>(std::istream &in, Good &good);

protected:
    std::string id_;          ///< 商品ID
    std::string name_;        ///< 名称
    double price_;            ///< 价格
    std::string description_; ///< 描述
    std::string sellerId_;    ///< 卖家ID
    Date shelfDate_;          ///< 上架时间
    GoodState goodState_;     ///< 商品状态
};

#endif // GOOD_H
