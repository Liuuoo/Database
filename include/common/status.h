#pragma once
#include <string>

class Status
{
public:
    enum Code {
        kOk = 0,
        kNotFound = 1,      // 未找到 (比如读取一个不存在的文件)
        kCorruption = 2,    // 数据损坏 (比如掉电导致日志残缺)
        kIOError = 3,       // 操作系统 I/O 错误
        kInvalidArgument = 4, // 无效参数 (比如传入了一个不合法的文件名)
        koutBound = 5,      // 越界 (比如读取一个数组时索引超出范围)
    };
    Status() : code_(kOk), msg_("") {}

    static Status Ok() { return Status(); }
    static Status NotFound(const std::string& msg) { return Status(kNotFound, msg); }
    static Status Corruption(const std::string& msg) { return Status(kCorruption, msg); }
    static Status IOError(const std::string& msg) { return Status(kIOError, msg); }
    static Status InvalidArgument(const std::string& msg) { return Status(kInvalidArgument, msg); }
    static Status OutOfBound(const std::string& msg) { return Status(koutBound, msg); }

    bool ok() const { return code_ == kOk; }
    bool IsNotFound() const { return code_ == kNotFound; }
    bool IsCorruption() const { return code_ == kCorruption; }
    bool IsIOError() const { return code_ == kIOError; }
    bool IsInvalidArgument() const { return code_ == kInvalidArgument; }
    bool IsOutOfBound() const { return code_ == koutBound; }
    
    std::string ToString() const {
        if (code_ == kOk) return "OK";
        std::string result;
        switch (code_) {
            case kNotFound:    result = "NotFound: "; break;
            case kCorruption:  result = "Corruption: "; break;
            case kIOError:     result = "IO error: "; break;
            case kInvalidArgument: result = "Invalid argument: "; break;
            case koutBound:    result = "Out of bound: "; break;
            default:           result = "Unknown code: "; break;
        }
        result.append(msg_);
        return result;
    }

private:
    /* data */
    Status(Code code, const std::string& msg) : code_(code), msg_(msg) {};
    Code code_;
    std::string msg_;
};