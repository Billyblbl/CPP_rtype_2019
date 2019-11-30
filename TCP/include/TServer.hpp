/*
** EPITECH PROJECT, 2019
** babel
** File description:
** server template
*/

#ifndef TSERVER_HPP_
#define TSERVER_HPP_

#include <vector>
#include <memory>
#include <type_traits>
#include <iomanip>
#include <boost/asio.hpp>
#include "TSession.hpp"
#include "TICallbackHandler.hpp"

namespace TCP {

	///
	///@brief Generic server template from Protocol
	///
	///@tparam Protocol used by the server, defines message nature and boundaries (over tcp)
	///@tparam SessionMeta Metadata type held by each connection's session
	///
	template<typename Protocol, typename SessionMeta = void>
	class TServer : public TICallbackHandler<Protocol, SessionMeta> {
		public:

			///
			///@brief Session type as defined by protocol and meatadata type
			///
			///
			using Session = TSession<Protocol, SessionMeta>;
			using SessionHandle = std::shared_ptr<Session>;
			using ConnectionType = typename TICallbackHandler<Protocol, SessionMeta>::ConnectionType;

			static_assert(std::is_base_of_v<ConnectionType, Session>, "Session type does not extend Connection type properly");

			using io_service = boost::asio::io_service;
			using tcp = boost::asio::ip::tcp;

			///
			///@brief Construct a new TServer object
			///
			///@param port to listen on
			///
			TServer(int port, io_service &service):
				_service(service),
				_work(_service),
				_incoming(_service)
				// _worker([this](){this->doWork();})
			{
				tcp::resolver	resolver(_service);
				tcp::endpoint	endpoint = *resolver.resolve(
					"127.0.0.1",
					std::to_string(port)
				);
				_incoming.open(endpoint.protocol());
				_incoming.set_option(tcp::acceptor::reuse_address(true));
				_incoming.bind(endpoint);
				_incoming.listen(boost::asio::socket_base::max_connections);
				std::cout << "Listening on: " << endpoint << std::endl;
				startAccept();
			}

			///
			///@brief Destroy the TServer object
			///
			///
			virtual ~TServer()
			{
				_service.stop();
			}

			///
			///@brief Handles a connection event on connection
			///
			///
			virtual void onConnect(ConnectionType &connection) override {(void)connection;}

			///
			///@brief Handles a message event on connection
			///
			///@param message message event data
			///
			virtual void onMessage(ConnectionType &connection, const typename Protocol::Message &message) override
			{
				(void)connection;
				(void)message;
			}

			///
			///@brief Handles an error event on connection
			///
			///@param er  error event data
			///
			virtual void onError(ConnectionType &connection, const boost::system::error_code &er) override
			{
				(void)connection;
				(void)er;
			}

			///
			///@brief worker task
			///
			///
			void	poll()
			{
				try {
					while (!_service.stopped()) {
						try {
							_service.poll();
						} catch(const std::exception &e) {
							std::cerr << e.what() << "\r\n";
						}
					}
				} catch(const std::exception& e) {
					// std::cerr << "WORKER FATAL " << e.what() << " Press [Enter] to exit\r\n";
					_service.stop();
				}
			}

		protected:
		private:

			///
			///@brief start connection accepting task
			///
			///
			void	startAccept()
			{
				SessionHandle	newConnection(_connections.emplace_back(std::make_shared<Session>(_service, *this)));
				_incoming.async_accept(newConnection->getSocket(), [this, newConnection](const boost::system::error_code &){
					static uint64_t lastID = 0;
					newConnection->getMetadata().id = lastID++;
					newConnection->onAccept();
					// std::cout << "Accepted connection ["
					// 		<< std::hex
					// 		<< std::setfill('0')
					// 		<< std::setw(16) << newConnection->getMetadata().id
					// 		<< ']' << std::endl;
					startAccept();
				});
			}


			io_service					&_service;
			io_service::work			_work;
			tcp::acceptor				_incoming;

		protected:
			std::vector<SessionHandle>	_connections;

	};
}

#endif /* !TSERVER_HPP_ */
