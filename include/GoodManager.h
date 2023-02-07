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
    /**
     * @brief GoodManager的构造函数
     * @param dataFilePath 商品的保存和拉取的路径
     */
    GoodManager(std::string dataFilePath);

    /**
     * @brief GoodManager的析构函数
     * 销毁::GoodManager 的对象
     * @note 在释放 goods_ 容器中所有开辟的内存空间前,会调用 saveGoods() 来保存数据
     * @see ::goods_ ::saveGoods
     */
    ~GoodManager();

    /**
     * @brief 拉取商品数据
     * @return 是否成功
     * @retval true 拉取成功
     * @retval false 拉取失败
     */
    bool pullGoods();

    /**
     * @brief 保存商品数据
     * @return 是否成功
     * @retval true 保存成功
     * @retval false 保存失败
     */
    bool saveGoods() const;

    /**
     * @brief 添加商品
     * @param good 添加的商品的指针(开辟的内存空间的指针)
     */
    void addGoods(Good *good);

    /**
     * @brief 遍历所有商品
     * 对已有的商品的指针进行遍历，可以通过指针访问或修改 Good

     * @param func void (*func)(Good *good)
     */
    void traverse(void (*func)(Good *good)) const;

protected:
    std::vector<Good *> goods_; ///< 商品数组容器
    unsigned int goodNumber_;   ///< 商品数量
    unsigned int savedGoodId_;  ///< 生成过的id数量
    std::string dataFilePath_;  ///< 数据文件路径

    /**
     * @brief 获取一个新id，根据 savedUserId_
     * @note savedGoodId_ 自增1
     * @see ::savedGoodId_
     * @return 返回id U+9位数字
     */
    std::string getNewId();
};

#endif // GOODMANAGER_H
