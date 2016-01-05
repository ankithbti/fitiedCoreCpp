/* 
 * File:   MessageVisitor.hpp
 * Author: ankithbti
 *
 * Created on 6 January, 2016, 12:35 AM
 */

#ifndef MESSAGEVISITOR_HPP
#define	MESSAGEVISITOR_HPP

#include <Message.hpp>

namespace genericTransport {

class MessageVistor {
    
public:
    typedef boost::shared_ptr<MessageVistor> SmartPtr;
    
    virtual void visit(HBMessage::SmartPtr, ArrayBuffer) = 0;
    
    // And all other types of supported messages
    
};

template <typename SchemaAdaptor>
class ConvertToBufferMessageVisitor : public MessageVistor {
    
private:
    SchemaAdaptor _sa;
public:
    ConvertToBufferMessageVisitor(SchemaAdaptor sa) : _sa(sa){
        
    }
    
    void visit(HBMessage::SmartPtr msg, ArrayBuffer buffer){
        _sa.convertToBuffer(buffer, msg);
    }
};

template <typename SchemaAdaptor>
class ParseFromBufferMessageVisitor : public MessageVistor {
    
private:
    SchemaAdaptor _sa;
public:
    ParseFromBufferMessageVisitor(SchemaAdaptor sa) : _sa(sa){
        
    }
    
    void visit(HBMessage::SmartPtr msg, ArrayBuffer buffer){
        _sa.parseFromBuffer(buffer, msg);
    }
};




}

#endif	/* MESSAGEVISITOR_HPP */

