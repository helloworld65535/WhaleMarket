
#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <ostream>
#include "Date.h"

class Order
{
public:
    Order();

    Order(const std::string &id, const std::string &goodId, const std::string &sellerId, const Date &date,
          unsigned int quantity);

    /**
     * @defgroup 访问器
     *  @{
     */
    const std::string &getId() const;      ///< 访问id_
    const std::string &getGoodId() const;  ///< 访问goodId_
    const std::string &getBuyerId() const; ///< 访问buyerId_
    const Date &getDate() const;           ///< 访问date_
    unsigned int getQuantity() const;      ///< 访问quantity_
    /** @} */

    /**
     *  @defgroup 更改器
     *  @{
     */
    void setId(const std::string &id);            ///< 更改id_
    void setGoodId(const std::string &goodId);    ///< 更改goodId_
    void setBuyerId(const std::string &sellerId); ///< 更改buyerId_
    void setDate(const Date &date);               ///< 更改date_
    void setQuantity(unsigned int quantity);      ///< 更改quantity_
    /** @} */

    friend std::ostream &operator<<(std::ostream &out, const Order &order);
    friend std::istream &operator>>(std::istream &in, Order &order);

protected:
    std::string id_;        ///< 订单ID
    std::string goodId_;    ///< 商品Id
    std::string buyerId_;   ///< 买家ID
    Date date_;             ///< 购买日期
    unsigned int quantity_; ///< 购买的商品数量
};

#endif // ORDER_H
