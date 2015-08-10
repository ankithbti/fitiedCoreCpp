#include <Setting.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <stdexcept>

namespace fitiedCoreCpp
{
namespace appSetting
{

bool Setting::isAttributePresent(const std::string& name) const
{

    BOOST_FOREACH(Attribute::SmartPtr attr, _attributes)
    {
        if (boost::iequals(attr->getName(), name))
        {
            return true;
        }
    }
    return false;
}

const std::string& Setting::getAttributeValue(const std::string& name) const
{

    BOOST_FOREACH(Attribute::SmartPtr attr, _attributes)
    {
        if (boost::iequals(attr->getName(), name))
        {
            return attr->getValue();
        }
    }
    throw std::runtime_error("Setting::getAttributeValue() - For Setting: [ " + _name + " ] No attribute found for Name: [ " + name + " ]");
}

bool Setting::isChildPresent(const std::string& name) const
{

    BOOST_FOREACH(Setting::SmartPtr child, _children)
    {
        if (boost::iequals(child->_name, name))
        {
            return true;
        }
    }
    return false;
}

Setting::SmartPtr Setting::getChild(const std::string& name)
{

    BOOST_FOREACH(Setting::SmartPtr child, _children)
    {
        if (boost::iequals(child->_name, name))
        {
            return child;
        }
    }
    throw std::runtime_error("Setting::getChild() - For Setting: [ " + _name + " ] No child found for Name: [ " + name + " ]");
}


}
}