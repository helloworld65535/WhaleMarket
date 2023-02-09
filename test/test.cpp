#include "Menu.h"

int main(void)
{
    // std::vector<Menu *> menus;

    Menu *menu = new Menu("首页");
    Function *func1 = new Function("功能一");
    Function *func2 = new Function("功能二");
    
    Menu *menu1 = new Menu("功能一界面");
    Menu *menu2 = new Menu("功能二界面");

    func1->setNextMenu(menu1);
    func2->setNextMenu(menu2);

    menu->addFunction(func1);
    menu->addFunction(func2);

    Menu *main = menu;



    return 0;
}