/* 
 * File:   SimpleFileLogger.hpp
 * Author: ankithbti
 *
 * Created on 8 August, 2015, 10:07 PM
 */

#ifndef SIMPLEFILELOGGER_HPP
#define	SIMPLEFILELOGGER_HPP

#include <Log.hpp>

namespace fitiedCoreCpp
{
namespace appLogger
{

class SimpleFileLogger : public Log<std::string>
{
public:
    typedef boost::shared_ptr<SimpleFileLogger> SmartPtr;

private:
    std::string _fileNamePrefix;
    std::string _logPath;
    std::string _absFileName;
    std::ofstream _outputFileStream;

public:

    SimpleFileLogger(const std::string& fileNamePrefix, const std::string& logPath = std::string());

    virtual ~SimpleFileLogger();

protected:
    virtual void printLogObject(LogObject::SmartPtr);
    virtual void printLogObject(StringLogObject::SmartPtr);


};
}
}

#endif	/* SIMPLEFILELOGGER_HPP */

