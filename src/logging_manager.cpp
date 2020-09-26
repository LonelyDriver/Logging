#include "logging_manager.h"

void logger::LoggingManager::RegisterLogger(const std::string& id, Logger logging){
    std::unique_lock<std::mutex> lock(m_mtx);
    if(m_loggers.find(id) == m_loggers.end()){
        logging->SetID(id);
        m_loggers[id] = logging;
        m_logging->Info(STREAM("registered "<<id));
        return;
    }
    m_logging->Info(STREAM(id<<" already registred"));
}

Logger logger::LoggingManager::GetLogger(const std::string& id){
    std::unordered_map<std::string, Logger>::iterator it = m_loggers.find(id);
    if(it != m_loggers.end()){
        return it->second;
    }
    RegisterLogger(id, std::make_shared<logger::ConsoleLogger>(id));
    return GetLogger(id);
}