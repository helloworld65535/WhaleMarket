#include "User.h"
#include "Date.h"
#include <fstream>

int testAdministrator(void)
{
    User *user;

    std::ifstream in("out.txt", std::ios::in);
    if (in.is_open())
    {
        std::string str;
        in >> str;
        std::cout << "UserType:" << str << std::endl;
        user = new Administrator();
        user->inputData(in);
    }
    else
    {
        user = new Administrator("Root", "Administrator", "123456");
    }
    in.close();
    if (user->validateAccount("Administrator", "123456"))
        std::cout << "登陆成功" << std::endl;
    else
        std::cout << "登陆失败" << std::endl;

    user->setPassword("111111");

    std::ofstream out("out.txt", std::ios::out);
    user->outputData(out);
    out.close();

    return 0;
}

int testDate(void)
{
    Date date;
    std::cin >> date;
    std::cout << date << std::endl;

    return 0;
}

int testBuyer(void)
{
    Buyer *user;

    std::ifstream in("out.txt", std::ios::in);
    if (in.is_open())
    {
        std::string str;
        in >> str;
        std::cout << "UserType:" << str << std::endl;
        user = new Buyer();
        user->inputData(in);
    }
    else
    {
        user = new Buyer("U000000000", "Buyer0", "123456", "零元购", "13272890790",
                         "北京北京", Date(2023, 2, 2), 0, NormalUser::NORMAL, 0);
    }
    in.close();

    user->addBalance(50);
    user->addConsumptionPoints(50);
    user->subBalance(100);
    user->subConsumptionPoints(100);

    if (user->validateAccount("Buyer0", "111111"))
        std::cout << "登陆成功" << std::endl;
    else
        std::cout << "登陆失败" << std::endl;
    user->setPassword("111111");

    std::ofstream out("out.txt", std::ios::out);
    user->outputData(out);
    out.close();

    return 0;
}

int testSeller(void)
{
    Seller *user;

    std::ifstream in("out.txt", std::ios::in);
    if (in.is_open())
    {
        std::string str;
        in >> str;
        std::cout << "UserType:" << str << std::endl;
        user = new Seller();
        user->inputData(in);
    }
    else
    {
        user = new Seller("U000000000", "Seller0", "123456", "黑星", "13272890790",
                         "北京北京", Date(2023, 2, 2), 0, NormalUser::NORMAL, 0);
    }
    in.close();

    user->addBalance(50);
    user->addtradingVolume();
    user->subBalance(100);

    if (user->validateAccount("Seller0", "111111"))
        std::cout << "登陆成功" << std::endl;
    else
        std::cout << "登陆失败" << std::endl;
    user->setPassword("111111");

    std::ofstream out("out.txt", std::ios::out);
    user->outputData(out);
    out.close();

    return 0;
}

int main(void)
{
    
    return 0;
}