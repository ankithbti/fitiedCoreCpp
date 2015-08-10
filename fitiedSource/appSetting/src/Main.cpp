#include <iostream>
#include <XmlSettingParser.hpp>

using namespace fitiedCoreCpp::appSetting;
int main()
{
std::cout << " Test " << std::endl;
try{
XmlSettingParser parser("../config/demo.xml");
}catch(const std::runtime_error& err){
    std::cout << " Error: " << err.what() << std::endl; 
}
sleep(5);

return 0;
}
