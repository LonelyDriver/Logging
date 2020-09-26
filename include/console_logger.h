#pragma once

#include <base_logger.h>
#include <iostream>

namespace logger {
    class ConsoleLogger : public BaseLogger{
    public:
        ConsoleLogger() : BaseLogger(){}
        ConsoleLogger(const std::string& id) : BaseLogger(id){}
    private:
        void WriteToLog(const std::string& output) override{
            std::cout << output << std::endl;
        }

    };
}