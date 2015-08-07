#include <tinyxml.h>
#include <iostream>

int main(){
    TiXmlDocument doc("demotest.xml");
    if(!doc.LoadFile()){
        std::cout << " Failed. " << std::endl;
        return -1;
    }
    std::cout << " Success. " << std::endl;
    return 0;
}
