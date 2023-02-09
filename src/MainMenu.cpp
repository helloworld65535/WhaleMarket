#include "MainMenu.h"
#include <unordered_map>

const char head[] = " __          ___           _        __  __            _        _   \n \\ \\        / / |         | |      |  \\/  |          | |      | |  \n  \\ \\  /\\  / /| |__   __ _| | ___  | \\  / | __ _ _ __| | _____| |_ \n   \\ \\/  \\/ / | '_ \\ / _` | |/ _ \\ | |\\/| |/ _` | '__| |/ / _ \\ __|\n    \\  /\\  /  | | | | (_| | |  __/ | |  | | (_| | |  |   <  __/ |_ \n     \\/  \\/   |_| |_|\\__,_|_|\\___| |_|  |_|\\__,_|_|  |_|\\_\\___|\\__|\n\n\n ";

bool Buyer_registration()
{
    printf("功能");
    system("pause");
    return true;
} ///< 买家注册
bool Seller_registration()
{
    printf("功能");
    system("pause");
    return true;
} ///< 卖家注册
bool Administrator_login()
{
    printf("功能");
    system("pause");
    return true;
} ///< 管理员登陆
bool Buyer_login()
{
    printf("功能");
    system("pause");
    return true;
} ///< 买家登陆
bool Retrieve_password()
{
    printf("功能");
    system("pause");
    return true;
} ///< 找回
bool Show_all_users()
{
    printf("功能");
    system("pause");
    return true;
} ///< 显示所有用户
bool Delete_a_user()
{
    printf("功能");
    system("pause");
    return true;
} ///< 删除用户
bool Find_a_user()
{
    printf("功能");
    system("pause");
    return true;
} ///< 查找用户

MainMenu::MainMenu()
{
    homeMenu_ = new Menu("首页");

    std::unordered_map<std::string, Menu *> menuHash;
    std::unordered_map<std::string, Function *> funcHash;

    // #注册
    menuHash["注册界面"] = new Menu("注册界面");
    funcHash["注册"] = new Function("注册", menuHash["注册界面"]);
    homeMenu_->addFunction(funcHash["注册"]);

    // funcHash["买家注册"] = new Function("买家注册", Buyer_registration);
    // funcHash["卖家注册"] = new Function("卖家注册", Seller_registration);
    menuHash["注册界面"]->addFunction(new Function("买家注册", Buyer_registration));
    menuHash["注册界面"]->addFunction(new Function("卖家注册", Seller_registration));
    // #登陆
    menuHash["登陆界面"] = new Menu("登陆界面");
    funcHash["登陆"] = new Function("登陆", menuHash["登陆界面"]);
    homeMenu_->addFunction(funcHash["登陆"]);

    // #管理员登陆
    menuHash["管理员界面"] = new Menu("管理员界面");
    funcHash["管理员登陆"] = new Function("管理员登陆", Administrator_login, menuHash["管理员界面"]);
    menuHash["登陆界面"]->addFunction(funcHash["管理员登陆"]);

    // #用户管理
    menuHash["用户管理界面"] = new Menu("用户管理界面");
    funcHash["用户管理"] = new Function("用户管理", menuHash["用户管理界面"]);
    menuHash["管理员界面"]->addFunction(funcHash["用户管理"]);

    funcHash["显示所有用户"] = new Function("显示所有用户", Show_all_users);
    menuHash["用户管理界面"]->addFunction(funcHash["显示所有用户"]);

    funcHash["删除用户"] = new Function("删除用户", Delete_a_user);
    menuHash["用户管理界面"]->addFunction(funcHash["删除用户"]);

    funcHash["查找用户"] = new Function("查找用户", Find_a_user);
    menuHash["用户管理界面"]->addFunction(funcHash["查找用户"]);

    // #商品管理
    menuHash["商品管理界面"] = new Menu("商品管理界面");
    funcHash["商品管理"] = new Function("商品管理", menuHash["商品管理界面"]);
    menuHash["管理员界面"]->addFunction(funcHash["商品管理"]);
    // #订单管理
    menuHash["订单管理界面"] = new Menu("订单管理界面");
    funcHash["订单管理"] = new Function("订单管理", menuHash["订单管理界面"]);
    menuHash["管理员界面"]->addFunction(funcHash["订单管理"]);

    // #买家登陆
    menuHash["买家界面"] = new Menu("买家界面");
    funcHash["买家登陆"] = new Function("买家登陆", Buyer_login, menuHash["买家界面"]);
    menuHash["登陆界面"]->addFunction(funcHash["买家登陆"]);
    // #卖家登陆
    menuHash["卖家界面"] = new Menu("卖家界面");
    funcHash["卖家登陆"] = new Function("卖家登陆", Buyer_login, menuHash["卖家界面"]);
    menuHash["登陆界面"]->addFunction(funcHash["卖家登陆"]);

    // #找回
    menuHash["找回界面"] = new Menu("找回界面");
    funcHash["找回"] = new Function("找回", Retrieve_password);
    homeMenu_->addFunction(funcHash["找回"]);
}

void MainMenu::start()
{
    // printf("%s", head);
    Menu *main = homeMenu_;
    while (main)
    {
        main->display();
        int choose = main->getChoose();
        main = main->nextMenu(choose);
    }
}
