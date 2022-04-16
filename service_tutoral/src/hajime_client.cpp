#include <rclcpp/rclcpp.hpp>
#include <new_message/srv/ningen.hpp>
#include <chrono>
#include <cstdlib>
#include <memory>
 
using namespace std::chrono_literals;

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    if (argc != 3) {
        RCLCPP_INFO_STREAM(rclcpp::get_logger("rclcpp"), "usage: add_two_ints_client X Y");
    }

    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("saikoudesu");
    rclcpp::Client<new_message::srv::Ningen>::SharedPtr client = 
            node->create_client<new_message::srv::Ningen>("new_service");
    auto request = std::make_shared<new_message::srv::Ningen::Request>();
    request->a = atoi(argv[1]);
    request->b = atoi(argv[2]);
    while (!client->wait_for_service(1s)) {
        if (!rclcpp::ok()) {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "interrupted while waiting");
            return 0;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available");
    }
    
    auto result = client->async_send_request(request);
    if (rclcpp::spin_until_future_complete(node, result) ==
            rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), result.get()->answer);
        auto param_client = std::make_shared<rclcpp::SyncParametersClient>(node, "hayaku");
        auto as = param_client->get_parameters({"tsuchida_parametor"});
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), as[0].value_to_string());
        
    }
    else {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Fail to service");
    }
    rclcpp::shutdown();
    return 0;
}