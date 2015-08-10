/* 
 * File:   Attribute.hpp
 * Author: ankithbti
 *
 * Created on 9 August, 2015, 8:01 PM
 */

#ifndef ATTRIBUTE_HPP
#define	ATTRIBUTE_HPP

#include <iostream>
#include <boost/shared_ptr.hpp>

namespace fitiedCoreCpp
{
namespace appSetting
{

class Attribute
{
public:

    typedef boost::shared_ptr<Attribute> SmartPtr;

private:

    std::string _name;
    std::string _value;

public:

    Attribute(const std::string& name, const std::string& value) :
    _name(name),
    _value(value)
    {

    }

    const std::string& getName() const
    {
        return _name;
    }

    const std::string& getValue() const
    {
        return _value;
    }

};
}
}


#endif	/* ATTRIBUTE_HPP */

