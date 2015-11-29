#include <gtest/gtest.h>
//#include <mysql++/mysql++.h>
#include <iostream>
#include <TcpServerTransport.hpp>
#include <Common.hpp>

namespace genericTransport{

class SA {
public:
    SA(boost::shared_ptr<TcpClientConnection<genericTransport::ArrayBuffer, SA> > client){
        
    }
};

}

TEST(AddTest, Positive){
    EXPECT_EQ(3,3);
    EXPECT_EQ(1,1);
}

TEST(TcpServer, Positive){
    EXPECT_TRUE(true);
}

/*
TEST(AddTest, mysqlTest){
    try{
//        mysqlpp::Connection conn(false);
//        conn.connect("test", "localhost", "root", "saring");
//        mysqlpp::Query q = conn.query();
//        q << "select * from employee";
//        
//        mysqlpp::StoreQueryResult res = q.store();
//        for(int i = 0 ; i < res.num_rows() ; ++i){
//            std::cout << " Query result : " << res[i]["name"] <<  " Rows: " << res[i]["age"] << std::endl;
//        }
        
//    }catch(const mysqlpp::BadQuery& err){
//        std::cout << " BadQuery Exception - " << err.what() << std::endl;
//    }catch(const mysqlpp::BadConversion& err){
//        std::cout << " BadConversion Exception - " << err.what() << std::endl;
    }catch(const std::exception& err){
        std::cout << " Exception - " << err.what() << std::endl;
    }
}
*/

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
