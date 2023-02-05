/**
 * @file GoodManager.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-02-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef GOODMANAGER_H
#define GOODMANAGER_H

#include <vector>
#include "Good.h"

class GoodManager
{
public:
    GoodManager();

    bool pullGoods();
    bool saveGoods() const;

protected:
    std::vector<Good *> goods_; ///< 商品数组容器
    unsigned int goodNumber_;   ///< good数量
    unsigned int savedGoodId_;  ///< 生成过的id数量
    std::string dataFilePath_;  ///< 路径

    /**
     * @brief 获取一个新id，根据 savedUserId_
     * @note ::savedUserId_ 自增1
     * @return 返回id U+9位数字
     */
    std::string getNewId();
};

#endif // GOODMANAGER_H
