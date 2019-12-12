/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include "TConnection.hpp"
#include "Protocol.hpp"
#include "Instance.hpp"

struct Metadata {
	uint32_t	playerID;
};

class Client : public TCP::TConnection<REngineTCP, Metadata> {
	public:
		Client(io_service &service, Instance &local);

		void	onConnect() override;

		void	onMessage(const REngineTCP::Message &message) override;
		void	onError(const boost::system::error_code &er) override;

		void	onEngineErr(const std::string &reason);

		void	makeInstance(const std::string &file);
		void	killInstance(Instance::ID id);

		void	joinInstance(Instance::ID id);
		void	quitInstance(Instance::ID id);

	protected:
	private:

		Instance		&_local;
		Instance::ID	_lobby;
};

#endif /* !CLIENT_HPP_ */
