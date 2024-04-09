#include "rclcpp/rclcpp.hpp"
#include "can_msgs/msg/ad_control_steering.hpp"
#include <iostream>

class SteeringControlNode : public rclcpp::Node {
public:
    SteeringControlNode() : Node("steering_control_node") {
        // 토픽 발행자 설정
        publisher_ = this->create_publisher<can_msgs::msg::AdControlSteering>("/drive/can/ad_control_steering", 10);

        // 사용자로부터 입력 받기
        std::cout << "Enter steering speed command (float64): ";
        std::cin >> speed_;
        std::cout << "Enter steering angle command (float64): ";
        std::cin >> angle_;

        // 몇 번 보낼지 입력 받기
        std::cout << "Enter the number of messages to send: ";
        std::cin >> num_messages_;

        // 메시지 발행
        publishMessages();
    }

private:
    void publishMessages() {
        can_msgs::msg::AdControlSteering msg;
        msg.steering_speed_cmd = speed_;
        msg.steering_angle_cmd = angle_;

        for (int i = 0; i < num_messages_; ++i) {
            publisher_->publish(msg);
	    rclcpp::sleep_for(std::chrono::milliseconds(20)); 
        }
    }

    double speed_;
    double angle_;
    int num_messages_;
    rclcpp::Publisher<can_msgs::msg::AdControlSteering>::SharedPtr publisher_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SteeringControlNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

