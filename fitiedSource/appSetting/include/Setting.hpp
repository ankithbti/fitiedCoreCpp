/* 
 * File:   Setting.hpp
 * Author: ankithbti
 *
 * Created on 9 August, 2015, 7:55 PM
 */

#ifndef SETTING_HPP
#define	SETTING_HPP

#include <boost/noncopyable.hpp>
#include <Attribute.hpp>
#include <vector>

namespace fitiedCoreCpp
{
namespace appSetting
{

class Setting : private boost::noncopyable
{
public:
    typedef boost::shared_ptr<Setting> SmartPtr;
    typedef std::vector<Attribute::SmartPtr> AttributeList;
    typedef AttributeList::iterator AttributeListIt;
    typedef AttributeList::const_iterator AttributeListConstIt;
    typedef std::vector<Setting::SmartPtr> ChildrenList;
    typedef ChildrenList::iterator ChildrenListIt;
    typedef ChildrenList::const_iterator ChildrenListConstIt;

private:

    std::string _name;
    std::string _value;
    AttributeList _attributes;
    ChildrenList _children;

public:

    Setting(const std::string& name, const std::string& val = std::string()) :
    _name(name),
    _value(val)
    {

    }

    void setValue(const std::string& value)
    {
        _value = value;
    }

    const std::string& getName() const
    {
        return _name;
    }

    const std::string& getValue() const
    {
        return _value;
    }

    void addAttribute(Attribute::SmartPtr attr)
    {
        _attributes.push_back(attr);
    }

    std::pair<AttributeListConstIt, AttributeListConstIt> getAttributeIterators() const
    {
        return std::make_pair<AttributeListConstIt, AttributeListConstIt>(_attributes.begin(), _attributes.end());
    }

    bool isAttributePresent(const std::string& name) const;
    const std::string& getAttributeValue(const std::string& name) const;

    size_t getAttributesCount() const
    {
        return _attributes.size();
    }

    void addChild(Setting::SmartPtr child)
    {
        _children.push_back(child);
    }

    std::pair<ChildrenListConstIt, ChildrenListConstIt> getChildrenIterators() const
    {
        return std::make_pair<ChildrenListConstIt, ChildrenListConstIt>(_children.begin(), _children.end());
    }

    bool isChildPresent(const std::string& name) const;
    Setting::SmartPtr getChild(const std::string& name);

    size_t getChildCount() const
    {
        return _children.size();
    }

    bool isLeaf() const
    {
        return (_children.size() == 0);
    }

};

}
}

#endif	/* SETTING_HPP */

