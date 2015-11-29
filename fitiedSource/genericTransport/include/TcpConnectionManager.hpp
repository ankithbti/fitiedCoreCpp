/* 
 * File:   TcpConnectionManager.hpp
 * Author: ankithbti
 *
 * Created on 29 November, 2015, 9:34 PM
 */

#ifndef TCPCONNECTIONMANAGER_HPP
#define	TCPCONNECTIONMANAGER_HPP

#include <TcpClientConnection.hpp>
#include <boost/foreach.hpp>
#include <set>


namespace genericTransport
{

template <typename SchemaAdaptor>
class TcpConnectionManager
{
    typedef std::set<typename TcpClientConnection<SchemaAdaptor>::SmartPtr > ClientConnections;
    typedef typename std::set<typename TcpClientConnection<SchemaAdaptor>::SmartPtr >::iterator ClientConnectionsIt;
    ClientConnections _clientConnections;

public:
    
    void start(typename TcpClientConnection<SchemaAdaptor>::SmartPtr c){
        _clientConnections.insert(c);
        c->start();
        
    }
    
    void stop(typename TcpClientConnection<SchemaAdaptor>::SmartPtr c){
        _clientConnections.erase(c);
        c->stop();
    }
    
    void stopAll(){
        
        for(ClientConnectionsIt it = _clientConnections.begin(); it != _clientConnections.end() ; ++it){
            //(static_cast<TcpClientConnection<Message, SchemaAdaptor> >(*it)).stop();
        }
        _clientConnections.clear();
        
    }
};

}

#endif	/* TCPCONNECTIONMANAGER_HPP */

