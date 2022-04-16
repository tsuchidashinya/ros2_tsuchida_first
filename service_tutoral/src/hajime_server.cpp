#include <rclcpp/rclcpp.hpp>
#include <new_message/srv/ningen.hpp>

#include <memory>

int count = 0;
std::shared_ptr<rclcpp::Node> node;

void add(const std::shared_ptr<new_message::srv::Ningen::Request> request,
            std::shared_ptr<new_message::srv::Ningen::Response> responce)
{
    int sum = request->a + request->b;
    count++;
    node->set_parameter(rclcpp::Parameter("tsuchida_parametor", count));
    responce->answer = "answer is " + std::to_string(sum);
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service is coming now");
}

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);

    node = rclcpp::Node::make_shared("hayaku");
    rclcpp::Service<new_message::srv::Ningen>::SharedPtr service =
                node->create_service<new_message::srv::Ningen>("new_service", &add);
    node->declare_parameter<int>("tsuchida_parametor", count);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}