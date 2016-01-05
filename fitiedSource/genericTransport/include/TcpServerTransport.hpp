/* 
 * File:   TcpServerTransport.hpp
 * Author: ankithbti
 *
 * Created on 29 November, 2015, 9:11 PM
 */

#ifndef TCPSERVERTRANSPORT_HPP
#define	TCPSERVERTRANSPORT_HPP

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <TcpConnectionManager.hpp>
#include <TcpClientConnection.hpp>
#include <Common.hpp>
#include <iostream>

namespace genericTransport
{


// To DO - Remove template here....Only Channel will have SA
template <typename SchemaAdaptor>
class TcpServerTransport : private boost::noncopyable
{
public:
    typedef boost::shared_ptr<TcpServerTransport<SchemaAdaptor> > SmartPtr;

private:
    std::string _host;
    std::string _port;
    boost::asio::io_service _ioService;
    boost::asio::io_service::work _ioWork;
    SocketSmartPtr _socket;
    boost::asio::ip::tcp::acceptor _acceptor;
    boost::shared_ptr<boost::thread> _ioServiceThread;
    boost::mutex _startStopMutex;
    boost::shared_ptr<TcpConnectionManager<SchemaAdaptor> > _manager;

    void do_accept()
    {
        if (_acceptor.is_open())
        {
            _acceptor.async_accept(*(_socket.get()), boost::bind(&TcpServerTransport<SchemaAdaptor>::asyncAccept, this, _1));
        }
    }

    void asyncAccept(boost::system::error_code ec)
    {
        if (!_acceptor.is_open())
        {
            std::cout << __FUNCTION__ << " :: Acceptor is not open." << std::endl;
            return;
        }

        if (!ec)
        {
            std::cout << __FUNCTION__ << " :: Accepted client connection." << std::endl;
            boost::shared_ptr<TcpClientConnection<SchemaAdaptor> > clientConn(new TcpClientConnection<SchemaAdaptor>(_socket, _manager));
            _manager->start(clientConn);
            _socket = SocketSmartPtr(new boost::asio::ip::tcp::socket(_ioService));
        }
        else
        {
            std::cout << __FUNCTION__ << " :: Error while accepting : " << ec.message() << std::endl;
        }

        // Ready to accept new request
        do_accept();
    }

    void runIoService()
    {
        std::cout << __FUNCTION__ << " :: Started ioService." << std::endl;
        _ioService.run();
        std::cout << __FUNCTION__ << " :: Stopped ioService." << std::endl;
    }


public:

    TcpServerTransport(const std::string& host, const std::string& port) :
    _host(host),
    _port(port),
    _ioService(),
    _ioWork(_ioService),
    _socket(new boost::asio::ip::tcp::socket(_ioService)),
    _acceptor(_ioService),
    _manager(new TcpConnectionManager<SchemaAdaptor>())
    {

        boost::asio::ip::tcp::resolver resolver(_ioService);
        boost::asio::ip::tcp::resolver::query query(_host, _port);
        boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
        _acceptor.open(endpoint.protocol());
        _acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
        _acceptor.bind(endpoint);
        _acceptor.listen();


        do_accept();
    }

    ~TcpServerTransport()
    {
        //stop();
        if (_socket)
        {
            if (_socket->is_open())
            {
                _socket->close();
            }
            _socket.reset();
        }
    }

    void start()
    {
        boost::unique_lock<boost::mutex> lock(_startStopMutex);
        std::cout << __FUNCTION__ << " :: Starting TCP Server." << std::endl;
        if (!_ioServiceThread)
        {
            _ioServiceThread = boost::shared_ptr<boost::thread>(new boost::thread(&TcpServerTransport<SchemaAdaptor>::runIoService, this));
        }
        do_accept();
        std::cout << __FUNCTION__ << " :: Started TCP Server." << std::endl;
    }

    void stop()
    {
        boost::unique_lock<boost::mutex> lock(_startStopMutex);

        std::cout << __FUNCTION__ << " :: Stopping TCP Server." << std::endl;

        if(_acceptor.is_open()){
            _acceptor.close();
        }
        
        _manager->stopAll();
        std::cout << __FUNCTION__ << " :: Stopped TCP Server." << std::endl;

    }
    
    void send(const ArrayBuffer& buffer, int clientId){
        // _manager get the appropriate Client Connection and sends data to it
    }




};

}
#endif	/* TCPSERVERTRANSPORT_HPP */

