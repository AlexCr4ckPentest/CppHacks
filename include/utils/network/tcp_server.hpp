/* tcp_server.hpp
 *
 * Simple TCP server, based on Boost.Asio library
*/



#include <memory>

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>



#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

namespace alex::utils::network
{
namespace asio = boost::asio;



class tcp_session : public std::enable_shared_from_this<tcp_session>
{
public:
  explicit tcp_session(asio::ip::tcp::socket&& socket)
    : socket_{std::move(socket)}
  {}

  // No copy, no move
  tcp_session(tcp_session&&) = delete;
  tcp_session(const tcp_session&) = delete;
  tcp_session& operator=(tcp_session&&) = delete;
  tcp_session& operator=(const tcp_session&) = delete;

  virtual void start() &
  { receive(); }

  tcp_session* when_destroyed(const std::function<void()>& handler) &
  {
    when_destryed_ = handler;
    return this;
  }

  tcp_session* when_data_received(const std::function<void(std::string_view)>& handler) &
  {
    when_data_received_ = handler;
    return this;
  }

protected:
  virtual void receive()
  {
    socket_.async_read_some(asio::buffer(buffer_, buffer_.max_size()),
                            [self = shared_from_this(), this](boost::system::error_code error, size_t n)
    {
      if (!error)
      {
#ifdef _TCP_ECHO_SERVER_
        send(n);
#else
        receive();
#endif
        when_data_received_({buffer_.data(), n});
      }
    });
  }

#ifdef _TCP_ECHO_SERVER_
  virtual void send(size_t n)
  {
    socket_.async_write_some(asio::buffer(buffer_, n),
                             [self = shared_from_this(), this](boost::system::error_code error, size_t)
    {
      if (!error)
      {
        receive();
      }
    });
  }
#endif

private:
  asio::ip::tcp::socket socket_;

  static std::array<char, 2048> buffer_;
  static std::function<void()> when_destryed_;
  static std::function<void(std::string_view)> when_data_received_;
};



class tcp_server
{
public:
  tcp_server(asio::io_context& io_con, const asio::ip::tcp::endpoint& endpoint)
    : server_endpoint_{endpoint}
    , tcp_acceptor_{io_con, server_endpoint_}
  {}

  tcp_server(asio::io_context& io_con, uint16_t port)
    : server_endpoint_{boost::asio::ip::tcp::v4(), port}
    , tcp_acceptor_{io_con, server_endpoint_}
  {}

  // No copy, no move
  tcp_server(tcp_server&&) = delete;
  tcp_server(const tcp_server&) = delete;
  tcp_server& operator=(tcp_server&&) = delete;
  tcp_server& operator=(const tcp_server&) = delete;



  virtual void run() &
  {
    tcp_acceptor_.async_accept([this](boost::system::error_code error, asio::ip::tcp::socket&& socket)
    {
      if (!error)
      {
        client_endpoint_ = socket.remote_endpoint();
        client_connected_handler_();

        std::make_shared<tcp_session>(std::move(socket))
            ->when_destroyed(client_disconnected_handler_)
            ->when_data_received(data_received_handler_)
            ->start();
      }
    });
  }

  asio::ip::tcp::endpoint remote_endpoint() const noexcept
  { return client_endpoint_; }

  tcp_server& when_client_connected(const std::function<void()>& client_connected_handler)
  {
    client_connected_handler_ = client_connected_handler;
    return *this;
  }

  tcp_server& when_client_disconnected(const std::function<void()>&& client_disconnected_handler)
  {
    client_disconnected_handler_ = client_disconnected_handler;
    return *this;
  }

  tcp_server& when_data_received(const std::function<void(std::string_view)>& data_received_handler)
  {
    data_received_handler_ = data_received_handler;
    return *this;
  }

private:
  asio::ip::tcp::endpoint server_endpoint_;
  asio::ip::tcp::acceptor tcp_acceptor_;
  asio::ip::tcp::endpoint client_endpoint_;
  static std::function<void()> client_connected_handler_;
  static std::function<void()> client_disconnected_handler_;
  static std::function<void(std::string_view)> data_received_handler_;
};



/* Initializing static members for class tcp_session
 */
std::array<char, 2048> tcp_session::buffer_{};
std::function<void()> tcp_session::when_destryed_{[]() {}};
std::function<void(std::string_view)> tcp_session::when_data_received_{[](std::string_view) {}};



/* Initializing static members for class tcp_server
 */
std::function<void()> tcp_server::client_connected_handler_{[]() {}};
std::function<void()> tcp_server::client_disconnected_handler_{[]() {}};
std::function<void(std::string_view)> tcp_server::data_received_handler_{[](std::string_view) {}};

} // namespace alex::utils::network

#endif // TCP_SERVER_HPP
