#include <iostream>
#include <ConsoleLogger.hpp>

using namespace fitiedCoreCpp::appLogger;
int main()
{
std::cout << " Test " << std::endl;
ConsoleLogger::SmartPtr _logger(new ConsoleLogger(1));
boost::shared_ptr<std::string> msg(new std::string("Test Log Experience....."));
_logger->log(INFO, msg);
_logger->log(INFO, "Testing a String Message.....");
_logger->log(INFO, "Testing a String Message2.....");
sleep(1);
return 0;
}
