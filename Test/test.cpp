
#include "DataManager.h"
#include "Good.h"

int main(void)
{
    DataManager<Good> dataManager("good.json", 'G');
    dataManager.loadData();

    dataManager.deleteData([](Good *good) -> bool
                           { return good->getName() == std::string("商品"); });

    return 0;
}