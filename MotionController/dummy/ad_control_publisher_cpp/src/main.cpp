#include "rclcpp/rclcpp.hpp"
#include "can_msgs/msg/ad_control_body.hpp"
#include <iostream>

using std::cin;

class AdControlPublisher : public rclcpp::Node
{
public:
    AdControlPublisher()
        : Node("ad_control_publisher")
    {
        publisher_ = this->create_publisher<can_msgs::msg::AdControlBody>("/drive/can/ad_control_body", 10);
        getInputAndPublish();
    }

private:
    void getInputAndPublish()
    {
        while (rclcpp::ok())
        {
            can_msgs::msg::AdControlBody msg;

            // Get input from the user
            std::cout << "Enter the status of each control (1 for ON, 0 for OFF):\n";
            std::cout << "Fog Light: ";
            std::cin >> msg.fog_light;
            std::cout << "Low Beam: ";
            std::cin >> msg.low_beam;
            std::cout << "Reversing Light: ";
            std::cin >> msg.reversing_light;
            std::cout << "Double Flash Light: ";
            std::cin >> msg.double_flash_light;
            std::cout << "Brake Light: ";
            std::cin >> msg.brake_light;
            std::cout << "Horn Control: ";
            std::cin >> msg.horn_control;
            std::cout << "High Beam: ";
            std::cin >> msg.high_beam;
            std::cout << "Right Turn Light: ";
            std::cin >> msg.right_turn_light;
            std::cout << "Left Turn Light: ";
            std::cin >> msg.left_turn_light;

            // Publish the message
            publisher_->publish(msg);
        }
    }

    rclcpp::Publisher<can_msgs::msg::AdControlBody>::SharedPtr publisher_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AdControlPublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

