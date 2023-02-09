#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>

class Menu;

class Function
{
protected:
  std::string name_;
  bool (*function_)(void);
  Menu *nextMenu_;

public:
  Function(std::string name);
  Function(std::string name, bool (*function)(void));
  Function(std::string name, Menu *nextMenu);
  Function(
      std::string name,
      bool (*function)(void),
      Menu *nextMenu);

  // Getter & Setter

  const std::string &getName() const;
  Menu *getNextMenu() const;
  void setName(const std::string &name);
  void setFunction(bool (*function)(void));
  void setNextMenu(Menu *nextMenu);

  bool run();
};

/**
 * @brief 菜单类
 * @details
 * @note @name 使用步骤
 * 1、新建Menu 和 Function \n
 * 2、功能添加子界面
 * 3、界面添加功能
 *  @see
 * Menu::addFunction \n
 * Function::setNextMenu
 */
class Menu
{
protected:
  std::string name_;                  ///< 名称
  std::vector<Function *> functions_; ///< 功能[]
  Menu *fatherMenu_;                  ///< 父菜单

public:
  Menu(std::string name);

  // Getter & Setter

  const std::string &getName() const;
  Menu *getFatherMenu() const;
  void setName(const std::string &name);
  void setFatherMenu(Menu *fatherMenu);

  void display();

  void displayPath(Menu *);

  int getChoose() const;

  bool run(int choose);

  Menu *nextMenu(int choose);

  void addFunction(Function *function);
};

#endif // MENU_H
