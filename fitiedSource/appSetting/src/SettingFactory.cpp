#include <SettingFactory.hpp>

#include "XmlSettingParser.hpp"

namespace fitiedCoreCpp
{
namespace appSetting
{

SettingParser::SmartPtr SettingFactory::getSettingParser(ParserType type,
                                                         const std::string& fileOrDbServerName,
                                                         const std::string& dbUserName,
                                                         const std::string& dbUserName)
{

    SettingParser::SmartPtr parser;

    switch (type)
    {
    case XML:
        parser = SettingParser::SmartPtr(new XmlSettingParser(fileOrDbServerName));
        break;
    case JSON:
        throw std::runtime_error("SettingFactory::getSettingParser() - Not Implemented yet.");
        break;
    case DATABASE:
        throw std::runtime_error("SettingFactory::getSettingParser() - Not Implemented yet.");
        break;
    default:
        throw std::runtime_error("SettingFactory::getSettingParser() - No Default Implemented yet.");
        break;
    }
    return parser;
}


}
}
