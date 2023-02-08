#include "Menu.h"
#include <iostream>

Function::Function(std::string name, bool (*function)(void), Menu *nextMenu = nullptr)
    : name_(name), function_(function_), nextMenu_(nextMenu) {}

Function::Function(std::string name, Menu *nextMenu)
    : name_(name), nextMenu_(nextMenu) {}

bool Function::run()
{
    if (function_ == nullptr)
        return true;
    return function_();
}

Menu *Function::getNextMenu() const
{
    return nextMenu_;
}

void Function::setNextMenu(Menu *menu)
{
    nextMenu_ = menu;
}

std::string Function::getName() const
{
    return name_;
}

Menu::Menu(std::string name)
    : name_(name)
{
    fatherMenu_ = nullptr;
}

void Menu::display()
{
    /*
    ===================
    | 1\name | 2\name |
    ===================
    */

    std::string str = "|";
    unsigned int length = 1;
    for (int i = 0; i < functions_.size(); i++)
    {
        str += " "+std::to_string(i)+"、" + functions_[i]->getName() + " |";
    }
    for (int i = 0; i < str.size(); i++)
        std::cout << '=';
    std::cout << std::endl
              << str << std::endl;

    for (int i = 0; i < str.size(); i++)
        std::cout << '=';
    std::cout << std::endl;
}

bool Menu::run()
{
    std::string chooseStr;
    unsigned int choose = -1;
    std::cout << "请输入你的选择：" << std::endl;
    do
    {
        std::cin >> chooseStr;
        try
        {
            choose = std::stoll(chooseStr);
        }
        catch (const std::exception &e)
        {
        	std::cout<<"输入错误！请重新输入："<<std::endl;
        }

    } while (choose>functions_.size());

    return functions_[choose]->run();
}

void Menu::addFunction(Function *function)
{
    functions_.push_back(function);
}
