/* tcp_server.hpp
 *
 * Simple TCP server
*/



#include <cstdint>
#include <array>
#include <string>
#include <functional>
#include <stdexcept>
#if 0
#include <thread>
#include <mutex>
#endif

#include <netinet/in.h>



#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

namespace alex::utils::network
{
namespace detail
{
constexpr static inline uint16_t BUFFER_SIZE {2048}; // 2 Kib

template<typename T>
concept MessageHandler = std::is_invocable_r_v<void, T, std::string_view>;
} // namespace alex::utils::network::detail

namespace errors
{
struct ServerError : public std::exception
{
    explicit ServerError(const char* message)
        : message_{message}
    {}

    const char* what() const noexcept override
    { return message_; }

private:
    const char* message_;
};
} // namespace alex::utils::network::errors



class TcpServer
{
public:
    explicit TcpServer(uint16_t port, std::string_view ip_address = ""); // Empty string == INADDR_ANY (listen everithing on port port_)
    TcpServer(const sockaddr_in& addr_info);

    ~TcpServer();

    // No copy, no move
    TcpServer(TcpServer&& other)                    = delete;
    TcpServer(const TcpServer& other)               = delete;
    TcpServer& operator=(TcpServer&& other)         = delete;
    TcpServer& operator=(const TcpServer& other)    = delete;

    void start(uint16_t max_clients = SOMAXCONN);

    inline uint16_t get_port() const noexcept
    { return port_; }

    inline std::string get_ip_address() const noexcept
    { return ip_address_; }

    inline sockaddr_in get_client_info() const noexcept
    { return client_addr_info_; }

#if 0
    void set_port(uint16_t port) noexcept
    { port_ = port; }

    void set_ip_address(std::string_view ip_address)
    { ip_address_ = ip_address; }
#endif

    template<detail::MessageHandler message_handler_t>
    inline void install_message_handler(message_handler_t message_handler)
    { message_handler_ = message_handler; }

protected:
    const uint16_t port_;
    std::string ip_address_;

    int server_socket_fd_;
    int client_socket_fd_;
    sockaddr_in server_addr_info_;
    sockaddr_in client_addr_info_;

    void stop();

    virtual void listen(uint16_t max_clients);
    virtual ssize_t receive() const noexcept;

private:
    static std::function<void(std::string_view)> message_handler_;
    static std::array<char, detail::BUFFER_SIZE> buffer_;
};

} // namespace alex::utils::network



// Implementation here
#include "impl/tcp_server/tcp_server_impl.hpp"

#endif // TCP_SERVER_HPP
