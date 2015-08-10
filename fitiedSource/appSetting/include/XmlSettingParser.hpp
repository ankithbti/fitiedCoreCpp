/* 
 * File:   XmlSettingParser.hpp
 * Author: ankithbti
 *
 * Created on 9 August, 2015, 9:44 PM
 */

#ifndef XMLSETTINGPARSER_HPP
#define	XMLSETTINGPARSER_HPP

#include <tinyxml.h>
#include <SettingParser.hpp>
#include <fstream>
#include <SimpleFileLogger.hpp>
#include <queue>

namespace fitiedCoreCpp
{
namespace appSetting
{

struct NodeWithParent
{
    typedef boost::shared_ptr<NodeWithParent> SmartPtr;

    Setting::SmartPtr _parent;
    TiXmlElement * _node;

    NodeWithParent(Setting::SmartPtr parent, TiXmlElement* node) :
    _parent(parent),
    _node(node)
    {

    }

};

class XmlSettingParser : public SettingParser
{
public:
    typedef boost::shared_ptr<XmlSettingParser> SmartPtr;
    typedef std::queue<NodeWithParent::SmartPtr> XmlNodesWithParentQ;

private:

    std::string _xmlFileName;
    Setting::SmartPtr _rootSetting;
    std::ifstream _fileStream;
    fitiedCoreCpp::appLogger::SimpleFileLogger _logger;
    XmlNodesWithParentQ _nodesWithParentQ;

public:
    XmlSettingParser(const std::string& xmlFile);

    virtual Setting::SmartPtr getRoot() const
    {
        return _rootSetting;
    }

    virtual ~XmlSettingParser()
    {

    }

private:
    void parseXmlFile();

    // Recursive Function
    void parseXmlElement(TiXmlElement* elem, Setting::SmartPtr parent = Setting::SmartPtr());
};

}
}

#endif	/* XMLSETTINGPARSER_HPP */

