

#include "UserManager.h"

int testregisterUser(void)
{
    UserManager userManager("test.txt");

    userManager.registerUser(new Administrator("12", "admin", "123456"));
    userManager.registerUser(new Buyer("12", "Buyer", "123456", "买买买", "07901234123", "北京北京", Date(2023, 2, 3), 0, NormalUser::NORMAL, 0));
    userManager.registerUser(new Seller("12", "Seller", "123456", "卖卖卖", "07904321321", "上海上海", Date(2023, 2, 2), 10, NormalUser::NORMAL, 2));
    return 0;
}
int testpullUsers(void)
{
    UserManager userManager("test.txt");
    userManager.pullUsers();

    std::cout << "结束" << std::endl;
    return 0;
}
int testloginAccount(void)
{
    UserManager userManager("test.txt");
    userManager.pullUsers();
    Administrator *user = (Administrator *)userManager.loginAccount("admin", "123456");
    if (user)
    {
        std::cout << "登陆成功" << std::endl;
    }
    else
    {
        std::cout << "登陆失败" << std::endl;
    }

    return 0;
}
int testCancelUser(void)
{
    UserManager userManager("test.txt");
    userManager.pullUsers();
    User *user = userManager.loginAccount("Buyer", "123456");
    if (user)
    {
        std::cout << "登陆成功" << std::endl;
        std::cout << "注销结果" << userManager.CancelUser(user);
    }
    else
    {
        std::cout << "登陆失败" << std::endl;
    }

    return 0;
}

int testregisterUser2(void)
{
    UserManager userManager("test.txt");
    userManager.pullUsers();
    std::cout << "注册存在的账号" << std::endl;
    std::cout << "注册结果" << userManager.registerUser(new Administrator("12", "admin", "123456"));

    return 0;
}
int main(void)
{
    
    testpullUsers();
    return 0;
}