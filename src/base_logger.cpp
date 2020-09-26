#include <base_logger.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <thread>
#include <cstdlib>

logger::BaseLogger::BaseLogger(const std::string& id) : BaseLogger(){
    m_id = id;
}

logger::BaseLogger::BaseLogger() :
m_loglevel(logger::Loglevel::L_ALL),
m_mtx(),
m_id(""){
    const char* env_p = std::getenv("LOG_LEVEL");
    if(env_p != nullptr){
        std::string env(env_p);
        if(env == "All"){
            LoggingLevel(Loglevel::L_ALL);
        }else if(env == "Debug"){
            LoggingLevel(Loglevel::L_DEBUG);
        }else if(env == "Info"){
            LoggingLevel(Loglevel::L_INFO);
        }else if(env == "Warn"){
            LoggingLevel(Loglevel::L_WARN);
        }else if(env == "Error"){
            LoggingLevel(Loglevel::L_ERROR);
        }
    }

}

void logger::BaseLogger::Info(const std::stringstream& message){
    std::unique_lock<std::mutex> lock(m_mtx);
    if(logger::Loglevel::L_INFO >= m_loglevel){
        WriteToLog(FormatLogging(message.str(), logger::Loglevel::L_INFO));
    }
}

void logger::BaseLogger::Debug(const std::stringstream& message){
    std::unique_lock<std::mutex> lock(m_mtx);
    if(logger::Loglevel::L_DEBUG >= m_loglevel){
        WriteToLog(FormatLogging(message.str(), logger::Loglevel::L_DEBUG));
    }
}

void logger::BaseLogger::Error(const std::stringstream& message){
    std::unique_lock<std::mutex> lock(m_mtx);
    if(logger::Loglevel::L_ERROR >= m_loglevel){
        WriteToLog(FormatLogging(message.str(), logger::Loglevel::L_ERROR));
    }
}

void logger::BaseLogger::Warn(const std::stringstream& message){
    std::unique_lock<std::mutex> lock(m_mtx);
    if(logger::Loglevel::L_WARN >= m_loglevel){
        WriteToLog(FormatLogging(message.str(), logger::Loglevel::L_WARN));
    }
}

void logger::BaseLogger::Info(const std::string& message){
    std::unique_lock<std::mutex> lock(m_mtx);
    if(logger::Loglevel::L_INFO >= m_loglevel){
        WriteToLog(FormatLogging(message, logger::Loglevel::L_INFO));
    }
}

void logger::BaseLogger::Debug(const std::string& message){
    std::unique_lock<std::mutex> lock(m_mtx);
    if(logger::Loglevel::L_DEBUG >= m_loglevel){
        WriteToLog(FormatLogging(message, logger::Loglevel::L_DEBUG));
    }
}

void logger::BaseLogger::Error(const std::string& message){
    std::unique_lock<std::mutex> lock(m_mtx);
    if(logger::Loglevel::L_ERROR >= m_loglevel){
        WriteToLog(FormatLogging(message, logger::Loglevel::L_ERROR));
    }
}

void logger::BaseLogger::Warn(const std::string& message){
    std::unique_lock<std::mutex> lock(m_mtx);
    if(logger::Loglevel::L_WARN >= m_loglevel){
        WriteToLog(FormatLogging(message, logger::Loglevel::L_WARN));
    }
}

std::string logger::BaseLogger::FormatLogging(const std::string& message, Loglevel level){
    std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(p.time_since_epoch());
    size_t ms_frac = ms.count() % 1000;
    std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(ms);
    std::time_t t = s.count();
    
    std::stringstream ss{};
    ss << std::put_time(std::localtime(&t), "%F %T") << "." << ms_frac << " " << std::this_thread::get_id() << " " << m_id << ConvertLevel(level)<< ": " << message;
    return ss.str();
}

std::string logger::BaseLogger::ConvertLevel(Loglevel level){
    switch(level){
        case Loglevel::L_DEBUG:
            return " [Debug]";
        case Loglevel::L_INFO:
            return " [Info]";
        case Loglevel::L_WARN:
            return " [Warn]";
        case Loglevel::L_ERROR:
            return " [Error]";
        default:
            return " [All]";
    }
}

void logger::BaseLogger::LoggingLevel(Loglevel level){
    std::unique_lock<std::mutex> lock(m_mtx);
    WriteToLog("Changed Loglevel to "+ConvertLevel(level));
    
    m_loglevel = level;
}

std::string logger::BaseLogger::LoggingLevel(){
    std::string ret = ConvertLevel(m_loglevel);
    return ret.substr(1,ret.size()-1);
}

void logger::BaseLogger::SetID(const std::string& id){
    std::unique_lock<std::mutex> lock(m_mtx);
    WriteToLog("Changed ID to "+id);

    m_id = id;
}