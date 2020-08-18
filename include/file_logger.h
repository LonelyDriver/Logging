#pragma once

#include <base_logger.h>
#include <iostream>
#include <fstream>

namespace logger {
    class FileLogger : public BaseLogger{
    public:
        FileLogger(const std::string& filename="Logger.log") : BaseLogger(), m_filename(filename){}
    private:
        std::string m_filename;

        void WriteToLog(const std::string& output) override{
            try{
            std::ofstream ostream;
            ostream.open(m_filename, std::ios::out | std::ios::app);
            ostream << output << std::endl;
            ostream.close();
        } catch(std::exception& e){
            std::cout << e.what() << std::endl;
        }

        }

    };
}