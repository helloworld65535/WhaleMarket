
#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <vector>

#include "User.h"

class UserManager
{
public:
    UserManager(const std::string dataFilePath);

    ~UserManager();

    /**
     * @brief 用户登陆
     * @param account 账号
     * @param password 密码
     * @return 登陆成功返回用户指针
     */
    User *loginAccount(std::string account, std::string password);

    /**
     * @brief 注册用户
     * @note 会自动调用 getNewId() 设置id
     * @param user 要注册的用户指针
     * @return 注册用户是否成功
     */
    bool registerUser(User *user);

    /**
     * @brief 注销用户
     * @param user 要注销的用户指针
     * @return 注销用户是否成功
     */
    bool CancelUser(User *user);

    bool pullUsers();

    bool saveUsers();

protected:
    std::vector<User *> users_; /* vector容器管理user */
    unsigned int userNumber_;   /* user数量 */
    unsigned int savedUserId_;  /* 生成过的id数量 */
    std::string dataFilePath_;

    /**
     * @brief 获取一个新id，根据 savedUserId_
     * @note savedUserId_自增1
     * @return 返回id U+9位数字
     */
    std::string getNewId();
};

#endif // USERMANAGER_H
