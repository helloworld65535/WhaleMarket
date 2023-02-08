
#include "DataManager.h"
#include "Good.h"

int main(void)
{
    DataManager<Good> dataManager("good.json", 'G');
    dataManager.addData(new Good("good", "good1", 135.85, "这是一个商品1", "S000000001", Date(2023, 2, 8), Good::IN_SALE));
    dataManager.addData(new Good("good", "good2", 235.85, "这是一个商品2", "S000000002", Date(2023, 2, 8), Good::IN_SALE));
    dataManager.addData(new Good("good", "good3", 335.85, "这是一个商品3", "S000000003", Date(2023, 2, 8), Good::IN_SALE));

    return 0;
}