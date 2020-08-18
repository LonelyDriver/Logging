#pragma once

#include <base_logger.h>
#include <iostream>

namespace logger {
    class ConsoleLogger : public BaseLogger{
    private:
        void WriteToLog(const std::string& output) override{
            std::cout << output << std::endl;
        }

    };
}