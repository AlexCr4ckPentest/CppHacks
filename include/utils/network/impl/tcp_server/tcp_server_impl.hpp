/*
 * WARNING! DO NOT INCLUDE THIS HEADER DIRECTLY!!!
 * BECAUSE IT LEADS TO COMPILATION ERRORS
*/

#ifndef TCP_SERVER_IMPL_HPP
#define TCP_SERVER_IMPL_HPP



#include <cstring>

#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>



namespace alex::utils::network
{
constexpr static inline int INVALID_SOCKET_FD {-1};

std::function<void(std::string_view)> TcpServer::message_handler_ {};
std::array<char, detail::BUFFER_SIZE> TcpServer::buffer_   {};



TcpServer::TcpServer(uint16_t port, std::string_view ip_address)
    : port_             {port}
    , ip_address_       {ip_address}
    , server_socket_fd_ {::socket(AF_INET, SOCK_STREAM, 0)}
    , client_socket_fd_ {INVALID_SOCKET_FD}
    , server_addr_info_ {}
    , client_addr_info_ {}
{
    if (server_socket_fd_ == INVALID_SOCKET_FD) {
        throw errors::ServerError("socket() syscall failed!");
    }

    server_addr_info_.sin_family = AF_INET;
    server_addr_info_.sin_port = htons(port_);
    server_addr_info_.sin_addr.s_addr = ((ip_address_.empty() || ip_address_ == "0.0.0.0") ?
                                             INADDR_ANY :
                                             ::inet_addr(ip_address_.c_str()));
}



TcpServer::TcpServer(const sockaddr_in& addr_info)
    : port_             {addr_info.sin_port}
    , server_socket_fd_ {::socket(AF_INET, SOCK_STREAM, 0)}
    , client_socket_fd_ {INVALID_SOCKET_FD}
    , server_addr_info_ {addr_info}
    , client_addr_info_ {}
{
    if (server_socket_fd_ == INVALID_SOCKET_FD) {
        throw errors::ServerError("socket() syscall failed!");
    }

    // Save ip-address
    ip_address_.reserve(INET_ADDRSTRLEN);
    if (::inet_ntop(server_addr_info_.sin_family,
                    reinterpret_cast<const void*>(&server_addr_info_.sin_addr),
                    ip_address_.data(),
                    INET_ADDRSTRLEN)
        == NULL) {
        throw errors::ServerError("inet_ntop() returned NULL!");
    }
}



TcpServer::~TcpServer()
{
    stop();
}



void TcpServer::start(uint16_t max_clients)
{
    if (::bind(server_socket_fd_,
               reinterpret_cast<sockaddr*>(&server_addr_info_),
               static_cast<socklen_t>(sizeof(server_addr_info_)))
        == INVALID_SOCKET_FD) {
        throw errors::ServerError("bind() syscall failed!");
    }

    listen(max_clients);
}



void TcpServer::stop()
{
    ::close(client_socket_fd_);
    ::close(server_socket_fd_);
}



void TcpServer::listen(uint16_t max_clients)
{
    if (::listen(server_socket_fd_, max_clients) == INVALID_SOCKET_FD) {
        throw errors::ServerError("listen() syscall failed!");
    }

    socklen_t client_addr_info_length {static_cast<socklen_t>(sizeof(client_addr_info_))};

    client_socket_fd_ = ::accept(server_socket_fd_,
                                 reinterpret_cast<sockaddr*>(&client_addr_info_),
                                 &client_addr_info_length);

    if (client_socket_fd_ == INVALID_SOCKET_FD) {
        throw errors::ServerError("accept() syscall failed!");
    }

    ssize_t bytes_received {0};

    while ((bytes_received = receive()) > 0) {
        std::string_view message {buffer_.data(), static_cast<std::string_view::size_type>(bytes_received)};
        message_handler_(message);
    }
}



ssize_t TcpServer::receive() const noexcept
{ return ::recv(client_socket_fd_, buffer_.data(), buffer_.size(), 0); }

} // namespace alex::utils::network

#endif // TCP_SERVER_IMPL_HPP
