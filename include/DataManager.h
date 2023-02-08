
#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <vector>
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/writer.h"

template <class T>
class DataManager
{
public:
    DataManager(std::string dataFilePath, char idHead);
    virtual ~DataManager();

    virtual bool loadData();
    virtual bool saveData();
    virtual void addData(T *data);

protected:
    std::vector<T *> dataList_; ///< 数据列表
    unsigned int dataNumber_;   ///< 数据数量
    unsigned int idNumber_;     ///< 生成过的id
    std::string dataFilePath_;  ///< 数据文件路径
    char idHead_;

    virtual std::string getNewId();
};

template <class T>
inline DataManager<T>::DataManager(std::string dataFilePath, char idHead)
{
    dataFilePath_ = dataFilePath;
    idHead_ = idHead;
    dataNumber_ = 0;
    idNumber_ = 0;
}

template <class T>
inline DataManager<T>::~DataManager()
{
    saveData();
    for (auto i = dataList_.begin(); i != dataList_.end(); ++i)
    {
        delete (*i);
        (*i) = nullptr;
    }
}

template <class T>
bool DataManager<T>::loadData()
{
    return false;
}

template <class T>
bool DataManager<T>::saveData()
{
    /**
     * @details
     * 以json文件保存
     *  {
     *   "dataNumber": 0,
     *   "idNumber": 0,
     *   "dataList": ["class T1", "class T2", "class T3", "class Tn"]
     *  }
     */
    rapidjson::Document doc;
    rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();
    doc.SetObject();

    doc.AddMember("dataNumber", dataNumber_, allocator);
    doc.AddMember("idNumber", idNumber_, allocator);

    rapidjson::Value vDataList(rapidjson::kArrayType);
    for (auto i = dataList_.begin(); i != dataList_.end(); ++i)
    {
        vDataList.PushBack((*i)->toJSONObject(allocator), allocator);
    }
    doc.AddMember("dataList", vDataList, allocator);

    FILE *fp = fopen("output.json", "wb"); // 非 Windows 平台使用 "w"
    char writeBuffer[65536];
    rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
    rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
    doc.Accept(writer);
    fclose(fp);

    return true;
}

template <class T>
void DataManager<T>::addData(T *data)
{
    data->setId(getNewId());
    dataList_.push_back(data);
    ++dataNumber_;
}

template <class T>
inline std::string DataManager<T>::getNewId()
{
    char s[11] ;
    sprintf(s, "%c%09u", idHead_, ++idNumber_);
    return std::string(s);
}

#endif // DATAMANAGER_H