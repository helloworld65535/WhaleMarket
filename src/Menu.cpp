
#include "Menu.h"
#include <iostream>

Function::Function(std::string name)
    : name_(name)
{
    function_ = nullptr;
    nextMenu_ = nullptr;
}

Function::Function(std::string name, bool (*function)(void))
    : name_(name), function_(function)
{
    nextMenu_ = nullptr;
}

Function::Function(std::string name, bool (*function)(void), Menu *nextMenu)
    : name_(name), function_(function), nextMenu_(nextMenu) {}

Function::Function(std::string name, Menu *nextMenu)
    : name_(name), nextMenu_(nextMenu)
{
    function_ = nullptr;
}

const std::string &Function::getName() const
{
    return name_;
}

Menu *Function::getNextMenu() const
{
    return nextMenu_;
}

void Function::setName(const std::string &name)
{
    name_ = name;
}

void Function::setFunction(bool (*function)(void))
{
    function_ = function;
}

void Function::setNextMenu(Menu *nextMenu)
{
    nextMenu_ = nextMenu;
}

bool Function::run()
{
    if (function_ == nullptr)
        return true;
    return function_();
}

//============================================================================

Menu::Menu(std::string name)
    : name_(name)
{
    fatherMenu_ = nullptr;
}

const std::string &Menu::getName() const
{
    return name_;
}

Menu *Menu::getFatherMenu() const
{
    return fatherMenu_;
}

void Menu::setName(const std::string &name)
{
    name_ = name;
}

void Menu::setFatherMenu(Menu *fatherMenu)
{
    fatherMenu_ = fatherMenu;
}

void Menu::display()
{
    /*
    ===================
    | 1\name | 2\name |
    */
    system("cls");
    displayPath(this);
    std::cout << std::endl;
    std::string str = "| 0、返回 |";

    if (fatherMenu_ == nullptr)
        str = "| 0:退出 |";
    unsigned int length = 1;
    for (int i = 0; i < functions_.size(); i++)
    {
        str += " " + std::to_string(i + 1) + ":" + functions_[i]->getName() + " |";
    }
    for (int i = 0; i < str.size(); i++)
        std::cout << '=';
    std::cout << std::endl
              << str << std::endl;

    for (int i = 0; i < str.size(); i++)
        std::cout << '=';
    std::cout << std::endl;
}

void Menu::displayPath(Menu *menu)
{
    if (menu == nullptr)
        return;
    displayPath(menu->fatherMenu_);
    std::cout << ">" << menu->getName();
}

int Menu::getChoose() const
{
    std::string str;
    int choose = -1;
    std::cout << "请输入你的选择：" << std::endl;

    try
    {
        std::cin >> str;
        choose = std::stoi(str);
    }
    catch (const std::exception &e)
    {
        choose = -1;
    }

    return choose;
}

bool Menu::run(int choose)
{
    if (choose > 0 && choose <= functions_.size())
    { // 功能
        return functions_[choose - 1]->run();
    }
    else if (choose == 0)
    { // 返回
    }
    else
    { // 输入错误
        std::cout << "输入错误请重试！" << std::endl;
    }
    return false;
}

Menu *Menu::nextMenu(int choose)
{
    if (choose > 0 && choose <= functions_.size())
    { // 功能
        if (functions_[choose - 1]->run())
        {
            return functions_[choose - 1]->getNextMenu();
        }
    }
    else if (choose == 0)
    { // 返回
        return fatherMenu_;
    }
    else
    { // 输入错误
        std::cout << "输入错误请重试！" << std::endl;
        system("pause");
    }
    return this;
}

void Menu::addFunction(Function *function)
{
    functions_.push_back(function);

    Menu *next = function->getNextMenu();
    if (next != nullptr)
    {
        next->setFatherMenu(this);
    }
    else
    {
        function->setNextMenu(this);
    }
}
