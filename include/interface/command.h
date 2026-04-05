#pragma once
#include <cstdint>
#include <string>
#include <ostream>
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
    friend std::ostream& operator<<(std::ostream& os, const Command& cmd)
    {
        os << "Command Type: " << static_cast<int>(cmd.type) << std::endl;
        os << "Key Size: " << cmd.key_size << std::endl;
        os << "Value Size: " << cmd.value_size << std::endl;
        os << "Key: " << cmd.key << std::endl;
        os << "Value: " << cmd.value << std::endl;
        os << "Timestamp: " << cmd.timestamp << std::endl;
        os << "Tombstone Flag: " << (cmd.tombstone_flag ? "true" : "false") << std::endl;
        return os;
    }
    Command() = default; // 默认构造函数
    void SetCmd(opType t, const std::string& k, const std::string& v, uint64_t ts = 0, bool tombstone = false)
    {
        type = t;
        key_size = k.size();
        value_size = v.size();
        key = k;
        value = v;
        timestamp = ts;
        tombstone_flag = tombstone;
    }
    opType GetType() const { return type; }
    std::string GetKey() const { return key; }
    std::string GetValue() const { return value; }
    uint64_t GetTimestamp() const { return timestamp; }
    bool IsTombstone() const { return tombstone_flag; }
};