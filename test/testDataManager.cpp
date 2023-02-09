
#include "DataManager.h"
#include "Good.h"
#include "Order.h"

int testDataManager(void)
{
    UserManager userManager("User.json", 'U');
    userManager.loadData();
    // userManager.addData(new Administrator("Admin", "Admin", "123456"));
    // userManager.addData(new Seller("Seller", "Seller", "123456","昵称Seller","13207900790","北京北京",Date(2023,2,2),5000,NormalUser::NORMAL,23));
    // userManager.addData(new Buyer("Buyer", "Buyer", "123456","昵称Buyer","13207900790","北京北京",Date(2023,2,2),5000,NormalUser::NORMAL,23));

    userManager.traversal([](User *user) -> void
                          { std::cout << user->getAccount() << std::endl; });
    userManager.saveData();
    return 0;
}