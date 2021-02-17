/* tcp_client.hpp
 *
 * Simple TCP client
*/



#include <cstdint>
#include <array>
#include <string>
#include <functional>
#include <stdexcept>

#include <netinet/in.h>




#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

namespace alex::utils::network
{
namespace detail
{
constexpr const char* LOCALHOST {"127.0.0.1"};
} // namespace alex::utils::network::detail

namespace errors
{
struct ClientError : public std::exception
{
    explicit ClientError(const char* message) noexcept
        : message_ {message}
    {}

    const char* what() const noexcept override
    { return message_; }

private:
    const char* message_;
};
} // namespace alex::utils::network::errors



class TcpClient
{
public:
    TcpClient();
    explicit TcpClient(uint16_t port, std::string_view ip_address = detail::LOCALHOST);

    ~TcpClient();

    bool connect();
    bool connect(uint16_t port, std::string_view ip_address = detail::LOCALHOST);

    void disconnect();

    virtual ssize_t send(const std::array<char, defines::BUFFER_SIZE>& buffer);
    ssize_t send(std::string_view message);

    virtual ssize_t receive(std::array<char, defines::BUFFER_SIZE>& buffer);

    inline uint16_t remote_port() const noexcept
    { return port_; }

    inline std::string remote_ip_address() const noexcept
    { return ip_address_; }

private:    
    uint16_t port_;
    std::string ip_address_;

    int socket_fd_;
    sockaddr_in addr_info_;
};

} // namespace alex::utils::network



// Implementation here
#include "impl/tcp_client/tcp_client_impl.hpp"

#endif // TCP_CLIENT_HPP
