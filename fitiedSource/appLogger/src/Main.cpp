#include <iostream>
#include <ConsoleLogger.hpp>
#include <SimpleFileLogger.hpp>

using namespace fitiedCoreCpp::appLogger;
int main()
{
std::cout << " Test " << std::endl;
ConsoleLogger::SmartPtr _logger(new ConsoleLogger(1));
boost::shared_ptr<std::string> msg(new std::string("Test Log Experience....."));
_logger->log(INFO, msg);
_logger->log(INFO, "Testing a String Message.....");
_logger->log(INFO, "Testing a String Message2.....");

SimpleFileLogger::SmartPtr _fileLogger(new SimpleFileLogger("TEST"));
_fileLogger->log(INFO, "My First File Log.");
_fileLogger->log(ERROR, "My 2nd File Log.");
_fileLogger->log(WARNING, "Testing a String Message2.....");
_fileLogger->log(DEBUG, "Testing a String Message2.....");


sleep(1);
return 0;
}
