#include <base_logger.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <thread>
#include <cstdlib>

logger::BaseLogger::BaseLogger() :
m_loglevel(logger::Loglevel::ALL),
m_mtx(){
    const char* env_p = std::getenv("LOG_LEVEL");
    if(env_p != nullptr){
        std::string env(env_p);
        if(env == "All"){
            LoggingLevel(Loglevel::ALL);
        }else if(env == "Debug"){
            LoggingLevel(Loglevel::DEBUG);
        }else if(env == "Info"){
            LoggingLevel(Loglevel::INFO);
        }else if(env == "Warn"){
            LoggingLevel(Loglevel::WARN);
        }else if(env == "Error"){
            LoggingLevel(Loglevel::ERROR);
        }
    }

}

void logger::BaseLogger::Info(const std::stringstream& message){
    std::unique_lock<std::mutex> lock(m_mtx);
    if(logger::Loglevel::INFO >= m_loglevel){
        WriteToLog(FormatLogging(message.str(), logger::Loglevel::INFO));
    }
}

void logger::BaseLogger::Debug(const std::stringstream& message){
    std::unique_lock<std::mutex> lock(m_mtx);
    if(logger::Loglevel::DEBUG >= m_loglevel){
        WriteToLog(FormatLogging(message.str(), logger::Loglevel::DEBUG));
    }
}

void logger::BaseLogger::Error(const std::stringstream& message){
    std::unique_lock<std::mutex> lock(m_mtx);
    if(logger::Loglevel::ERROR >= m_loglevel){
        WriteToLog(FormatLogging(message.str(), logger::Loglevel::ERROR));
    }
}

void logger::BaseLogger::Warn(const std::stringstream& message){
    std::unique_lock<std::mutex> lock(m_mtx);
    if(logger::Loglevel::WARN >= m_loglevel){
        WriteToLog(FormatLogging(message.str(), logger::Loglevel::WARN));
    }
}

void logger::BaseLogger::Info(const std::string& message){
    std::unique_lock<std::mutex> lock(m_mtx);
    if(logger::Loglevel::INFO >= m_loglevel){
        WriteToLog(FormatLogging(message, logger::Loglevel::INFO));
    }
}

void logger::BaseLogger::Debug(const std::string& message){
    std::unique_lock<std::mutex> lock(m_mtx);
    if(logger::Loglevel::DEBUG >= m_loglevel){
        WriteToLog(FormatLogging(message, logger::Loglevel::DEBUG));
    }
}

void logger::BaseLogger::Error(const std::string& message){
    std::unique_lock<std::mutex> lock(m_mtx);
    if(logger::Loglevel::ERROR >= m_loglevel){
        WriteToLog(FormatLogging(message, logger::Loglevel::ERROR));
    }
}

void logger::BaseLogger::Warn(const std::string& message){
    std::unique_lock<std::mutex> lock(m_mtx);
    if(logger::Loglevel::WARN >= m_loglevel){
        WriteToLog(FormatLogging(message, logger::Loglevel::WARN));
    }
}

std::string logger::BaseLogger::FormatLogging(const std::string& message, Loglevel level){
    std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(p.time_since_epoch());
    size_t ms_frac = ms.count() % 1000;
    std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(ms);
    std::time_t t = s.count();
    
    std::stringstream ss{};
    ss << "\033[90m"<< std::put_time(std::localtime(&t), "%F %T") << "." << ms_frac << " " << std::this_thread::get_id() << ConvertLevel(level)<< ":" << message << "\033[0m";
    return ss.str();
}
/*
void logger::BaseLogger::WriteToLog(const std::string& output){
    std::cout << output << std::endl;
}
*/

std::string logger::BaseLogger::ConvertLevel(Loglevel level){
    switch(level){
        case Loglevel::DEBUG:
            return " \033[35m[Debug]";
        case Loglevel::INFO:
            return " \033[36m[Info]";
        case Loglevel::WARN:
            return " \033[33m[Warn]";
        case Loglevel::ERROR:
            return " \033[31m[Error]";
        default:
            return " [All]";
    }
}

void logger::BaseLogger::LoggingLevel(Loglevel level){
    WriteToLog("\033[90mChanged Loglevel to "+ConvertLevel(level)+"\033[0m");
    
    m_loglevel = level;
}

std::string logger::BaseLogger::LoggingLevel(){
    std::string ret = ConvertLevel(m_loglevel);
    return ret.substr(1,ret.size()-1);
}