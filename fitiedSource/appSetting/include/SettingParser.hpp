/* 
 * File:   SettingParser.hpp
 * Author: ankithbti
 *
 * Created on 9 August, 2015, 9:55 PM
 */

#ifndef SETTINGPARSER_HPP
#define	SETTINGPARSER_HPP

#include <Setting.hpp>

namespace fitiedCoreCpp {
namespace appSetting{

class SettingParser : private boost::noncopyable {
    
public:
    typedef boost::shared_ptr<SettingParser> SmartPtr;
    
    virtual Setting::SmartPtr getRoot() const = 0;
    
    virtual ~SettingParser(){
        
    }
    
};

}
}


#endif	/* SETTINGPARSER_HPP */

