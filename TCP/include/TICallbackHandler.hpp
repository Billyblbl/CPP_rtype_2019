/*
** EPITECH PROJECT, 2019
** babel
** File description:
** callback handler interface template
*/

#ifndef TICALLBACKHANDLER_HPP_
#define TICALLBACKHANDLER_HPP_

#include <boost/asio.hpp>
#include "TConnection.hpp"

namespace TCP {

	///
	///@brief Generic Callback handler interface template
	///
	/// Defines a common interface for an object capable
	/// of handling connections of Protocol
	///
	///@tparam Protocol managed by the callback handler
	///
	template<typename Protocol, typename Metadata>
	class TICallbackHandler {
		public:

			///
			///@brief Default constructor
			///
			///
			TICallbackHandler() = default;

			///
			///@brief Move constructor
			///
			///@warning Deleted as moving a handler refered to by one or more connection
			/// without reassigning them all to the newly moved handler will lead to dangling
			/// references. Too dangerous
			///
			TICallbackHandler(TICallbackHandler &&) = delete;

			///
			///@brief The type of connection handled by the callback handler as defined by Protocol
			///
			///
			using ConnectionType = TConnection<Protocol, Metadata>;

			///
			///@brief Destroy the TICallbackHandler object
			///
			///
			virtual ~TICallbackHandler() = default;

			///
			///@brief Handles a connection event on connection
			///
			///
			virtual void onConnect(ConnectionType &connection) = 0;

			///
			///@brief Handles a message event on connection
			///
			///@param message message event data
			///
			virtual void onMessage(ConnectionType &connection, const typename Protocol::Message &message) = 0;

			///
			///@brief Handles an error event on connection
			///
			///@param er  error event data
			///
			virtual void onError(ConnectionType &connection, const boost::system::error_code &er) = 0;

		protected:
		private:
	};
}


#endif /* !ICALLBACKHANDLER_HPP_ */
