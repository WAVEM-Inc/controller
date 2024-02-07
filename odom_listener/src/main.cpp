// odom_listener.cpp: Listens to /odom topic and logs the odometry messages.

#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/odometry.hpp"

class OdomListener : public rclcpp::Node {
 public:
  OdomListener() : Node("odom_listener") {
    listener_ = this->create_subscription<nav_msgs::msg::Odometry>(
        "/odom", 10, std::bind(&OdomListener::OdomCallback, this, std::placeholders::_1));
  }

 private:
  void OdomCallback(const nav_msgs::msg::Odometry::SharedPtr msg) const {
    RCLCPP_INFO(this->get_logger(), "Received odometry message:\nFrame ID: '%s', Child Frame ID: '%s'",
                msg->header.frame_id.c_str(), msg->child_frame_id.c_str());
    // Additional message processing can be done here.
  }

  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr listener_;
};

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<OdomListener>());
  rclcpp::shutdown();
  return 0;
}

