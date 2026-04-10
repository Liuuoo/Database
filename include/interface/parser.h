#pragma once // 防止重复包含        
#include<string>
#include<string_view>
#include<cstdint>
#include<stdexcept>
#include"command.h"
#include"../common/my_time.h"

class parser
{
private: 
    std::string key;
    std::string value;
    std::string op;
    Command cmd;
public:
    parser(std::string_view s);
    Command getCmd() const
    {
        return cmd; // 返回当前对象的副本
    }
};