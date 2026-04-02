enum opType : uint8_t { GET = 1, PUT = 2, DELETE = 3 };
struct command
{
    opType type;
    uint8_t key_size;
    uint8_t value_size;
    std::string_view key;
    std::string_view value;
    uint32_t timestamp;
    bool tombstone_flag;
};