#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>

class Function
{
public:
  Function(
      std::string name,
      bool (*function)(void),
      Menu *nextMenu);
  Function(std::string name,Menu *nextMenu);
  bool run();

  Menu *getNextMenu() const;
  void setNextMenu(Menu *menu);
	std::string getName()const;
protected:
  std::string name_;
  bool (*function_)(void);
  Menu *nextMenu_;
};

class Menu
{
protected:
  std::string name_;
	std::vector<Function *> functions_;
	Menu *fatherMenu_;

public:
	Menu(std::string name);

  void display();

	bool run();

  void addFunction(Function *function);
};

#endif // MENU_H
