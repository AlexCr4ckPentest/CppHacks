/*
 * WARNING! DO NOT INCLUDE THIS HEADER DIRECTLY!!!
 * BECAUSE IT LEADS TO COMPILATION ERRORS
*/



#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>



#ifndef TCP_CLIENT_IMPL_HPP
#define TCP_CLIENT_IMPL_HPP

namespace alex::utils::network
{
TcpClient::TcpClient()
    : port_         {0}
    , ip_address_   {detail::LOCALHOST}
    , socket_fd_    {::socket(AF_INET, SOCK_STREAM, 0)}
    , addr_info_    {}
{
    if (socket_fd_ == -1) {
        throw errors::ClientError("socket() syscall failed!");
    }

    addr_info_.sin_family = AF_INET;
}



TcpClient::TcpClient(uint16_t port, std::string_view ip_address)
    : port_         {port}
    , ip_address_   {ip_address}
    , socket_fd_    {::socket(AF_INET, SOCK_STREAM, 0)}
    , addr_info_    {}
{
    if (socket_fd_ == defines::INVALID_SOCKET_FD) {
        throw errors::ClientError("socket() syscall failed!");
    }

    addr_info_.sin_family = AF_INET;
    addr_info_.sin_addr.s_addr = inet_addr(ip_address_.c_str());
    addr_info_.sin_port = ::htons(port_);
}



TcpClient::~TcpClient()
{
    if (socket_fd_ != defines::INVALID_SOCKET_FD) {
        disconnect();
    }
}



bool TcpClient::connect()
{
    if (::connect(socket_fd_,
                  reinterpret_cast<sockaddr*>(&addr_info_),
                  static_cast<socklen_t>(sizeof(addr_info_)))
        == defines::INVALID_SOCKET_FD) {
        throw errors::ClientError("connect() syscall failed!");
    }

    return true;
}



bool TcpClient::connect(uint16_t port, std::string_view ip_address)
{
    addr_info_.sin_addr.s_addr = inet_addr(ip_address.data());
    addr_info_.sin_port = ::htons(port);

    port_ = port;
    ip_address_ = ip_address;

    return connect();
}



void TcpClient::disconnect()
{ ::close(socket_fd_); }



ssize_t TcpClient::send(const std::array<char, detail::BUFFER_SIZE>& buffer)
{ return ::send(socket_fd_, buffer.data(), buffer.size(), 0); }



ssize_t TcpClient::send(std::string_view message)
{ return ::send(socket_fd_, message.data(), message.length() + 1, 0); }



ssize_t TcpClient::receive(std::array<char, detail::BUFFER_SIZE>& buffer)
{ return ::recv(socket_fd_, buffer.data(), buffer.size(), 0); }

} // namespace alex::utils::network

#endif // TCP_CLIENT_IMPL_HPP
