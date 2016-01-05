/* 
 * File:   Channel.hpp
 * Author: ankithbti
 *
 * Created on 5 January, 2016, 12:42 AM
 */

#ifndef CHANNEL_HPP
#define	CHANNEL_HPP

#include <Common.hpp>
#include <Setting.hpp>
#include <boost/variant.hpp>
#include <boost/function.hpp>
#include "MessageVisitor.hpp"



namespace genericTransport {


template <typename Transport, typename SchemaAdaptor>
class Channel {
    public:
        typedef boost::variant< boost::function< void (Message::SmartPtr) > > CallbackType ;
        typedef std::map<int, CallbackType> CallbackContainer;
private:
    fitiedCoreCpp::appSetting::Setting::SmartPtr _channelSettings;
    CallbackContainer _callbacks;
    Transport _transport;
    SchemaAdaptor _schemaAdaptor;
    
public:
    
    Channel(fitiedCoreCpp::appSetting::Setting::SmartPtr setting, CallbackContainer ccc) : _channelSettings(setting),
    _callbacks(ccc){
        
    }
    
    void registerClientCallback(int id, boost::function<void(Message)> callback){
        _callbacks.insert(id, callback);
    }
    
    // Some  more registered callbacks can also come.
    
    //void registerOnReadCallback(int messageID, boost::function)
    // Transport Settings and callbacks will be passed to Transport
    
    void start();
    void stop();
    
    template < typename Message>
    void send(const Message& msg, int clientId = 0){
        // ClientId will be used in case of Server
        ArrayBuffer buffer;
        ConvertToBufferMessageVisitor<SchemaAdaptor> cmv(_schemaAdaptor);
        msg.accept(cmv, buffer);
        // send these bytes buffer to TCP 
        // _transport.send(buffer, clientId);
    }
    
    void onReadBytesCallback(ArrayBuffer, int noOfBytes);
    
    
};

}

#endif	/* CHANNEL_HPP */

