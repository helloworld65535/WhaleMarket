#ifndef USER_H
#define USER_H

#include <string>
#include <fstream>
#include "Date.h"
class User
{
public:
    enum userType
    {
        SELLER,        /* 卖家 */
        BUYER,         /* 买家 */
        ADMINISTRATOR, /* 管理员 */
    };
    typedef enum userType UserType;

    explicit User(UserType type);
    User() {}
    ~User() {}

    User(const std::string &id, const std::string &account, const std::string &password, UserType type);

    /// @brief getId
    const std::string &getId() const;
    /// @brief getAccount
    const std::string &getAccount() const;
    /// @brief getPassword
    const std::string &getPassword() const;
    /// @brief getType
    UserType getType() const;

    /// @brief setId
    void setId(const std::string &id);
    /// @brief setAccount
    void setAccount(const std::string &account);
    /// @brief setPassword
    void setPassword(const std::string &password);

    /**
     * @brief 账号验证
     * @param account 账号
     * @param password 密码
     * @return 账号密码符合则返回真
     */
    virtual bool validateAccountPassword(std::string account, std::string password) const;

    virtual bool validateAccount(std::string account) const;

    /// @brief 将用户数据输出到文件 @param out 文件输出流
    virtual void outputData(std::ofstream &out);

    /// @brief 从文件获取数据 @param in 文件输入流
    virtual void inputData(std::ifstream &in);

protected:
    std::string id_;       /* ID */
    std::string account_;  /* 账号8~20位 */
    std::string password_; /* 密码8~20位 */
    UserType type_;        /* 用户类型 */
};

class Administrator : public User
{
public:
    Administrator();

    ~Administrator() {}

    /**
     * @brief Administrator构造
     * @param id ID
     * @param account 账号8~20位
     * @param password 密码8~20位
     */
    Administrator(const std::string &id, const std::string &account, const std::string &password);
};

class NormalUser : public User
{
public:
    enum accountState
    {
        NORMAL, /* 正常 */
        BANED,  /* 封禁 */
    };
    typedef enum accountState AccountState;

    NormalUser() {}
    NormalUser(UserType type);
    ~NormalUser() {}

    NormalUser(const std::string &id, const std::string &account, const std::string &password, UserType type,
               const std::string &nickName, const std::string &phoneNumber, const std::string &address,
               const Date &registrationDate, double balance, AccountState accountState);
    /// @brief getNickName
    const std::string &getNickName() const;
    /// @brief getPhoneNumber
    const std::string &getPhoneNumber() const;
    /// @brief getAddress
    const std::string &getAddress() const;
    /// @brief getRegistrationDate
    const Date &getRegistrationDate() const;
    /// @brief getBalance
    double getBalance() const;
    /// @brief getAccountState
    AccountState getAccountState() const;

    /// @brief setNickName
    void setNickName(const std::string &nickName);
    /// @brief setPhoneNumber
    void setPhoneNumber(const std::string &phoneNumber);
    /// @brief setAddress
    void setAddress(const std::string &address);
    /// @brief setBalance
    void setBalance(double balance);
    /// @brief setAccountState
    void setAccountState(AccountState accountState);
    void setAccountState(unsigned accountState);

    /**
     * @brief 增加余额,失败则余额不变
     * @param amount 量
     * @return 是否成功
     */
    bool addBalance(const double amount);

    /**
     * @brief 扣除余额,失败则余额不变
     * @param amount 量
     * @return 是否成功
     */
    bool subBalance(const double amount);

    /// @brief 将用户数据输出到文件 @param out 文件输出流
    virtual void outputData(std::ofstream &out) override;

    /// @brief 从文件获取数据 @param in 文件输入流
    virtual void inputData(std::ifstream &in) override;

protected:
    std::string nickName_;      /* 昵称 */
    std::string phoneNumber_;   /* 电话号码 */
    std::string address;        /* 地址 */
    Date registrationDate_;     /* 注册时间 */
    double balance_;            /* 余额 */
    AccountState accountState_; /* 账号状态 */
};

class Buyer : public NormalUser
{
public:
    Buyer();

    /**
     * @brief Buyer构造
     * @param id ID
     * @param account 账号8~20位
     * @param password 密码8~20位
     * @param nickName 昵称
     * @param phoneNumber 电话号码
     * @param address 地址
     * @param registrationDate 注册时间
     * @param balance 余额
     * @param accountState 账号状态
     * @param consumptionPoints 消费积分
     */
    Buyer(const std::string &id, const std::string &account, const std::string &password,
          const std::string &nickName, const std::string &phoneNumber, const std::string &address,
          const Date &registrationDate, double balance, AccountState accountState,
          unsigned int consumptionPoints);

    /// @brief getConsumptionPoints
    unsigned int getConsumptionPoints() const;

    /// @brief setConsumptionPoints
    void setConsumptionPoints(unsigned int consumptionPoints);

    /**
     * @brief 增加积分,失败则积分不变
     * @param amount 量
     * @return 是否成功
     */
    bool addConsumptionPoints(const unsigned int amount);

    /**
     * @brief 扣除积分,失败则积分不变
     * @param amount 量
     * @return 是否成功
     */
    bool subConsumptionPoints(const unsigned int amount);

    /// @brief 将用户数据输出到文件 @param out 文件输出流
    virtual void outputData(std::ofstream &out) override;

    /// @brief 从文件获取数据 @param in 文件输入流
    virtual void inputData(std::ifstream &in) override;

protected:
    unsigned int consumptionPoints_; /* 消费积分 */
};

class Seller : public NormalUser
{
public:
    Seller();

    /**
     * @brief Seller构造
     * @param id ID
     * @param account 账号8~20位
     * @param password 密码8~20位
     * @param nickName 昵称
     * @param phoneNumber 电话号码
     * @param address 地址
     * @param registrationDate 注册时间
     * @param balance 余额
     * @param accountState 账号状态
     * @param tradingVolume 交易量
     */
    Seller(const std::string &id, const std::string &account, const std::string &password,
           const std::string &nickName, const std::string &phoneNumber, const std::string &address,
           const Date &registrationDate, double balance, AccountState accountState, unsigned int tradingVolume);

    /// @brief getTradingVolume
    unsigned int getTradingVolume() const;

    /// @brief 交易量增加 1
    void addtradingVolume();

    /// @brief 将用户数据输出到文件 @param out 文件输出流
    virtual void outputData(std::ofstream &out) override;

    /// @brief 从文件获取数据 @param in 文件输入流
    virtual void inputData(std::ifstream &in) override;

protected:
    unsigned int tradingVolume_; /* 交易量 */
};

#endif // USER_H
