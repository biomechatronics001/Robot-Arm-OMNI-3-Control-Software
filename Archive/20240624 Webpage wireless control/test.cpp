#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <json/json.h>
#include <iostream>

typedef websocketpp::server<websocketpp::config::asio_no_tls> server;

using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// 消息处理器
void on_message(server* s, connection_hdl hdl, server::message_ptr msg) {
    std::string payload = msg->get_payload();
    Json::Reader reader;
    Json::Value json;
    if (reader.parse(payload, json)) {
        std::string message = json["message"].asString();
        std::cout << "Received message: " << message << std::endl;
        
        // 假设的翻译函数
        std::string translated_message = "Translated " + message; // 示例实现
        std::cout << "Translated message: " << translated_message << std::endl;

        // 响应客户端
        s->send(hdl, translated_message, msg->get_opcode());
    } else {
        std::cerr << "Failed to parse JSON message." << std::endl;
    }
}

int main() {
    server echo_server;

    try {
        // 设置日志设置
        echo_server.set_access_channels(websocketpp::log::alevel::all);
        echo_server.clear_access_channels(websocketpp::log::alevel::frame_payload);

        // 初始化Asio
        echo_server.init_asio();

        // 设置消息处理器
        echo_server.set_message_handler(bind(&on_message, &echo_server, ::_1, ::_2));

        // 监听端口1234
        echo_server.listen(1234);

        // 开始接受连接
        echo_server.start_accept();

        // 开始Asio io_service循环
        echo_server.run();
    } catch (websocketpp::exception const & e) {
        std::cerr << "Websocketpp exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception" << std::endl;
    }

    return 0;
}
