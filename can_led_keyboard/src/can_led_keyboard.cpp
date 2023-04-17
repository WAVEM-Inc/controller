#include "can_led_keyboard/can_led_keyboard.hpp"

KeyboardPublisher::KeyboardPublisher()
: Node("keyboard_publisher"),tp_control_hardware(TP_CONTROL_HARD_WARE){
    fn_start();
    fn_print_key();
    m_publisher = this->create_publisher<can_msgs::msg::ControlHardware>(tp_control_hardware, 10);
    m_timer = this->create_wall_timer(100ms, std::bind(&KeyboardPublisher::fn_timer_callback, this));
}
void KeyboardPublisher::fn_print_key(){
    std::cout << "h : horrn, "<< "l : head_light, " << " j : left_light, " << "k : right_light, "<< "s : all off, " << "a : all on"<<std::endl;
}

void KeyboardPublisher::fn_start(){
        std::cout<<R"(
  /$$$$$$   /$$$$$$  /$$   /$$        /$$       /$$$$$$$$ /$$$$$$$        /$$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$$  /$$$$$$$ 
 /$$__  $$ /$$__  $$| $$$ | $$       | $$      | $$_____/| $$__  $$      | $$__  $$ /$$__  $$ /$$__  $$| $$__  $$| $$__  $$
| $$  \__/| $$  \ $$| $$$$| $$       | $$      | $$      | $$  \ $$      | $$  \ $$| $$  \ $$| $$  \ $$| $$  \ $$| $$  \ $$
| $$      | $$$$$$$$| $$ $$ $$       | $$      | $$$$$   | $$  | $$      | $$$$$$$ | $$  | $$| $$$$$$$$| $$$$$$$/| $$  | $$
| $$      | $$__  $$| $$  $$$$       | $$      | $$__/   | $$  | $$      | $$__  $$| $$  | $$| $$__  $$| $$__  $$| $$  | $$
| $$    $$| $$  | $$| $$\  $$$       | $$      | $$      | $$  | $$      | $$  \ $$| $$  | $$| $$  | $$| $$  \ $$| $$  | $$
|  $$$$$$/| $$  | $$| $$ \  $$       | $$$$$$$$| $$$$$$$$| $$$$$$$/      | $$$$$$$/|  $$$$$$/| $$  | $$| $$  | $$| $$$$$$$/
 \______/ |__/  |__/|__/  \__//$$$$$$|________/|________/|_______//$$$$$$|_______/  \______/ |__/  |__/|__/  |__/|_______/ 
                             |______/                            |______/                                                  
                                                                                                                           
                                                                                                                           
)" <<std::endl;
}

void KeyboardPublisher::fn_timer_callback(){
     if (fn_kbhit()) {
      char c = getchar();
      can_msgs::msg::ControlHardware msg;
      fn_print_key();
      switch (c) {
        case 'h':
            std::cout << "msg : horn on" <<std::endl;
            msg.horn = true;
            break;
        case 'l':
            std::cout << "msg : head_light on" <<std::endl;
            msg.head_light = true;
            break;
        case 'j':
            std::cout << "msg : left_light on" <<std::endl;
            msg.left_light = true;
            break;
        case 'k':
            std::cout << "msg : right_light on" <<std::endl;
            msg.right_light = true;
            break;
        case 's' :
            std::cout << "msg : all off" <<std::endl;
            break;
        case 'a' :
            std::cout << "msg : all on" <<std::endl;
            msg.right_light = true;
            msg.left_light = true;
            msg.head_light = true;
            msg.horn = true;
            break;
        default:
          return;
      }

      m_publisher->publish(msg);
    }
}

bool KeyboardPublisher::fn_kbhit(){
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return true;
    }
    return false;
}


int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<KeyboardPublisher>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
