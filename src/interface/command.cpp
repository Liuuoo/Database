#include "../../include/interface/command.h"
#include "../../include/common/status.h"

[[nodiscard]] Status Command::SetCmd(opType t, const std::string& k, const std::string& v, uint64_t ts, bool tombstone)
{
    type = t;
    key_size = k.size();
    value_size = v.size();
    key = k;
    value = v;
    timestamp = ts;
    tombstone_flag = tombstone;
    return Status::Ok();
}

std::ostream& operator<<(std::ostream& os, const Command& cmd)
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
