
#include <fstream>
#include "UserManager.h"

UserManager::UserManager(const std::string dataFilePath)
{
    dataFilePath_ = dataFilePath;
    userNumber_ = 0;
    savedUserId_ = 0;
}

UserManager::~UserManager()
{
    saveUsers();
    for (auto i = users_.begin(); i != users_.end(); ++i)
    {
        delete (*i);
        (*i) = nullptr;
    }
}

std::string UserManager::getNewId()
{
    std::string insertStr(std::to_string(++savedUserId_));
    std::string newStr = std::string("U00000000").substr(0, 10 - insertStr.length()) + insertStr;
    return newStr;
}

User *UserManager::loginAccount(std::string account, std::string password)
{
    User *user = nullptr;
    for (auto i = users_.begin(); i != users_.end(); i++)
        if ((*i)->validateAccountPassword(account, password))
            user = (*i);

    return user;
}

bool UserManager::registerUser(User *user)
{
    for (auto i = users_.begin(); i != users_.end(); i++)
        if ((*i)->validateAccount(user->getAccount()))
            return false;
    users_.push_back(user);
    user->setId(getNewId());
    ++userNumber_;
    return true;
}

bool UserManager::CancelUser(User *user)
{
    for (auto i = users_.begin(); i != users_.end(); i++)
        if ((*i) == user)
        {
            delete user;
            users_.erase(i);
            --userNumber_;
            return true;
        }
    return false;
}

bool UserManager::pullUsers()
{
    std::ifstream in(dataFilePath_, std::ios::in);
    if (in.is_open())
    {
        std::string str;
        unsigned int userNumber = 0;
        in >> str;
        if (str == std::string("userNumber="))
            in >> userNumber;
        else
            return false;
        in >> str;
        if (str == std::string("savedUserId="))
            in >> savedUserId_;
        else
            return false;

        for (int i = 0; i < userNumber; ++i)
        {
            unsigned int userType = -1;
            in >> userType;

            User *user = nullptr;
            if (User::ADMINISTRATOR == userType)
            {
                user = new Administrator();
            }
            else if (User::BUYER == userType)
            {
                user = new Buyer();
            }
            else if (User::SELLER == userType)
            {
                user = new Seller();
            }
            else
            {
                break;
            }
            ++userNumber_;
            user->inputData(in);
            users_.push_back(user);
        }
    }
    return false;
}

bool UserManager::saveUsers()
{
    std::ofstream out(dataFilePath_, std::ios::out);
    out << "userNumber=" << std::endl
        << userNumber_ << std::endl
        << "savedUserId=" << std::endl
        << savedUserId_ << std::endl;
    for (auto i = users_.begin(); i != users_.end(); i++)
    {
        (*i)->outputData(out);
    }
    return true;
}
