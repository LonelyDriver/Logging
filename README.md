## Simple C++ Logger
Threadsafe console and file logger class.
To use include ```<console_logger.h>``` or ```<file_logger.h>```.

## Build
Clone repository.

    mkdir build
    cd build

If you want to build examples.

    cmake .. -Dbuild_examples=ON

    


## Using
Create logger.

	Logger logging = std::make_shared<logger::ConsoleLogger>();

There are four logging levels.

    logging->Debug("This is a Debug message");
    logging->Info("This is a Info message");
    logging->Warn("This is a Warning message");
    logging->Error("This is a Error message");
    
You can also use ```std::stringstream``` for logging.

    logging->Debug(STREAM("Hello world " << 123));

Set logging level.

    logging->LoggingLevel(logger::Loglevel::INFO);

