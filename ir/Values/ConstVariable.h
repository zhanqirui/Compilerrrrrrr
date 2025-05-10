#pragma once

#include "User.h"
#include "Type.h"

///
/// @brief 表示具有 const 属性的变量（有名字、可寻址）
///
class ConstVariable : public User {
public:
    ConstVariable(Type * type, const std::string & name) : User(type), name(name)
    {
        this->setConst(true);
    }

    std::string getIRName() const override
    {
        return name;
    }

    bool isConst()
    {
        return is_constant;
    }

    int32_t getLoadRegId() override
    {
        return loadRegNo;
    }

    void setLoadRegId(int32_t regId) override
    {
        this->loadRegNo = regId;
    }

private:
    std::string name;
    int32_t loadRegNo = -1;
};
