#include <ros/ros.h>
#include <gtest/gtest.h>
#include "beginner_tutorials/AddTwoInts.h"

class Service {  
  public:  
    ros::NodeHandle n;   
    ros::ServiceClient client;
    ros::ServiceServer mServer;
    int a =1,b =2,sum =3;
    bool mService;    
    bool callback(beginner_tutorials::AddTwoInts::Request& req, beginner_tutorials::AddTwoInts::Response& res){
      a = (int)req.a;
      b = (int)req.b;      
      sum = a + b;
      mService = true;
      ROS_INFO("request: x=%i, y=%i", a, b);
      return mService;
    }     
    Service(): mService(false){
      mServer = n.advertiseService("add_two_ints", &Service::callback, this);
      //ros::spinOnce();
    }
    
    int getA(){return a;}
    ~Service() {}
    const int& result() const { return sum; 
    }    
};

class TestSuite : public testing::Test {
  public:  
    Service s;    
    virtual ~TestSuite(){}

    virtual void SetUp() override
      {          
        s.client = s.n.serviceClient<beginner_tutorials::AddTwoInts>("add_two_ints");
        beginner_tutorials::AddTwoInts srv;
        srv.request.a = 10;
        srv.request.b = 20;
        EXPECT_TRUE(s.client.call(srv))<< "Error setup"; 
      }
    virtual void TearDown() override {     
    }
};

TEST_F(TestSuite, inputTest) {     
  EXPECT_EQ(s.getA(), 10) << "Failed to receive a";
}

// TEST_F(TestSuite, registrationTest) {  
//   EXPECT_EQ((int)b, 30) << "Failed to receive b";
// }

// TEST_F(TestSuite, registrationTest) {  
//   EXPECT_EQ((int)sum, 40) << "The sum is not not calculated correctly";
// }

int main(int argc, char** argv){
  //ros::init(argc, argv, "add_two_ints_server");
  ros::init(argc, argv, "add_two_ints");
  testing::InitGoogleTest(&argc, argv);
  //while(ros::ok()) 
  // ros::spinOnce();
  auto res = RUN_ALL_TESTS();

  ros::shutdown();
  return res;
}
