/* 
 * File:   Log.hpp
 * Author: ankithbti
 *
 * Created on 8 August, 2015, 4:02 PM
 */

#ifndef LOG_HPP
#define	LOG_HPP

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <queue>
#include <boost/thread.hpp>

namespace fitiedCoreCpp
{
namespace appLogger
{

enum LogLevel
{
    ERROR = 0,
    WARNING,
    INFO,
    DEBUG
};

template <typename T>
class Log : private boost::noncopyable
{
public:
    typedef boost::shared_ptr<Log> SmartPtr;
    typedef boost::shared_ptr<const Log> SmartConstPtr;
    typedef typename boost::shared_ptr<T> TSmartPtr;

protected:

    struct LogObject
    {
        typedef boost::shared_ptr<LogObject> SmartPtr;

        TSmartPtr _obj;
        boost::posix_time::ptime _timeStamp;
        std::string _levelStr;

        LogObject(TSmartPtr obj, LogLevel l) : _obj(obj)
        {
            _timeStamp = boost::posix_time::microsec_clock::local_time();
            getLevelString(l, _levelStr);
        }

        void getLevelString(LogLevel l, std::string& str)
        {
            switch (l)
            {
            case ERROR:
                str = "ERROR";
                break;
            case WARNING:
                str = "WARN";
                break;
            case INFO:
                str = "INFO";
                break;
            case DEBUG:
                str = "DEBUG";
                break;
            default:
                str = "DEFAULT";
                break;
            }
        }
    };

    struct StringLogObject
    {
        typedef boost::shared_ptr<StringLogObject> SmartPtr;

        std::string _obj;
        boost::posix_time::ptime _timeStamp;
        std::string _levelStr;

        StringLogObject(const std::string& obj, LogLevel l) : _obj(obj)
        {
            _timeStamp = boost::posix_time::microsec_clock::local_time();
            getLevelString(l, _levelStr);
        }

        void getLevelString(LogLevel l, std::string& str)
        {
            switch (l)
            {
            case ERROR:
                str = "ERROR";
                break;
            case WARNING:
                str = "WARN";
                break;
            case INFO:
                str = "INFO";
                break;
            case DEBUG:
                str = "DEBUG";
                break;
            default:
                str = "DEFAULT";
                break;
            }
        }
    };


    boost::mutex _qMutex;
    boost::condition_variable _qCondVar;
    std::queue<typename LogObject::SmartPtr> _queue;
    boost::thread_group _threadPool;
    volatile bool _isStopping;

    boost::mutex _stringQMutex;
    boost::condition_variable _stringQCondVar;
    std::queue<typename StringLogObject::SmartPtr> _stringQ;
    boost::thread _stringLoggerThread;

public:

    Log(int numOfConsumerThreads = 1) :
    _isStopping(false),
    _stringLoggerThread(boost::bind(&Log::consumeStringLog, this))
    {
        for (int i = 0; i < numOfConsumerThreads; ++i)
        {
            _threadPool.create_thread(boost::bind(&Log::consumeToLog, this));
        }
    }

    void log(LogLevel l, TSmartPtr msg)
    {
        typename LogObject::SmartPtr logObj(new LogObject(msg, l));
        boost::mutex::scoped_lock lock(_qMutex);
        _queue.push(logObj);
        _qCondVar.notify_one();
    }

    void log(LogLevel l, const std::string& msg)
    {
        typename StringLogObject::SmartPtr logObj(new StringLogObject(msg, l));
        boost::mutex::scoped_lock lock(_stringQMutex);
        _stringQ.push(logObj);
        _stringQCondVar.notify_one();
    }

    virtual ~Log()
    {
        _isStopping = true;
        _threadPool.interrupt_all();
        _threadPool.join_all();
        _stringLoggerThread.interrupt();
        _stringLoggerThread.join();
    }

protected:

    virtual void printLogObject(typename LogObject::SmartPtr) = 0;
    virtual void printLogObject(typename StringLogObject::SmartPtr) = 0;

private:

    void consumeStringLog()
    {
        while (true)
        {
            try
            {
                typename StringLogObject::SmartPtr logObj;
                {
                    boost::mutex::scoped_lock lock(_stringQMutex);

                    while (_stringQ.size() == 0)
                    {
                        if (_isStopping)
                        {
                            std::cout << " Stopping consumeStringLog Thread. " << std::endl;
                            return;
                        }
                        _stringQCondVar.wait(lock);
                    }

                    // Get the entry
                    logObj = _stringQ.front();
                    _stringQ.pop();
                }
                printLogObject(logObj);
            }
            catch (const boost::thread_interrupted& err)
            {
                std::cout << " Log::consumeToLog() - Got Interrupt Signal. " << _queue.size() << std::endl;
            }
        }//while
    }

    void consumeToLog()
    {
        while (true)
        {
            try
            {
                typename LogObject::SmartPtr logObj;
                {
                    boost::mutex::scoped_lock lock(_qMutex);

                    while (_queue.size() == 0)
                    {
                        if (_isStopping)
                        {
                            std::cout << " Stopping consumeToLog Thread. " << std::endl;
                            return;
                        }
                        _qCondVar.wait(lock);
                    }

                    // Get the entry
                    logObj = _queue.front();
                    _queue.pop();
                }
                printLogObject(logObj);
            }
            catch (const boost::thread_interrupted& err)
            {
                std::cout << " Log::consumeToLog() - Got Interrupt Signal. " << _queue.size() << std::endl;
            }
        }//while
    }


};

}
}

#endif	/* LOG_HPP */

