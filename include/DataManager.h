
#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <vector>
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/writer.h"
#include "rapidjson/filereadstream.h"

/**
 * @brief DataManager模板类
 * @tparam T 对该类进行数据管理
 * @pre T类必须要有:\n
 * T(const rapidjson::Value &value) 构造函数\n
 * rapidjson::Value toJSONObject(rapidjson::Document::AllocatorType &allocator) 成员函数：将数据转为json格式
 */
template <class T>
class DataManager
{
public:
    DataManager(std::string dataFilePath, char idHead);
    virtual ~DataManager();

    /**
     * @brief 从 dataFilePath_ 文件中加载数据
     * @return 是否加载成功
     * @details
     * 使用到 T(const rapidjson::Value &value) 的构造函数来创建对象
     */
    virtual bool loadData();

    /**
     * @brief 保存数据到 dataFilePath_ 文件中
     * @return 是否保存成功
     * @details
     * 使用到T类的 toJSONObject() 的成员函数
     */
    bool saveData();

    /**
     * @brief 添加 T 的对象
     * @param data 指针，指向开辟的内存空间
     * @details @name 使用示例
     * @code {.cpp}
     * DataManager  dataManager;
     * dataManager.addData(new T(...));
     * @endcode
     */
    void addData(T *data);

    /**
     * @brief 遍历
     * @param func 对每一个T进行操作 void (*func)(T *)
     */
    void traversal(void (*func)(T *));

    /**
     * @brief 寻找满足条件的T
     * @param comparator 比较器 bool (*comparator)(T *)
     * @return std::vector<T *>
     */
    std::vector<T *> findData(bool (*comparator)(T *));

    /**
     * @brief 根据指针删除数据
     * @param data T 对象指针
     */
    void deleteData(T *data);

    /**
     * @brief 根据条件删除数据
     * @param comparator 条件
     */
    void deleteData(bool (*comparator)(T *));

protected:
    std::vector<T *> dataList_; ///< 数据列表
    unsigned int dataNumber_;   ///< 数据数量
    unsigned int idNumber_;     ///< 生成过的id
    std::string dataFilePath_;  ///< 数据文件路径
    char idHead_;               ///< 生成ID的首字母

    /**
     * @brief 获取一个新的唯一ID
     * @return 唯一ID
     * @note @see  调用后 ::idNumber_ 自增1
     */
    std::string getNewId();
};

template <class T>
 DataManager<T>::DataManager(std::string dataFilePath, char idHead)
{
    dataFilePath_ = dataFilePath;
    idHead_ = idHead;
    dataNumber_ = 0;
    idNumber_ = 0;
}

template <class T>
 DataManager<T>::~DataManager()
{
    // saveData();
    for (auto i = dataList_.begin(); i != dataList_.end(); ++i)
    {
        delete (*i);
        (*i) = nullptr;
    }
}

template <class T>
bool DataManager<T>::loadData()
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
            dataList_.push_back(new T(vDataList[i]));
        }
    }
    dataNumber_ = doc["dataList"].Size();

    return true;
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

    FILE *fp = fopen(dataFilePath_.c_str(), "wb"); // 非 Windows 平台使用 "w"
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
void DataManager<T>::traversal(void (*func)(T *))
{
    for (auto &&i : dataList_)
    {
        func(i);
    }
}

template <class T>
std::vector<T *> DataManager<T>::findData(bool (*comparator)(T *))
{
    std::vector<T *> result;
    for (auto &&i : dataList_)
    {
        if (comparator(i))
        {
            result.push_back(i);
        }
    }
    return result;
}

template <class T>
void DataManager<T>::deleteData(T *data)
{
    for (auto i = dataList_.begin(); i != dataList_.end();)
    {
        if ((*i) == data)
        {
            delete (*i);
            i = dataList_.erase(i);
            --dataNumber_;
            continue;
        }
        ++i;
    }
}

template <class T>
inline void DataManager<T>::deleteData(bool (*comparator)(T *))
{
    for (auto i = dataList_.begin(); i != dataList_.end();)
    {
        if (comparator(*i))
        {
            delete (*i);
            i = dataList_.erase(i);
            --dataNumber_;
            continue;
        }
        ++i;
    }
}

template <class T>
inline std::string DataManager<T>::getNewId()
{
    char s[11];
    sprintf(s, "%c%09u", idHead_, ++idNumber_);
    return std::string(s);
}

#include "User.h"
class UserManager : public DataManager<User>
{
public:
    UserManager(std::string dataFilePath, char idHead);

    virtual bool loadData();
    virtual bool saveData();

private:
    User *newUser(const rapidjson::Value &value);
};

#endif // DATAMANAGER_H