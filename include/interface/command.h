#pragma once
#include <cstdint>
#include <string>
#include <ostream>
#include "../common/status.h"
enum opType : uint8_t { GET = 1, PUT = 2, DELETE = 3 };

class Command
{
private:
    opType type;
    uint16_t key_size; // key的大小
    uint32_t value_size; // value的大小
    std::string key;
    std::string value; // value
    uint64_t timestamp = 0; // 时间戳-默认值为0，表示未设置
    bool tombstone_flag = false; // 墓碑标志, 默认值为false，表示未删除

public:
    // 重写输出流运算符，方便调试和日志记录
    friend std::ostream& operator<<(std::ostream& os, const Command& cmd); 

    Command() = default; // 默认构造函数

    // 设置命令的属性，并返回状态
    Status SetCmd(opType t, const std::string& k, const std::string& v, uint64_t ts = 0, bool tombstone = false);

    opType GetType() const { return type; }

    std::string GetKey() const { return key; }

    std::string GetValue() const { return value; }

    uint64_t GetTimestamp() const { return timestamp; }
    
    bool IsTombstone() const { return tombstone_flag; }
};