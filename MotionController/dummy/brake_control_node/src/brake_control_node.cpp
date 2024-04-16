#include "rclcpp/rclcpp.hpp"
#include "can_msgs/msg/ad_control_brake.hpp"
#include <iostream>

class BrakeControlNode : public rclcpp::Node {
public:
    BrakeControlNode() : Node("brake_control_node") {
        // 토픽 발행자 설정
        publisher_ = this->create_publisher<can_msgs::msg::AdControlBrake>("/drive/can/ad_control_brake", 10);

        // 사용자로부터 입력 받기
        std::cout << "Enter brake pressure command (int32): ";
        std::cin >> brake_pressure_;

        // 몇 번 보낼지 입력 받기
        std::cout << "Enter the number of messages to send: ";
        std::cin >> num_messages_;

        // 메시지 발행
        publishMessages();
    }

private:
    void publishMessages() {
        can_msgs::msg::AdControlBrake msg;
        msg.brakepressure_cmd = brake_pressure_;

        for (int i = 0; i < num_messages_; ++i) {
            publisher_->publish(msg);
            rclcpp::sleep_for(std::chrono::milliseconds(20)); // 0.02초(20밀리초) 슬립
        }
    }

    int32_t brake_pressure_;
    int num_messages_;
    rclcpp::Publisher<can_msgs::msg::AdControlBrake>::SharedPtr publisher_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<BrakeControlNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

