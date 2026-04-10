#include "../../include/log/log_writer.h"
[[nodiscard]] Status write_to_disk(const Command& cmd) 
{
    FILE* file = fopen("../wal.log", "a"); // 以追加模式打开日志文件
    if (!file) {
        file = fopen("../wal.log", "w");
        std::cout<<"Log file created successfully."<<std::endl;

        if (!file) {
            std::cerr << "Failed to create log file." << std::endl;
            return Status::IOError("Failed to create log file");
        }

    }
    std::string log_entry = "Command Type: " + std::to_string(static_cast<int>(cmd.GetType())) + "\n" +
                            "Key Size: " + std::to_string(cmd.GetKey().size()) + "\n" +
                            "Value Size: " + std::to_string(cmd.GetValue().size()) + "\n" +
                            "Key: " + cmd.GetKey() + "\n" +
                            "Value: " + cmd.GetValue() + "\n" +
                            "Timestamp: " + std::to_string(cmd.GetTimestamp()) + "\n" +
                            "Tombstone Flag: " + (cmd.IsTombstone() ? "true" : "false") + "\n\n";

    fclose(file);
    return Status::Ok();
}