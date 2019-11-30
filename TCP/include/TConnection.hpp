/*
** EPITECH PROJECT, 2019
** babel
** File description:
** connection template
*/

#ifndef TCONNECTION_HPP_
#define TCONNECTION_HPP_

#include <array>
#include <vector>
#include <memory>
#include <boost/asio.hpp>

namespace TCP
{
	
	///
	///@brief Generic connection object
	///
	///@tparam Protocol protocol used to define message bounds
	///@warning Protocol is always over tcp
	///
	template<typename Protocol, typename Metadata>
	class TConnection {
		public:

			using tcp = boost::asio::ip::tcp;
			using io_service = boost::asio::io_service;

			///
			///@brief Reader buffer
			///
			///
			struct RBuffer {
				std::array<std::byte, 1024>	input;
				std::vector<std::byte>		data;
			};

			///
			///@brief Writter buffer
			///
			///
			using WBuffer = std::vector<std::byte>;

			///
			///@brief Construct a new TConnection object
			///
			///@param service assigned asio io_service
			///
			TConnection(io_service &service):
				_socket(service),
				_open(false)
			{}

			///
			///@brief Move constructor
			///
			///
			TConnection(TConnection &&) = delete;

			///
			///@brief Destroy the TConnection object
			///
			///
			virtual ~TConnection()
			{
				bool	wasOpen = _open;
				_open = false;
				if (wasOpen) {
					close();
				}
			}

			///
			///@brief Move assignement
			///
			///@param rhs moving connection object
			///
			TConnection		&operator=(TConnection &&rhs) = delete;

			///
			///@brief Called when the connection  is used in socket accept network procedure.
			///
			/// TConnection is considered open from this point
			///
			void			onAccept()
			{
				_open = true;
				startReceive();
				startSend();
				onConnect();
			}

			///
			///@brief Equality operator
			///
			/// Equality based on meory location as connection are immovable objects
			///
			bool			operator==(const TConnection &rhs) const
			{
				return this == &rhs;
			}

			///
			///@brief Called on connect, meant to be overriden
			///
			///
			virtual void	onConnect() {};

			///
			///@brief Called on message as defined by Protocol, meant to be overriden
			///
			///@param message received to treat
			///
			virtual void	onMessage(const typename Protocol::Message &message) {(void)message;}

			///
			///@brief Called on network error, meant to be overriden
			///
			///@param er error received to treat
			///
			virtual void	onError(const boost::system::error_code &er)
			{
				std::cerr << er << "\r\n";
			}

			///
			///@brief Bufferise message to be sent on sender work
			///
			///@param message to send
			///
			void			Send(const typename Protocol::Message &message)
			{
				Protocol::writeMessage(_wBuffer, message);
			}

			///
			///@brief Get the Socket object
			///
			///@return tcp::socket& connection's socket
			///
			tcp::socket			&getSocket()
			{
				return _socket;
			}

			///
			///@brief Get the Socket object
			///
			///@return const tcp::socket& connection's immutable socket
			///
			const tcp::socket	&getSocket() const
			{
				return _socket;
			}

			///
			///@brief Get the Metadata object
			///
			/// const getter
			///
			const Metadata	&getMetadata() const
			{
				return _data;
			}

			///
			///@brief Get the Metadata object
			///
			/// mutable getter
			///
			Metadata		&getMetadata()
			{
				return _data;
			}

			void			close()
			{
				_open = false;
				boost::system::error_code ec;
				_socket.shutdown(tcp::socket::shutdown_both, ec);
				if (ec)
					std::cerr << "E : " << ec << "\r\n";
				_socket.close(ec);
				if (ec)
					std::cerr << "E : " << ec << "\r\n";
			}

			bool			isOpen() const
			{
				return _open;
			}

		protected:
		private:

			///
			///@brief Receiving work
			///
			/// fills Reader buffer and call onMessage when reader buffer
			/// contains a message as defined by Protocol
			///
			void	startReceive()
			{
				auto handler = [this](const boost::system::error_code &er, size_t bytes){
					try {
						if (er) {
							onError(er);
							_open = false;
						} else {
							_rBuffer.data.insert(_rBuffer.data.end(), _rBuffer.input.begin(), _rBuffer.input.begin() + bytes);
							if (Protocol::hasValidMessage(_rBuffer.data))
								onMessage(Protocol::extractMessage(_rBuffer.data));
							//Protocol : is there a messaeg? -> handle it
							startReceive();
						}
					} catch(const std::exception& e) {
						std::cerr << __func__ << ' ' << e.what() << "\r\n";
					}
				};
				_socket.async_receive(boost::asio::buffer(_rBuffer.input), handler);
			}

			///
			///@brief Sender work
			///
			/// Sends data from Writer buffer
			///
			void	startSend()
			{
				auto handler = [this](const boost::system::error_code &er, size_t bytes){
					try {
						if (er) {
							onError(er);
							_open = false;
						} else {
							_wBuffer.erase(_wBuffer.begin(), _wBuffer.begin() + bytes);
							startSend();
						}
					} catch(const std::exception& e) {
						std::cerr << __func__ << ' ' << e.what() << "\r\n";
					}
				};
				_socket.async_send(boost::asio::buffer(_wBuffer), handler);
			}

			tcp::socket	_socket;
			bool		_open;
			RBuffer		_rBuffer;
			WBuffer		_wBuffer;

			Metadata	_data;

	};
} // namespace TCP



#endif /* !TCONNECTION_HPP_ */
