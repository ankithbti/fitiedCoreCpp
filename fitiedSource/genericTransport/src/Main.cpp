#include <iostream>
#include <TcpServerTransport.hpp>

namespace genericTransport{
class SA {
public:
    SA(){
        
    }
};

}

int main(){
    std::cout << " Testing " << std::endl;
    
    genericTransport::TcpServerTransport<genericTransport::SA> tcpServer("127.0.0.1", "9867");
    tcpServer.start();
    
    std::cout << " Going to wait. " << std::endl;
    
    boost::this_thread::sleep(boost::posix_time::milliseconds(50000));
    
    std::cout << " End wait. " << std::endl;
    tcpServer.stop();
    
    return 0;
}
