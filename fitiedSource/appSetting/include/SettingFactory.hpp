/* 
 * File:   SettingFactory.hpp
 * Author: ankithbti
 *
 * Created on 10 August, 2015, 10:24 PM
 */

#ifndef SETTINGFACTORY_HPP
#define	SETTINGFACTORY_HPP

#include <SettingParser.hpp>

namespace fitiedCoreCpp
{
namespace appSetting
{

class SettingFactory : private boost::noncopyable
{
public:
    typedef boost::shared_ptr<SettingFactory> SmartPtr;

    enum ParserType
    {
        XML = 0,
        JSON,
        DATABASE
    };

    SettingParser::SmartPtr getSettingParser(ParserType type, const std::string& fileOrDbServerName,
                                             const std::string& dbUserName = std::string(),
                                             const std::string& dbUserName = std::string());

};
}
}


#endif	/* SETTINGFACTORY_HPP */

