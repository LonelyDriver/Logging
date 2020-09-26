#pragma once
#include <memory>
#include <string>
#include <sstream>

namespace logger
{
    enum class Loglevel{L_ALL=0, L_DEBUG=10, L_INFO=30, L_WARN=50, L_ERROR=70};
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
        virtual void SetID(const std::string& id) = 0;
    };
} // namespace logger

using Logger = std::shared_ptr<logger::LoggerInterface>;
