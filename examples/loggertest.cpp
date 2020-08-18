#include <console_logger.h>
#include <file_logger.h>
#include <thread>
/*
void thread_test1(Logger logging){
    for(int i=0;i<50;++i){
        logging->Debug("Logging from thread: "+std::to_string(std::this_thread::get_id()));
    }
}
*/

void console_logger_test(){
    Logger logging = std::make_shared<logger::ConsoleLogger>();
    logging->Debug("THis is a debug message1");
    logging->Info("This is a Info message1");
    logging->Warn("This is a warning message1");
    logging->Error("This is a error message1");
    logging->LoggingLevel(logger::Loglevel::L_INFO);
    logging->Debug("THis is a debug message2");
    logging->Info("This is a Info message2");
    logging->Warn("This is a warning message2");
    logging->Error("This is a error message2");
    logging->LoggingLevel(logger::Loglevel::L_WARN);
    logging->Debug("THis is a debug message3");
    logging->Info("This is a Info message3");
    logging->Warn("This is a warning message3");
    logging->Error("This is a error message3");
    logging->LoggingLevel(logger::Loglevel::L_ERROR);
    logging->Debug("THis is a debug message4");
    logging->Info("This is a Info message4");
    logging->Warn("This is a warning message4");
    logging->Error("This is a error message4");
}

void file_logger_test(){
    Logger logging = std::make_shared<logger::FileLogger>();
    logging->Debug("THis is a debug message1");
    logging->Info("This is a Info message1");
    logging->Warn("This is a warning message1");
    logging->Error("This is a error message1");
    logging->LoggingLevel(logger::Loglevel::L_INFO);
    logging->Debug("THis is a debug message2");
    logging->Info("This is a Info message2");
    logging->Warn("This is a warning message2");
    logging->Error("This is a error message2");
    logging->LoggingLevel(logger::Loglevel::L_WARN);
    logging->Debug("THis is a debug message3");
    logging->Info("This is a Info message3");
    logging->Warn("This is a warning message3");
    logging->Error("This is a error message3");
    logging->LoggingLevel(logger::Loglevel::L_ERROR);
    logging->Debug("THis is a debug message4");
    logging->Info("This is a Info message4");
    logging->Warn("This is a warning message4");
    logging->Error("This is a error message4");
}

void test(){
    Logger logging = std::make_shared<logger::ConsoleLogger>();
    logging->Debug(STREAM("Hello"<<" World"<<" "<<1234324));
}

void func(Logger logging){
    for(int i=0;i<100;++i){
        logging->Debug(STREAM("Hi from thread "<<std::this_thread::get_id()));
    }
}

void thread_test(){
    Logger logging = std::make_shared<logger::ConsoleLogger>();
    std::thread t1(func, std::ref(logging));
    std::thread t2(func, std::ref(logging));
    std::thread t3(func, std::ref(logging));
    std::thread t4(func, std::ref(logging));
    std::thread t5(func, std::ref(logging));

    t5.join();
    t4.join();
    t3.join();
    t2.join();
    t1.join();
}

int main(){
    console_logger_test();
    file_logger_test();
    thread_test();
}