/* 
 * File:   Message.hpp
 * Author: ankithbti
 *
 * Created on 5 January, 2016, 12:32 AM
 */

#ifndef MESSAGE_HPP
#define	MESSAGE_HPP

#include <Common.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>

namespace genericTransport {

class MessageVistor;
class Message : private boost::noncopyable {
    
public:
    typedef boost::shared_ptr<Message> SmartPtr;
    
    virtual void accept(boost::shared_ptr<MessageVistor>, ArrayBuffer) = 0;
};

class HBMessage : public Message, public boost::enable_shared_from_this<HBMessage>{
public:
    typedef boost::shared_ptr<HBMessage> SmartPtr;
    void accept(boost::shared_ptr<MessageVistor> mv, ArrayBuffer buffer);
    
};

}


#endif	/* MESSAGE_HPP */

