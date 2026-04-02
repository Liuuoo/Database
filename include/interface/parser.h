#pragma once // 防止重复包含        
#include<string>
#include<cstdint>
#include<stdexcept>
#include"command.h"

class parser
{
private: 
    command cmd;
public:
    parser(std::string_view s)
    {
        // s示例 PUT {key,value}
        // key为int时，处理为：123（示例）
        // value为string时，处理为："hello"（示例）
        size_t index1 = s.find(" ");
        std::string_view op = s.substr(0, index1);
        size_t index2 = s.find("{");
        size_t index3 = s.find(",");
        size_t index4 = s.find("}");
        std::string_view key = s.substr(index2 + 1, index3 - index2 - 1);
        std::string_view value = s.substr(index3 + 1, index4 - index3 - 1);
        if(op == "GET")
        {
            cmd.type = GET; // 
        }
        else if(op == "PUT")
        {
            cmd.type = PUT;
        }
        else if(op == "DELETE")
        {
            cmd.type = DELETE;
        }
        else
        {
            throw std::runtime_error("Invalid command");
        }
        cmd.key = key;
        cmd.value = value;
    };
    command get_command() const
    {
        return cmd;
    }
    ~parser();
};

