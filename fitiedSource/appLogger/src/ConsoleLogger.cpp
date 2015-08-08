#include <ConsoleLogger.hpp>
#include <iostream>

namespace fitiedCoreCpp
{

namespace appLogger
{

void ConsoleLogger::printLogObject(LogObject::SmartPtr logObj)
{
    //std::cout << logObj->_timeStamp << " " << logObj->_levelStr << " - " << *logObj->_obj << std::endl;
}

void ConsoleLogger::printLogObject(StringLogObject::SmartPtr logObj)
{
    std::cout << logObj->_timeStamp << " " << logObj->_levelStr << " - " << logObj->_obj << std::endl;
}

}
}
