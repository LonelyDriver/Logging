#pragma once
#include <memory>
#include <string>
#include <sstream>

namespace logger
{
    enum class Loglevel{ALL=0, DEBUG=10, INFO=30, WARN=50, ERROR=70};
    /**
     * @brief Base interface for logger
     * 
     */
    class LoggerInterface{
    public:
        virtual ~LoggerInterface() = default;
        virtual void Info(const std::string& message) = 0;
        virtual void Debug(const std::string& message) = 0;
        virtual void Warn(const std::string& message) = 0;
        virtual void Error(const std::string& message) = 0;
        
        virtual void Info(const std::stringstream& message) = 0;
        virtual void Debug(const std::stringstream& message) = 0;
        virtual void Warn(const std::stringstream& message) = 0;
        virtual void Error(const std::stringstream& message) = 0;

        virtual void LoggingLevel(Loglevel level) = 0;
        virtual std::string LoggingLevel() = 0;
    };
} // namespace logger

using Logger = std::shared_ptr<logger::LoggerInterface>;
