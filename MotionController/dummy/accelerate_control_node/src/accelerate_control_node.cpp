#include "rclcpp/rclcpp.hpp"
#include "can_msgs/msg/ad_control_accelerate.hpp"
#include <iostream>

class AccelerateControlNode : public rclcpp::Node {
public:
    AccelerateControlNode() : Node("accelerate_control_node") {
        // 토픽 발행자 설정
        publisher_ = this->create_publisher<can_msgs::msg::AdControlAccelerate>("/drive/can/ad_control_accelerate", 10);

        // 사용자로부터 입력 받기
        std::cout << "Enter acceleration command (float64): ";
        std::cin >> acceleration_;

        std::cout << "Enter speed control (float64): ";
        std::cin >> speed_control_;

        // 몇 번 보낼지 입력 받기
        std::cout << "Enter the number of messages to send: ";
        std::cin >> num_messages_;

        // 메시지 발행
        publishMessages();
    }

private:
    void publishMessages() {
        can_msgs::msg::AdControlAccelerate msg;
        msg.acc = acceleration_;
        msg.speed_control = speed_control_;

        for (int i = 0; i < num_messages_; ++i) {
            publisher_->publish(msg);
            rclcpp::sleep_for(std::chrono::milliseconds(20)); // 0.02초(20밀리초) 슬립
        }
    }

    double acceleration_;
    double speed_control_;
    int num_messages_;
    rclcpp::Publisher<can_msgs::msg::AdControlAccelerate>::SharedPtr publisher_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AccelerateControlNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

