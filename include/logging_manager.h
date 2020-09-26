#pragma once
#include <unordered_map>
#include "console_logger.h"

namespace logger {
    class LoggingManager{
    public:
        LoggingManager() = delete;
        LoggingManager(const LoggingManager&) = delete;
        static void RegisterLogger(const std::string& id, Logger logging);
        static Logger GetLogger(const std::string& id);

    private:
        static inline std::unordered_map<std::string,Logger> m_loggers;
        static inline Logger m_logging = std::make_shared<logger::ConsoleLogger>("LOGGINGMANAGER");
        static inline std::mutex m_mtx;
    };
}

using LogManager = logger::LoggingManager;