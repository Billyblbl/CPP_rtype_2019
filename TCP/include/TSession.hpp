/*
** EPITECH PROJECT, 2019
** babel
** File description:
** server side connection type
*/

#ifndef TSESSION_HPP_
#define TSESSION_HPP_

#include <boost/asio.hpp>
#include "TConnection.hpp"
#include "TICallbackHandler.hpp"

namespace TCP {

	///
	///@brief Session template
	///
	/// Defines a connection type from Protocol which delegates
	/// protocol callbacks handling to a Callback handler of the
	/// same Protocol type
	///
	///@tparam Protocol type used to define the nature of the connection and its events
	///
	template<typename Protocol, typename Metadata>
	class TSession : public TConnection<Protocol, Metadata> {
		public:

			///
			///@brief Callback handler interface type as defined by Protocol
			///
			///
			using HandlerType = TICallbackHandler<Protocol, Metadata>;

			///
			///@brief Construct a new TSession object
			///
			///@param service io_service of network workers
			///@param handler Callback handler object
			///
			TSession(boost::asio::io_service &service, HandlerType &handler):
				TConnection<Protocol, Metadata>(service),
				_handler(&handler)
			{}

			///
			///@brief Move constructor
			///
			///
			TSession(TSession &&) = default;

			///
			///@brief Destroy the TSession object
			///
			///
			virtual ~TSession() = default;

			///
			///@brief Move assignement
			///
			///@param rhs moving session object
			///
			TSession	&operator=(TSession &&rhs) = default;

			///
			///@brief Set the Callback Handler object
			///
			///
			void		setCallbackHandler(HandlerType &handler)
			{
				_handler = &handler;
			}

			///
			///@brief Get the Callback Handler object
			///
			///
			HandlerType	&getCallbackHandler() const
			{
				return *_handler;
			}

			///
			///@brief Delegates message events management to handler
			///
			///
			void	onMessage(const typename Protocol::Message &message) final
			{
				_handler->onMessage(*this, message);
			}

			///
			///@brief Delegates connection event management to handler
			///
			///
			void	onConnect() final
			{
				_handler->onConnect(*this);
			}

			///
			///@brief Delegates connection event management to handler
			///
			///
			void	onError(const boost::system::error_code &er) final
			{
				_handler->onError(*this, er);
			}

		protected:
		private:
			HandlerType	*_handler;
	};
}


#endif /* !Session_HPP_ */
