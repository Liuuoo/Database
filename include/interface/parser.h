#pragma once // 防止重复包含        
#include<string>
#include<string_view>
#include<cstdint>
#include<stdexcept>
#include"command.h"
#include"common/my_time.h"

class parser
{
private: 
    std::string key;
    std::string value;
    std::string op;
    Command cmd;
public:
    parser(std::string_view s)
    {
        // s示例 PUT {key,value}
        // key为int时，处理为：123（示例）
        // value为string时，处理为："hello"（示例）
        bool is_tombstone = false; // 默认值为false，表示未删除
        opType cmd_type; // 定义一个opType类型的变量来存储命令类型
        try
        {
            size_t index1 = s.find(" ");
            op = s.substr(0, index1);
            if(op == "GET")
            {
                cmd_type = GET; 
                if(s.find("{")==std::string::npos || s.find("}")==std::string::npos)
                {
                    throw std::runtime_error("Invalid command"); // 抛出异常，表示无效的命令
                }
                size_t index2 = s.find("{");
                size_t index3 = s.find("}");
                key = s.substr(index2 + 1, index3 - index2 - 1);
                // 这边VALUE暂时留空，后续skiplist完成后加入
            }
            else if (op == "DELETE")
            {
                cmd_type = DELETE; 
                is_tombstone = true; // 设置墓碑标志为true，表示已删除
                if(s.find("{")==std::string::npos || s.find("}")==std::string::npos)
                {
                    throw std::runtime_error("Invalid command"); // 抛出异常，表示无效的命令
                }
                size_t index2 = s.find("{");
                size_t index3 = s.find("}");
                key = s.substr(index2 + 1, index3 - index2 - 1);
                // 这边VALUE暂时留空，后续skiplist完成后加入
            }
            else if(op == "PUT")
            {
                cmd_type = PUT;  
                if(s.find("{")==std::string::npos || s.find("}")==std::string::npos  || s.find(",")==std::string::npos)
                {
                    throw std::runtime_error("Invalid command"); // 抛出异常，表示无效的命令
                }
                size_t index2 = s.find("{");
                size_t index3 = s.find(",");
                size_t index4 = s.find("}");
                key = s.substr(index2 + 1, index3 - index2 - 1);
                value = s.substr(index3 + 1, index4 - index3 - 1);
            }
            else
            {
                throw std::runtime_error("Invalid command"); // 抛出异常，表示无效的命令
            }
        }
        catch(const std::exception& e)
        {
            throw std::runtime_error("Invalid command"); // 抛出异常，表示无效的命令
        }
        cmd.SetCmd(cmd_type, key, value, getTimestampMs(), is_tombstone); // 创建一个command对象，并初始化type、key和value
    };
    Command getCmd() const
    {
        return cmd; // 返回当前对象的副本
    }
};

