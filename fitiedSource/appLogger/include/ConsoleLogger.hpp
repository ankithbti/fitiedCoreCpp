/* 
 * File:   ConsoleLogger.hpp
 * Author: ankithbti
 *
 * Created on 8 August, 2015, 4:11 PM
 */

#ifndef CONSOLELOGGER_HPP
#define	CONSOLELOGGER_HPP

#include <Log.hpp>
#include <iostream>
#include <queue>
#include <boost/thread.hpp>

namespace fitiedCoreCpp
{
namespace appLogger
{

class ConsoleLogger : public Log<std::string>
{
public:
    typedef boost::shared_ptr<std::string> MsgSmartPtr;

    ConsoleLogger(int numConsumerThreads = 1) : Log<std::string>(numConsumerThreads)
    {

    }

    virtual ~ConsoleLogger(){
        
    }

protected:
    virtual void printLogObject(LogObject::SmartPtr logObj);
    virtual void printLogObject(StringLogObject::SmartPtr logObj);

};
}
}
#endif	/* CONSOLELOGGER_HPP */

