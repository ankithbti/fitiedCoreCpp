/* 
 * File:   PBSchemaAdaptor.hpp
 * Author: ankithbti
 *
 * Created on 5 January, 2016, 12:33 AM
 */

#ifndef PBSCHEMAADAPTOR_HPP
#define	PBSCHEMAADAPTOR_HPP

#include <Common.hpp>
#include <Message.hpp>

namespace genericTransport
{

class PBSchemaAdaptor
{
public:

    void parseFromBuffer(const ArrayBuffer& buffer, HBMessage&);
    void convertToBuffer(ArrayBuffer& buffer, const HBMessage&);
    
    // Will override these for all Message Types

};
}

#endif	/* PBSCHEMAADAPTOR_HPP */

