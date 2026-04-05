#include "../include/common/my_time.h"
#include <chrono>
// 这边的时间戳比较脆弱，当机器时间晚与该时间时，会变成大的数，并且时间戳会变成负数，后续需要修改。
// 辅助函数：获取 2026-04-05 00:00:00 的时间点
std::chrono::system_clock::time_point getCustomEpoch() {
    // 使用 static 静态局部变量 + Lambda 表达式
    // 确保 std::mktime 的计算只在第一次调用时执行一次，提高后续调用的性能
    static std::chrono::system_clock::time_point custom_epoch = []() {
        std::tm time_info = {};
        time_info.tm_year = 2026 - 1900; // std::tm 中年份是从 1900 开始算的
        time_info.tm_mon  = 4 - 1;       // 月份是从 0 开始的 (0 代表 1月，3 代表 4月)
        time_info.tm_mday = 5;           // 日 (1-31)
        time_info.tm_hour = 0;           // 时
        time_info.tm_min  = 0;           // 分
        time_info.tm_sec  = 0;           // 秒
        time_info.tm_isdst = -1;         // -1 表示由系统自动判断是否为夏令时
        
        // std::mktime 会将 tm 结构转换为本地时间的 time_t
        time_t time_t_epoch = std::mktime(&time_info);
        
        // 转换为 chrono 的 time_point 并返回
        return std::chrono::system_clock::from_time_t(time_t_epoch);
    }();
    
    return custom_epoch;
}

// 获取基于自定义基准的时间戳（秒级）
std::uint64_t getTimestampSec() {
    auto now = std::chrono::system_clock::now();
    // 核心改变：用当前时间减去自定义基准时间
    auto duration = now - getCustomEpoch(); 
    return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
}

// 获取基于自定义基准的时间戳（毫秒级）
std::uint64_t getTimestampMs() {
    auto now = std::chrono::system_clock::now();
    // 核心改变：用当前时间减去自定义基准时间
    auto duration = now - getCustomEpoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}