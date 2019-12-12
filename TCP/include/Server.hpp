/*
** EPITECH PROJECT, 2019
** babel
** File description:
** babel server class
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <boost/asio.hpp>
#include <vector>
#include <memory>
#include "TServer.hpp"
#include "Protocol.hpp"
#include "Instance.hpp"

struct Metadata {
	uint64_t	id;
	uint32_t	playerID;
	// int				callId;
	// REngineTCP::Pseudonym	pseudo;
};

class Server : public TCP::TServer<REngineTCP, Metadata> {
	public:

		using InstanceList = std::vector<std::unique_ptr<Instance>>;
		using Session = ConnectionType;

		Server(int port, io_service &service, InstanceList &list);
		~Server() = default;

		void	onMessage(Session &session, const REngineTCP::Message &message) override;
		void	onError(Session &session, const boost::system::error_code &er) override;

		void	onEngineErr(Session &session, const std::string &reason);

		Instance::ID	makeInstance(const std::string &file);
		void			killInstance(Instance::ID id);

		void			joinInstance(Session &session, Instance::ID id);
		void			quitInstance(Session &session, Instance::ID id);

	protected:
	private:
		InstanceList	&_instances;
};

#endif /* !SERVER_HPP_ */
