#include "DataManager.h"

UserManager::UserManager(std::string dataFilePath, char idHead)
    : DataManager<User>(dataFilePath, idHead) {}



bool UserManager::loadData()
{
    FILE *fp = fopen(dataFilePath_.c_str(), "rb");
    if (fp == nullptr)
    {
        return false;
    }
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document doc;
    doc.ParseStream(is);
    fclose(fp);

    if (doc.HasMember("dataNumber") && doc["dataNumber"].IsUint())
        dataNumber_ = doc["dataNumber"].GetUint();

    if (doc.HasMember("idNumber") && doc["idNumber"].IsUint())
        idNumber_ = doc["idNumber"].GetUint();

    if (doc.HasMember("dataList") && doc["dataList"].IsArray())
    {
        const rapidjson::Value &vDataList = doc["dataList"];
        for (rapidjson::SizeType i = 0; i < vDataList.Size(); i++)
        {
            dataList_.push_back(newUser(vDataList[i]));
        }
    }
    dataNumber_ = doc["dataList"].Size();

    return true;
}

bool UserManager::saveData()
{
    rapidjson::Document doc;
    rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();
    doc.SetObject();

    doc.AddMember("dataNumber", dataNumber_, allocator);
    doc.AddMember("idNumber", idNumber_, allocator);

    rapidjson::Value vDataList(rapidjson::kArrayType);
    for (auto i = dataList_.begin(); i != dataList_.end(); ++i)
    {
        switch ((*i)->getType())
        {
        case User::ADMINISTRATOR:
            vDataList.PushBack(((Administrator *)*i)->toJSONObject(allocator), allocator);
            break;
        case User::BUYER:
            vDataList.PushBack(((Buyer *)*i)->toJSONObject(allocator), allocator);
            break;
        case User::SELLER:
            vDataList.PushBack(((Seller *)*i)->toJSONObject(allocator), allocator);
            break;
        default:
            break;
        }
    }
    doc.AddMember("dataList", vDataList, allocator);

    FILE *fp = fopen(dataFilePath_.c_str(), "wb"); // 非 Windows 平台使用 "w"
    char writeBuffer[65536];
    rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
    rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
    doc.Accept(writer);
    fclose(fp);

    return true;
}

User *UserManager::newUser(const rapidjson::Value &value)
{
    User *ptr = nullptr;
    unsigned int type = -1;
    if (value.HasMember("type") && value["type"].IsUint())
        type = value["type"].GetUint();

    switch (type)
    {
    case User::ADMINISTRATOR:
        ptr = new Administrator(value);
        break;
    case User::BUYER:
        ptr = new Buyer(value);
        break;
    case User::SELLER:
        ptr = new Seller(value);
        break;
    default:
        break;
    }
    return ptr;
}
