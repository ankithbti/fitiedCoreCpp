#include <SimpleFileLogger.hpp>
#include <sstream>
#include <stdexcept>

namespace fitiedCoreCpp
{
namespace appLogger
{

SimpleFileLogger::SimpleFileLogger(const std::string& fileNamePrefix, const std::string& logPath) :
_fileNamePrefix(fileNamePrefix),
_logPath(logPath)
{
    if(_logPath.empty()){
        _logPath = ".";
    }
    if( *_logPath.rbegin() != '/'){
        _logPath += "/";
    }
    boost::posix_time::ptime currDateTime(boost::posix_time::microsec_clock::local_time());
    std::stringstream fullFileName;
    fullFileName << _logPath << _fileNamePrefix << "_" << currDateTime << ".log" ;
    _absFileName = fullFileName.str();
    _outputFileStream.open(_absFileName.c_str(), std::ofstream::out);
    if(!_outputFileStream.good()){
        throw std::runtime_error("SimpleFileLogger::SimpleFileLogger() - Failed to open file for writing :: " + _absFileName);
    }
}

void SimpleFileLogger::printLogObject(LogObject::SmartPtr obj)
{

}

void SimpleFileLogger::printLogObject(StringLogObject::SmartPtr obj)
{
    _outputFileStream << obj->_timeStamp << " " << 
            obj->_levelStr << " - " <<
            obj->_obj << std::endl;
}

SimpleFileLogger::~SimpleFileLogger()
{
    _outputFileStream.flush();
    _outputFileStream.close();
}




}
}
