/* tcp_client.hpp
 *
 * Simple TCP client
*/



#include <cstdint>
#include <array>
#include <string>
#include <stdexcept>



#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

namespace alex::utils::network
{
namespace detail
{
constexpr const char* LOCALHOST {"127.0.0.1"};
} // namespace detail

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
} // namespace errors



class TcpClient
{
public:
    explicit TcpClient();
    TcpClient(uint16_t port, std::string_view ip_address = detail::LOCALHOST);

protected:


private:
    int socket_fd_;

    uint16_t port_;
    std::string ip_address_;
};



TcpClient::TcpClient()
    : socket_fd_ {}
{}

TcpClient::TcpClient(uint16_t port, std::string_view ip_address)

{  }

} // namespace alex::utils::network



// Implementation here
#include "impl/tcp_client/tcp_client_impl.hpp"

#endif // TCP_CLIENT_HPP
