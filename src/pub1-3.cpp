#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <memory>
// #include <chrono>

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("node_pub1_3");
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    auto mypub = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", qos_profile);
    char key;
    //rclcpp::WallRate loop_rate(1.0); //반복주파수를 저장하는 객체(단위 Hz)
    while(rclcpp::ok())
    {
        geometry_msgs::msg::Twist message;
        std::cin >> key;
        switch (key)
        {
            case 'f': message.linear.x = 1; break;
            case 'b': message.linear.x = -1; break;
            case 'l': message.angular.z = 1.5708; break;
            case 'r': message.angular.z = -1.5708; break;
            default: RCLCPP_INFO(node->get_logger(), "bad input"); continue;
        }
        mypub->publish(message);
        RCLCPP_INFO(node->get_logger(), "msg sent");
        //rclcpp::spin_some(node);
        //loop_rate.sleep(); //반복주파수에서 남은 시간 만큼 sleep
    }
    rclcpp::shutdown();
    return 0;
}