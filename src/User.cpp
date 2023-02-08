#include "User.h"
#include <cmath>

// User Begin ================================================================================================

User::User(User::UserType type) : type_(type) {}

User::User(const rapidjson::Value &value) : User(User::SELLER)
{
    if (!value.IsObject())
        return;
    if (value.HasMember("id") && value["id"].IsString())
        id_ = value["id"].GetString();
    if (value.HasMember("account") && value["account"].IsString())
        account_ = value["account"].GetString();
    if (value.HasMember("password") && value["password"].IsString())
        password_ = value["password"].GetString();
    if (value.HasMember("type") && value["type"].IsUint())
        type_ = (User::UserType)value["type"].GetUint();
}

User::User(const std::string &id, const std::string &account, const std::string &password, User::UserType type)
    : id_(id), account_(account), password_(password), type_(type) {}

const std::string &User::getId() const
{
    return id_;
}

const std::string &User::getAccount() const
{
    return account_;
}

const std::string &User::getPassword() const
{
    return password_;
}

User::UserType User::getType() const
{
    return type_;
}

void User::setId(const std::string &id)
{
    id_ = id;
}

void User::setAccount(const std::string &account)
{
    account_ = account;
}

void User::setPassword(const std::string &password)
{
    password_ = password;
}

bool User::validateAccountPassword(std::string account, std::string password) const
{
    if (account_ != account || password_ != password)
        return false;
    return true;
}

bool User::validateAccount(std::string account) const
{
    if (account_ != account)
        return false;
    return true;
}

void User::outputData(std::ofstream &out)
{
    out << type_ << std::endl
        << id_ << std::endl
        << account_ << std::endl
        << password_ << std::endl;
}

void User::inputData(std::ifstream &in)
{
    in >> id_ >> account_ >> password_;
}

rapidjson::Value User::toJSONObject(rapidjson::Document::AllocatorType &allocator)
{
    rapidjson::Value vObject(rapidjson::kObjectType);
    vObject.AddMember("id", rapidjson::StringRef(id_.c_str()), allocator);
    vObject.AddMember("account", rapidjson::StringRef(account_.c_str()), allocator);
    vObject.AddMember("password", rapidjson::StringRef(password_.c_str()), allocator);
    vObject.AddMember("type", type_, allocator);
    return vObject;
}

// User End ================================================================================================

// Administrator Begin =====================================================================================

Administrator::Administrator(const std::string &id,
                             const std::string &account,
                             const std::string &password)
    : User(id, account, password, User::ADMINISTRATOR) {}

// void Administrator::outputData(std::ofstream &out)
//{
//     out << type_ << std::endl
//         << id_ << std::endl
//         << account_ << std::endl
//         << password_ << std::endl;
// }
//
// void Administrator::inputData(std::ifstream &in)
//{
//     in >> id_ >> account_ >> password_;
// }

Administrator::Administrator() : User(User::ADMINISTRATOR) {}

Administrator::Administrator(const rapidjson::Value &value)
    : User(value) {}

// Administrator End =======================================================================================

// NormalUser Begin ========================================================================================

NormalUser::NormalUser(User::UserType type) : User(type) {}

NormalUser::NormalUser(const rapidjson::Value &value) : User(value)
{
    if (value.HasMember("nickName") && value["nickName"].IsString())
        nickName_ = value["nickName"].GetString();
    if (value.HasMember("phoneNumber") && value["phoneNumber"].IsString())
        phoneNumber_ = value["phoneNumber"].GetString();
    if (value.HasMember("address") && value["address"].IsString())
        address_ = value["address"].GetString();
    if (value.HasMember("registrationDate") && value["registrationDate"].IsObject())
        registrationDate_ = value["registrationDate"].GetObject();
    if (value.HasMember("balance") && value["balance"].IsDouble())
        balance_ = value["balance"].GetDouble();
    if (value.HasMember("accountState") && value["accountState"].IsUint())
        accountState_ = (NormalUser::AccountState)value["accountState"].GetUint();
}

NormalUser::NormalUser(const std::string &id, const std::string &account, const std::string &password,
                       User::UserType type, const std::string &nickName, const std::string &phoneNumber,
                       const std::string &address, const Date &registrationDate, double balance,
                       NormalUser::AccountState accountState)
    : User(id, account, password, type), nickName_(nickName),
      phoneNumber_(phoneNumber), address_(address),
      registrationDate_(registrationDate), balance_(balance),
      accountState_(accountState) {}

const std::string &NormalUser::getNickName() const
{
    return nickName_;
}

const std::string &NormalUser::getPhoneNumber() const
{
    return phoneNumber_;
}

const std::string &NormalUser::getAddress() const
{
    return address_;
}

const Date &NormalUser::getRegistrationDate() const
{
    return registrationDate_;
}

double NormalUser::getBalance() const
{
    return balance_;
}

NormalUser::AccountState NormalUser::getAccountState() const
{
    return accountState_;
}

void NormalUser::setNickName(const std::string &nickName)
{
    nickName_ = nickName;
}

void NormalUser::setPhoneNumber(const std::string &phoneNumber)
{
    phoneNumber_ = phoneNumber;
}

void NormalUser::setAddress(const std::string &address)
{
    NormalUser::address_ = address;
}

void NormalUser::setBalance(double balance)
{
    balance_ = balance;
}

void NormalUser::setAccountState(NormalUser::AccountState accountState)
{
    accountState_ = accountState;
}

void NormalUser::setAccountState(unsigned accountState)
{
    switch (accountState)
    {
    case NORMAL:
        accountState_ = NORMAL;
        break;
    case BANED:
        accountState_ = BANED;
        break;
    default:
        break;
    }
}

bool NormalUser::addBalance(const double amount)
{
    bool ret = (std::isinf(balance_ + amount));
    balance_ = ret ? balance_ : balance_ + amount;
    return !ret;
}

bool NormalUser::subBalance(const double amount)
{
    bool ret = (balance_ - amount) < 0;
    balance_ = ret ? balance_ : balance_ - amount;
    return !ret;
}

void NormalUser::outputData(std::ofstream &out)
{
    User::outputData(out);
    out << nickName_ << std::endl
        << phoneNumber_ << std::endl
        << address_ << std::endl
        << registrationDate_ << std::endl
        << balance_ << std::endl
        << accountState_ << std::endl;
}

void NormalUser::inputData(std::ifstream &in)
{
    User::inputData(in);
    unsigned accountState;
    in >> nickName_ >> phoneNumber_ >> address_ >> registrationDate_ >> balance_ >> accountState;
    setAccountState(accountState);
}

rapidjson::Value NormalUser::toJSONObject(rapidjson::Document::AllocatorType &allocator)
{
    rapidjson::Value vObject = User::toJSONObject(allocator);
    vObject.AddMember("nickName", rapidjson::StringRef(nickName_.c_str()), allocator);
    vObject.AddMember("phoneNumber", rapidjson::StringRef(phoneNumber_.c_str()), allocator);
    vObject.AddMember("address", rapidjson::StringRef(address_.c_str()), allocator);
    vObject.AddMember("registrationDate", registrationDate_.toJSONObject(allocator), allocator);
    vObject.AddMember("balance", balance_, allocator);
    vObject.AddMember("accountState", accountState_, allocator);
    return vObject;
}

// NormalUser End ==========================================================================================

// Buyer Start ==========================================================================================

Buyer::Buyer() : NormalUser(User::BUYER) {}

Buyer::Buyer(const rapidjson::Value &value) : NormalUser(value)
{
    if (value.HasMember("consumptionPoints") && value["consumptionPoints"].IsUint())
        consumptionPoints_ = value["consumptionPoints"].GetUint();
}

Buyer::Buyer(const std::string &id, const std::string &account,
             const std::string &password, const std::string &nickName,
             const std::string &phoneNumber, const std::string &address,
             const Date &registrationDate, double balance,
             NormalUser::AccountState accountState, unsigned int consumptionPoints)
    : NormalUser(id, account, password, User::BUYER, nickName, phoneNumber, address, registrationDate, balance, accountState),
      consumptionPoints_(consumptionPoints) {}

unsigned int Buyer::getConsumptionPoints() const
{
    return consumptionPoints_;
}

void Buyer::setConsumptionPoints(unsigned int consumptionPoints)
{
    consumptionPoints_ = consumptionPoints;
}

bool Buyer::addConsumptionPoints(const unsigned int amount)
{
    if (consumptionPoints_ > consumptionPoints_ + amount)
        return false;
    consumptionPoints_ += amount;
    return true;
}

bool Buyer::subConsumptionPoints(const unsigned int amount)
{
    if (consumptionPoints_ < consumptionPoints_ - amount)
        return false;
    consumptionPoints_ -= amount;
    return true;
}

void Buyer::outputData(std::ofstream &out)
{
    NormalUser::outputData(out);
    out << consumptionPoints_ << std::endl;
}

void Buyer::inputData(std::ifstream &in)
{
    NormalUser::inputData(in);
    in >> consumptionPoints_;
}

rapidjson::Value Buyer::toJSONObject(rapidjson::Document::AllocatorType &allocator)
{
    rapidjson::Value vObject = NormalUser::toJSONObject(allocator);
    vObject.AddMember("consumptionPoints", consumptionPoints_, allocator);
    return vObject;
}

// Buyer End ==========================================================================================
Seller::Seller() : NormalUser(User::SELLER) {}

Seller::Seller(const rapidjson::Value &value) : NormalUser(value)
{
    if (value.HasMember("tradingVolume") && value["tradingVolume"].IsUint())
        tradingVolume_ = value["tradingVolume"].GetUint();
}

Seller::Seller(const std::string &id, const std::string &account,
               const std::string &password, const std::string &nickName,
               const std::string &phoneNumber, const std::string &address,
               const Date &registrationDate, double balance,
               NormalUser::AccountState accountState, unsigned int tradingVolume)
    : NormalUser(id, account, password, User::SELLER, nickName, phoneNumber,
                 address, registrationDate, balance, accountState),
      tradingVolume_(tradingVolume) {}

unsigned int Seller::getTradingVolume() const
{
    return tradingVolume_;
}

void Seller::addtradingVolume()
{
    ++tradingVolume_;
}

void Seller::outputData(std::ofstream &out)
{
    NormalUser::outputData(out);
    out << tradingVolume_ << std::endl;
}

void Seller::inputData(std::ifstream &in)
{
    NormalUser::inputData(in);
    in >> tradingVolume_;
}

rapidjson::Value Seller::toJSONObject(rapidjson::Document::AllocatorType &allocator)
{
    rapidjson::Value vObject = NormalUser::toJSONObject(allocator);
    vObject.AddMember("tradingVolume", tradingVolume_, allocator);
    return vObject;
}
