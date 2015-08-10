#include <XmlSettingParser.hpp>

namespace fitiedCoreCpp
{
namespace appSetting
{

XmlSettingParser::XmlSettingParser(const std::string& xmlFile) :
_xmlFileName(xmlFile),
_fileStream(xmlFile.c_str()),
_logger("XmlSettingParser")
{
    if (!_fileStream.good())
    {
        throw std::runtime_error("XmlSettingParser::XmlSettingParser() - Failed to read xmlFile: [ " + xmlFile + " ]");
    }
    // Close the file Stream as we don't need it now.
    _fileStream.close();

    // Now parse the file
    parseXmlFile();
}

void XmlSettingParser::parseXmlFile()
{
    TiXmlDocument doc(_xmlFileName.c_str());
    if (!doc.LoadFile())
    {
        throw std::runtime_error("XmlSettingParser::parseXmlFile() - Failed to load XmlFile: [ " + _xmlFileName + " ]");
    }

    TiXmlHandle handleDoc(&doc);
    TiXmlElement *pElem = handleDoc.FirstChildElement().Element();

    if (!pElem)
    {
        throw std::runtime_error("XmlSettingParser::parseXmlFile() - No Xml Tag present in XmlFile: [ " + _xmlFileName + " ]");
    }


    Setting::SmartPtr rootSetting(new Setting(pElem->Value()));
    TiXmlAttribute * attr = pElem->FirstAttribute();
    while (attr)
    {
        rootSetting->addAttribute(Attribute::SmartPtr(new Attribute(attr->Name(), attr->Value())));
        attr = attr->Next();
    }
    _rootSetting = rootSetting;

    TiXmlElement * child = pElem->FirstChildElement();
    if (child)
    {
        parseXmlElement(child, _rootSetting);
    }
}

void XmlSettingParser::parseXmlElement(TiXmlElement* e, Setting::SmartPtr parent)
{
    if (!e || !parent)
    {
        return;
    }

    // Iterating Siblings
    while (e)
    {
        NodeWithParent::SmartPtr nodeWithParent(new NodeWithParent(parent, e));
        _nodesWithParentQ.push(nodeWithParent);

        Setting::SmartPtr node(new Setting(e->Value()));
        TiXmlAttribute * attr = e->FirstAttribute();
        while (attr)
        {
            node->addAttribute(Attribute::SmartPtr(new Attribute(attr->Name(), attr->Value())));
            attr = attr->Next();
        }
        parent->addChild(node);

        e = e->NextSiblingElement();
    }

    // Iterate its child
    while (_nodesWithParentQ.size() > 0)
    {
        NodeWithParent::SmartPtr node = _nodesWithParentQ.front();
        _nodesWithParentQ.pop();
        parseXmlElement(node->_node->FirstChildElement(), node->_parent->getChild(node->_node->Value()));
    }


}



}
}
