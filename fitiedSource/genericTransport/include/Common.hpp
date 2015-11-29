/* 
 * File:   Common.hpp
 * Author: ankithbti
 *
 * Created on 29 November, 2015, 9:32 PM
 */

#ifndef COMMON_HPP
#define	COMMON_HPP

#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

namespace genericTransport {

typedef boost::shared_ptr<boost::asio::ip::tcp::socket> SocketSmartPtr;
typedef boost::array<char, 8192> ArrayBuffer;

}

#endif	/* COMMON_HPP */

