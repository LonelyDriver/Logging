#pragma once
#include <logger_interface.h>
#include <mutex>

#define STREAM(msg) ((std::stringstream&) (std::stringstream("") << msg))

namespace logger{
    class BaseLogger : public LoggerInterface{
    public:
        BaseLogger();
        virtual ~BaseLogger() = default;
        void Info(const std::string& message) override;
        void Debug(const std::string& message) override;
        void Warn(const std::string& message) override;
        void Error(const std::string& message) override;

        void Info(const std::stringstream& message) override;
        void Debug(const std::stringstream& message) override;
        void Warn(const std::stringstream& message) override;
        void Error(const std::stringstream& message) override;

        void LoggingLevel(Loglevel level) override;
        std::string LoggingLevel() override;
    protected:
        std::string FormatLogging(const std::string& message, Loglevel level);
        std::string ConvertLevel(Loglevel level);
        virtual void WriteToLog(const std::string& output) = 0;

        Loglevel m_loglevel;
        std::mutex m_mtx;
        std::stringstream m_stream;
    };
}